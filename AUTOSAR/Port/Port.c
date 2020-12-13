 /******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port.c
 *
 * Description: Source file for Port Module APIs on TM4C123GH6PM Microcontroller
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        10/12/2020
 *
 ******************************************************************************/


#include "Port.h"
#include "Port_Reg.h"

/* Check if DET Error is enabled or not through configuration tool*/
#if(PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif

/*
 * Global variable to check if Port is initialized or not
 * STATIC to make its scope within this file only
*/
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

/*
 * Pointer to const structure that has the configurations of Port Module
 * Initialized with Null to avoid any errors
 * STATIC to make its scope within this file only
*/
STATIC const Port_ConfigChannel * Port_Channels = NULL_PTR;


/************************************************************************************
* Service Name:         Port_Init
* Service ID[hex]:      0x00
* Sync/Async:           Synchronous
* Reentrancy:           Non-Reentrant
* Parameters (in):      ConfigPtr - Pointer to configuration set
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function to initialize the port driver Module
************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr)
{
    /* Pointer to Requested Port Register */
    volatile uint32* PortGpio_Ptr = NULL_PTR;

    /* Variable to waste time to ensure clock stability */
    volatile uint32  delay = 0;

    /* Variable to iterate on it */
    uint8 counter = 0;

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* Check if the input configuration pointer to structure is Not a Null Pointer */
    if(NULL_PTR == ConfigPtr)
    {
        /* ConfigPtr is a Null Pointer, Report a DET Error as a PORT_E_PARAM_CONFIG */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_PARAM_CONFIG);

        /*
         * As SWS Said, if a Null pointer found, Function should report an DET Error
         * and return without any action
        */

        return;
    }
    else
/*
 * Here you can see #endif is put after else so that if DET Error disabled through tool
 * i won't have a bug here said "else without previous if"
 */
#endif
    {

        /*
         * Point to the first channel of the first element
         * of the array of post built configuration structure
         * (portChannels[0])
        */
        Port_Channels = ConfigPtr -> portChannels;

        /* For Loop to iterate through Channels */
        for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
        {

             switch(Port_Channels[counter].portNum)
             {
             case PORTA:

                 /* Point the pointer to PORTA Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;

             break;

             case PORTB:

                 /* Point the pointer to PORTB Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;

             break;

             case PORTC:

                 /* Point the pointer to PORTC Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;

             break;

             case PORTD:

                 /* Point the pointer to PORTD Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;

             break;

             case PORTE:

                 /* Point the pointer to PORTE Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;

             break;

             case PORTF:

                 /* Point the pointer to PORTF Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;

             break;
             }
               /* Enable Clock for requested Port */
               SYSCTL_REGCGC2_REG   |= (1 << Port_Channels[counter].portNum);

               /* Delay to waste sometime to ensure clock stability */
               delay = SYSCTL_REGCGC2_REG;
            /*
             * Check if the pin is not on the default mode
             * if it is on default mode, Nothing of GPIO Configuration sequence will happen
             * Which means the pin will be not usable in this application
            */
            if(Port_Channels[counter].direction != PORT_PIN_DEFAULT)
            {
               /*
                * Check if requested Pins are the Locked ones (PF0 or PD7)
                * If so, start unlock procedure to set the corresponding configurations to them
               */
               if( ( (Port_Channels[counter].portNum == PORTD) && (Port_Channels[counter].pinNum == PORT_D_PIN_7) ) || \
                   ( (Port_Channels[counter].portNum == PORTF) && (Port_Channels[counter].pinNum == PORT_F_PIN_0) ) )
               {
                   /* First, Unlock the LOCK Register by setting it with its Unlock value */

                   /*
                    * First, PortGpio_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
                    * because if it is not type casted, adding Lock Register offset will make it
                    * PORT_LOCK_REG_OFFSET value * 4 because it will behave as uint32*,
                    * so it is a must to type cast the base address to uint8*
                    *
                    * Second the whole pointer is type casted again to uint32*
                    * Lastly the last asterisk on the left is used to dereference the pointer
                   */
                   *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK_VALUE;

                   /* Set the Commit bit of the corresponding pin in Commit register */
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[counter].pinNum);
               }

               /*
                * Check if requested Pins are the JTAG Ones
                * if so, do nothing
               */
               else if( (Port_Channels[counter].portNum == PORTC) && (Port_Channels[counter].pinNum <= PORT_C_PIN_3_JTAG) )
               {
                   /* DO Nothing, these are JTAG Pins */

                   /* Continue used because this iteration is not a valid one so that i need to go to the next one */
                   continue;
               }
               else
               {
                  /* Do nothing, no need to unlock the commit register */
               }

               /*
                * Check if Analog mode Selected or Not
                * ANALOG_MODE_SELECTED     = 15 -> ADC
               */
               if( (Port_Channels[counter].mode == ANALOG_MODE_SELECTED) )
               {
                  /*
                   * Analog Mode Selected
                   * Start Analog Mode initiation Procedures
                  */

                   /* 1- Set AFSEL (Alternative Function Selection) Bit corresponding to the Pin Number */
                   SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[counter].pinNum );

                   /* 2- Clear DEN (Digital Enable) Bit corresponding to the pin number */
                   CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);

                   /* 3- Set AMSEL (Analog Mode Selection) Bit Corresponding to the pin number */
                   SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[counter].pinNum );
               }
               else
               {
                   /*
                    * Normal Digital Mode
                    * Start Digital Mode initiation procedure
                   */

                   /* 1- Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
                   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[counter].pinNum);

                   /* Check if Alternative function selected or not*/
                   if( (Port_Channels[counter].mode == DIO_PIN) )
                   {
                       /*
                        * Alternative function not selected
                        * Pin Configured as Normal PORT
                       */

                       /* 2- Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[counter].pinNum);

                       /* 3- Clear the PMCx bits for this pin */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PORT_CONTROL_MASK_VALUE << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );

                   }

                   else
                   {
                       /* Alternative function selected */

                       /* 2- Set AFSEL (Alternative Function Selection) Bit corresponding to the Pin Number */
                       SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[counter].pinNum );

                       /*
                        * 3- Set the PMCx bits for this pin
                        * First, get the mode selected from the Structure
                        * Then left shift it with PinNum *4
                        * because every pin has 4 bits of configurations
                       */
                       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Port_Channels[counter].mode) << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS) );

                   }

               }

                 /* Check if Pin Input or Output */
               if(Port_Channels[counter].direction == PORT_PIN_OUT)
               {
                   /* Output Pin Selected */

                   /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);

                   /* Check for Initial Value */
                   if(Port_Channels[counter].initialValue == INITIAL_VALUE_HIGH)
                   {
                       /* Set the corresponding bit initial value = 1 */
                       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[counter].pinNum);
                   }
                   else
                   {
                       /* Set the corresponding bit initial value = 0 */
                       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Channels[counter].pinNum);

                   }

                   /* Check for Slew Rate Enabled / Disabled */
                   if(Port_Channels[counter].slewRate == SLEW_RATE_ENABLE)
                   {
                       /* Slew Rate enabled, Set the corresponding bit in GPIOSLR (Slew Rate)  */
                       SET_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_SLEW_RATE_CONTROL_OFFSET), Port_Channels[counter].pinNum);
                   }
                   else
                   {
                       /* Slew Rate disabled, clear the corresponding bit in GPIOSLR (Slew Rate)  */
                       CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_SLEW_RATE_CONTROL_OFFSET), Port_Channels[counter].pinNum);
                   }
               }
               else if (Port_Channels[counter].direction == PORT_PIN_IN)
               {
                   /* Input Pin Selected */

                   /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                   CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);

                   /* Check for Internal resistor settings */
                   if(Port_Channels[counter].resistor == PULL_UP)
                   {
                       /* Internal Pull Up resistor Selected */

                       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                       SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channels[counter].pinNum);

                   }
                   else if(Port_Channels[counter].resistor == PULL_DOWN)
                   {
                       /* Internal Pull Down resistor settings */

                       /* Set the corresponding bit in the GPIOPDR register to enable the internal pull up pin */
                        SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channels[counter].pinNum);
                   }
                   else
                   {
                       /*
                        * Neither Internal Pull Up, nor Pull down selected
                        * Clear Both Pull up & down for corresponding pin
                       */

                       /* Clear Pull Up Internal Resistor corresponding Pin */
                       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , Port_Channels[counter].pinNum);

                       /* Clear Pull Up Internal Resistor corresponding Pin */
                       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , Port_Channels[counter].pinNum);

                   }


               }
               else
               {
                   /* Do nothing  */
               }

               /* Check if Analog mode is not selected to enable the digital feature */
               if( !(Port_Channels[counter].mode == ANALOG_MODE_SELECTED) )
               {
                   /* Digital Mode Selected */

                   /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
                   SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[counter].pinNum);
               }

            }
            else
            {
                /*
                 *  This else for the first if in the loop
                 * if the flow goes here, then the pin is not used
                 * then nothing will happen to this pin (as GPIO Configurations)
                 * It should go to initial value (Reset value from Data sheet)
                 */

                /* Clear the corresponding bit in AFSEL Register to go initial value (from the data sheet which is reset value) */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in PUR (Pull up) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in PDR (Pull down) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in SLR (Slew Rate) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_SLEW_RATE_CONTROL_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bit in DEN (Digital Enable) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Do not do anything with Lock & Commit register */

                /* Clear the corresponding bit in AMSEL (Analog Mode Selection) Register */
                CLEAR_BIT(*(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[counter].pinNum);

                /* Clear the corresponding bits in PCTL (Port Control) Register (Responsible of Alternative function selection)*/
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(PORT_CONTROL_MASK_VALUE << ( (Port_Channels[counter].pinNum) * PORT_CONTROL_BIT_NUMBERS));

            }

        }
          /*
           * Set the Port_status variable as Initialized
           * because all the pins are initialized now
          */
          Port_Status = PORT_INITIALIZED;
    }

}


/************************************************************************************
* Service Name:         Port_SetPinDirection
* Service ID[hex]:      0x02
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      Pin       - Port Pin ID Number
*                       Direction - Port Pin Direction
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function that sets the port pin direction
* Note:                 This function can be deleted if
*                       PORT_SET_PIN_DIRECTION_API != STD_ON
************************************************************************************/

/* check if Port_GetVersionAPI is selected from the tool */
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
    /* Pointer to Requested Port Register */
    volatile uint32* PortGpio_Ptr = NULL_PTR;

    /* Variable to hold Error status */
    boolean error = FALSE;

    /* Variable used to loop on the array of structure */
    uint8 counter = 0;

    /* Variable used to save the index of the array element needed  */
    uint8 Id = 0;

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* Check if this function is called before initialization the Port Module */
    if(PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Port Module doesn't initialized yet, report a PORT_E_UNINIT DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing */
    }

    /* Check for incorrect PortPin ID Passed */
    if(PORT_CONFIGURED_CHANNLES <= Pin)
    {
        /* Incorrect Pin ID passed, report a PORT_E_PARAM_PIN DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);

    }
    else
    {
        /* Do nothing */
    }

/*
 * Here you can see #endif is put after else so that if DET Error disabled through tool
 * i won't have a bug here said "else without previous if"
 */
#endif

    for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
    {
        if(Port_Channels[counter].pinNum == Pin)
        {
            /* Save the Array index */
            Id = counter;

            /* Get out of the Loop */
            break;
        }
    }

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if this Pin is unchangeable */
    if( Port_Channels[Id].pinDirection_Changeable == PIN_DIRECTION_CHANGEABILITY_OFF)
    {
        /* Pin is Unchangeable, report an PORT_E_DIRECTON_UNCHANGEABLE DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTON_UNCHANGEABLE);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing, Pin direction is changeable */
    }
#endif
    /* Check if there are no errors */
    if(error == FALSE)
    {
        /* Find Port that pin on it */
        switch(Port_Channels[Id].portNum)
        {
            case PORTA:
                /* Point the pointer to PORTA Base Address */
                PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;
            break;

            case PORTB:
                /* Point the pointer to PORTB Base Address */
                PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;
            break;

            case PORTC:
                /* Point the pointer to PORTC Base Address */
                PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;
            break;

            case PORTD:
                /* Point the pointer to PORTD Base Address */
                PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;
            break;

            case PORTE:
                /* Point the pointer to PORTE Base Address */
                PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
            break;

            case PORTF:
                  /* Point the pointer to PORTF Base Address */
                  PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
              break;
        }

        /*
         * Check if requested Pins are the Locked ones (PF0 or PD7)
         * If so, start unlock procedure to set the corresponding configurations to them
        */
        if( ( (Port_Channels[Id].portNum == PORTD) && (Port_Channels[Id].pinNum == PORT_D_PIN_7) ) || \
            ( (Port_Channels[Id].portNum == PORTF) && (Port_Channels[Id].pinNum == PORT_F_PIN_0) ) )
        {
            /* First, Unlock the LOCK Register by setting it with its Unlock value */

            /*
             * First, PortGpio_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
             * because if it is not type casted, adding Lock Register offset will make it
             * PORT_LOCK_REG_OFFSET value * 4 because it will behave as uint32*,
             * so it is a must to type cast the base address to uint8*
             *
             * Second the whole pointer is type casted again to uint32*
             * Lastly the last asterisk on the left is used to dereference the pointer
            */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK_VALUE;

            /* Set the Commit bit of the corresponding pin in Commit register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[Id].pinNum);
        }

        /*
         * Check if requested Pins are the JTAG Ones
         * if so, do nothing
        */
        else if( (Port_Channels[Id].portNum == PORTC) && (Port_Channels[Id].pinNum <= PORT_C_PIN_3_JTAG) )
        {
            /* DO Nothing, these are JTAG Pins */

            /* Continue used because this iteration is not a valid one so that i need to go to the next one */

        }
        else
        {
           /* Do nothing, no need to unlock the commit register */
        }


        /* Check for Pin Direction */
        if(Direction == PORT_PIN_OUT)
        {
            /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);
        }
        else if (Direction == PORT_PIN_IN)
        {
            /* Clear the corresponding bit in the GPIODIR register to configure it as output pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Pin);
        }
    }
    else
    {
        /* Do nothing, there is an error and reported by DET if it was enabled */
    }
}
#endif


/************************************************************************************
* Service Name:          Port_RefreshPortDirection
* Service ID[hex]:       0x02
* Sync/Async:            Synchronous
* Reentrancy:            Non-Reentrant
* Parameters (in):       None
* Parameters (inout):    None
* Parameters (out):      None
* Return value:          None
* Description:           Function used to refresh the direction of all
*                        configured ports to configured direction
************************************************************************************/

void Port_RefreshPortDirection(void)
{
    /* Pointer to Requested Port Register */
    volatile uint32* PortGpio_Ptr = NULL_PTR;

    /* Variable to hold Error status */
    boolean error = FALSE;

    /* Variable used to loop on the array of structure */
    uint8 counter = 0;

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* Check if this function is called before initialization the Port Module */
    if(PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Port Module doesn't initialized yet, report an PORT_E_UNINIT DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);

        /* Set error variable to True */
        error = TRUE;
    }

    else
    {
        /* Do nothing, Pin direction is changeable */
    }
/*
 * Here you can see #endif is put after else so that if DET Error disabled through tool
 * i won't have a bug here said "else without previous if"
 */
#endif

    if(FALSE == error)
    {
        /*
         * Loop through all array structure elements to refresh them
         * with the configured direction for them
        */
        for(counter = 0; counter <= PORT_CONFIGURED_CHANNLES; counter++)
        {
            switch(Port_Channels[counter].portNum)
             {
             case PORTA:

                 /* Point the pointer to PORTA Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;

             break;

             case PORTB:

                 /* Point the pointer to PORTB Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;

             break;

             case PORTC:

                 /* Point the pointer to PORTC Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;

             break;

             case PORTD:

                 /* Point the pointer to PORTD Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;

             break;

             case PORTE:

                 /* Point the pointer to PORTE Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;

             break;

             case PORTF:

                 /* Point the pointer to PORTF Base Address */
                 PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;

             break;
             }

             /*
              * Check if requested Pins are the Locked ones (PF0 or PD7)
              * If so, start unlock procedure to set the corresponding configurations to them
             */
             if( ( (Port_Channels[counter].portNum == PORTD) && (Port_Channels[counter].pinNum == PORT_D_PIN_7) ) || \
                 ( (Port_Channels[counter].portNum == PORTF) && (Port_Channels[counter].pinNum == PORT_F_PIN_0) ) )
             {
                 /* First, Unlock the LOCK Register by setting it with its Unlock value */

                 /*
                  * First, PortGpio_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
                  * because if it is not type casted, adding Lock Register offset will make it
                  * PORT_LOCK_REG_OFFSET value * 4 because it will behave as uint32*,
                  * so it is a must to type cast the base address to uint8*
                  *
                  * Second the whole pointer is type casted again to uint32*
                  * Lastly the last asterisk on the left is used to dereference the pointer
                 */
                 *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK_VALUE;

                 /* Set the Commit bit of the corresponding pin in Commit register */
                 SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[counter].pinNum);
             }

             /*
              * Check if requested Pins are the JTAG Ones
              * if so, do nothing
             */
             else if( (Port_Channels[counter].portNum == PORTC) && (Port_Channels[counter].pinNum <= PORT_C_PIN_3_JTAG) )
             {
                 /* DO Nothing, these are JTAG Pins */

                 /* Continue used because this iteration is not a valid one so that i need to go to the next one */
                 continue;
             }
             else
             {
                /* Do nothing, no need to unlock the commit register */
             }


            /* Check if the Pin direction is changeable or not */
            if(Port_Channels[counter].pinDirection_Changeable == PIN_DIRECTION_CHANGEABILITY_ON)
            {
                /* Check for Pin Direction */
                if(Port_Channels[counter].direction == PORT_PIN_OUT)
                {
                    /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);
                }
                else if (Port_Channels[counter].direction == PORT_PIN_IN)
                {
                    /* Clear the corresponding bit in the GPIODIR register to configure it as output pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , Port_Channels[counter].pinNum);
                }
            }
            else
            {
                    /* Do nothing, This pin direction is unchangeable during run time */
            }
        }
    }
    else
    {
        /* Do nothing, there is an error and reported by DET if it was enabled */
    }

}


/************************************************************************************
* Service Name:         Port_GetVersionInfo
* Service ID[hex]:      0x03
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      None
* Parameters (inout):   None
* Parameters (out):     VersionInfo - Pointer to where to store the version information of this module.
* Return value:         None
* Description:          Function to get the version information of this module.
* Note:                 This function can be deleted if
*                       PORT_VERSION_INFO_API != STD_ON
************************************************************************************/


/* check if Port_GetVersionAPI is selected from the tool */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
/* Check if DET Error is selected from the tool */
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if(NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    }
    else
    {
        /* Do nothing */
    }
    /* Check if this function is called before initialization the Port Module */
    if(PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Port Module doesn't initialized yet, report an PORT_E_UNINIT DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
    }

    else
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software 4Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
#endif


/************************************************************************************
* Service Name:         Port_SetPinMode
* Service ID[hex]:      0x04
* Sync/Async:           Synchronous
* Reentrancy:           Reentrant
* Parameters (in):      Pin     - Port Pin ID Number
*                       Mode    - New Port pin Mode to be set in port pin
* Parameters (inout):   None
* Parameters (out):     None
* Return value:         None
* Description:          Function used to set port pin mode during run time
************************************************************************************/

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
    /* Pointer to Requested Port Register */
    volatile uint32* PortGpio_Ptr = NULL_PTR;

    /* Variable to hold Error status */
    boolean error = FALSE;

    /* Variable used to loop on the array of structure */
    uint8 counter = 0;

    /*
     * Variable used to save the index of the array element needed
     * initialized with 60 because its value should be changed if
     * the pin parameter of the function is correct
    */
    uint8 Id = 60;

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* Check if this function is called before initialization the Port Module */
    if(PORT_NOT_INITIALIZED == Port_Status)
    {
        /* Port Module doesn't initialized yet, report a PORT_E_UNINIT DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing */
    }
#endif

    for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
    {
        if(Port_Channels[counter].pinNum == Pin)
        {
            Id = 0;

            /* Save the Array index */
            Id = counter;

            /* Get out of the Loop */
            break;
        }
    }

    /* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check for incorrect PortPin ID Passed */
    if(Id == 60 )
    {
        /* Incorrect Pin ID passed after looping all the array, report a PORT_E_PARAM_PIN DET Error */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing */
    }

    /* Check if the mode is invalid */
    if(Mode > PORT_D_PIN_4_USB0DP)
    {
        /*
         * PORT_D_PIN_4_USB0DP is the biggest value in my enum
         * if the mode is bigger than that then its value is invalid
        */

        /* Report a PORT_E_PARAM_INVALID_MODE */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing */
    }

    /*
     * Check if Mode is unchangeable or not
     * if that, then report a DET Error
    */
    if(Port_Channels[Id].pinMode_Changeable == PIN_MODE_CHANGEABILITY_OFF)
    {
        /* Mode is unchangeable, report a PORT_E_MODE_UNCHANGEABLE */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);

        /* Set error variable to True */
        error = TRUE;
    }
    else
    {
        /* Do nothing */
    }
#endif

    if(FALSE == error)
    {
        switch(Port_Channels[Id].portNum)
        {
        case PORTA:

            /* Point the pointer to PORTA Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;

        break;

        case PORTB:

            /* Point the pointer to PORTB Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;

        break;

        case PORTC:

            /* Point the pointer to PORTC Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;

        break;

        case PORTD:

            /* Point the pointer to PORTD Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;

        break;

        case PORTE:

            /* Point the pointer to PORTE Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;

        break;

        case PORTF:

            /* Point the pointer to PORTF Base Address */
            PortGpio_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;

        break;
        }

        /*
         * Check if requested Pins are the Locked ones (PF0 or PD7)
         * If so, start unlock procedure to set the corresponding configurations to them
        */
        if( ( (Port_Channels[Id].portNum == PORTD) && (Port_Channels[Id].pinNum == PORT_D_PIN_7) ) || \
            ( (Port_Channels[Id].portNum == PORTF) && (Port_Channels[Id].pinNum == PORT_F_PIN_0) ) )
        {
            /* First, Unlock the LOCK Register by setting it with its Unlock value */

            /*
             * First, PortGpio_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
             * because if it is not type casted, adding Lock Register offset will make it
             * PORT_LOCK_REG_OFFSET value * 4 because it will behave as uint32*,
             * so it is a must to type cast the base address to uint8*
             *
             * Second the whole pointer is type casted again to uint32*
             * Lastly the last asterisk on the left is used to dereference the pointer
            */
            *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = LOCK_REGISTER_UNLOCK_VALUE;

            /* Set the Commit bit of the corresponding pin in Commit register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , Port_Channels[Id].pinNum);
        }

        /*
         * Check if requested Pins are the JTAG Ones
         * if so, do nothing
        */
        else if( (Port_Channels[Id].portNum == PORTC) && (Port_Channels[Id].pinNum <= PORT_C_PIN_3_JTAG) )
        {
            /* DO Nothing, these are JTAG Pins */

            /* Continue used because this iteration is not a valid one so that i need to go to the next one */

        }
        else
        {
           /* Do nothing, no need to unlock the commit register */
        }

        /*
         * Check if Analog mode Selected or Not
         * ANALOG_MODE_SELECTED     = 15 -> ADC
        */
        if( (Mode == ANALOG_MODE_SELECTED) )
        {
           /*
            * Analog Mode Selected
            * Start Analog Mode initiation Procedures
           */

            /* 1- Set AFSEL (Alternative Function Selection) Bit corresponding to the Pin Number */
            SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[Id].pinNum );

            /* 2- Clear DEN (Digital Enable) Bit corresponding to the pin number */
            CLEAR_BIT( *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[Id].pinNum);

            /* 3- Set AMSEL (Analog Mode Selection) Bit Corresponding to the pin number */
            SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Channels[Id].pinNum );
        }
        else
        {
            /*
             * Normal Digital Mode
             * Start Digital Mode initiation procedure
            */

            /* 1- Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Channels[Id].pinNum);

            /* Check if Alternative function selected or not*/
            if(Mode == DIO_PIN)
            {
                /*
                 * Alternative function not selected
                 * Pin Configured as Normal PORT
                */

                /* 2- Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Channels[Id].pinNum);

                /* 3- Clear the PMCx bits for this pin */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << ( (Port_Channels[Id].pinNum) * 4));

            }

            else
            {
                /* Alternative function selected */

                /* 2- Set AFSEL (Alternative Function Selection) Bit corresponding to the Pin Number */
                SET_BIT( *(volatile uint32*)((volatile uint8*)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET), Port_Channels[Id].pinNum );

                /*
                 * 3- Set the PMCx bits for this pin
                 * First, get the mode selected from the Structure
                 * Then left shift it with PinNum *4
                 * because every pin has 4 bits of configurations
                */
                *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= ( (Port_Channels[Id].mode) << ( (Port_Channels[Id].pinNum) * 4) );

            }

        }

        /* Check if Analog mode is not selected to enable the digital feature */
        if( !(Mode == ANALOG_MODE_SELECTED) )
        {
            /* Digital Mode Selected */

            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , Port_Channels[Id].pinNum);
        }


    }
    else
    {
        /* Do nothing, there is an error and reported by DET if DET is Enabled */
    }

}







