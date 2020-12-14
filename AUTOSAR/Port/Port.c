/******************************************************************************
 *
 * Module:      Port
 *
 * File Name:   Port.c
 *
 * Description: Source file for Port Module APIs on STM32F4
 * 				Microcontroller Family - Port Driver
 *
 * Version      1.0.0
 *
 * Author:      Islam Ehab
 *
 * Date:        13/12/2020
 ******************************************************************************/

/*******************************************************************************
 *
 * @file        Port
 *
 * @brief       Source file for Port Module APIs on STM32F4
 * 				Microcontroller Family - Port Driver
 *
 * @version     1.0.0
 *
 * @author      Islam Ehab
 *
 * @date        13/12/2020
 *
 *******************************************************************************/


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

/**************************************************************************
 * 					Static Global Functions Prototype				 	  *
***************************************************************************/

STATIC void Port_RegInit(void);

/**************************************************************************/


/**************************************************************************
 * 					Static Global Variable Definition				 	  *
***************************************************************************/
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
/**************************************************************************/

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
	/*
	 * Pointer to Requested Port Register
	 * Note: Type of Pointer is GPIO_REG which is a structure
	 * holds all GPIO registers with their offsets by saving them
	 * in the struct with their arrangement in the data sheet
	*/
	volatile GPIO_REG* PortGpio_Ptr = NULL_PTR;

	/* Variable to waste time to ensure clock stability */
	volatile uint32  delay = 0;

	/* Variable to iterate on it */
	uint8 counter = 0;

	/* Check if DET Error is enabled or not through configuration tool */
#if(PORT_DEV_ERROR_DETECT == STD_ON)

	/* Check if the input configuration pointer to structure is Not a Null Pointer (wrong Parameter) */
	if(NULL_PTR == ConfigPtr)
	{
		/* ConfigPtr is a Null Pointer, Report a DET Error as a PORT_E_INIT_FAILED */
		Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID, PORT_E_INIT_FAILED);

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

		/* Initiate All Ports Registers before using them */
		Port_RegInit();

		/* For Loop to iterate through Channels */
		for(counter = 0; counter < PORT_CONFIGURED_CHANNLES; counter++)
		{

			switch(Port_Channels[counter].portNum)
			{
			/* Point the pointer to PORTA Base Address */
			case PORTA:	PortGpio_Ptr = GPIO_PORTA_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTB Base Address */
			case PORTB:	PortGpio_Ptr = GPIO_PORTB_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTC Base Address */
			case PORTC:	PortGpio_Ptr = GPIO_PORTC_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTD Base Address */
			case PORTD:	PortGpio_Ptr = GPIO_PORTD_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTE Base Address */
			case PORTE:	PortGpio_Ptr = GPIO_PORTE_BASE_ADDRESS;
			break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429

			/* Point the pointer to PORTF Base Address */
			case PORTF: PortGpio_Ptr = GPIO_PORTF_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTG Base Address */
			case PORTG: PortGpio_Ptr = GPIO_PORTG_BASE_ADDRESS;
			break;
#endif
/****************************************************************************************/
			/* Point the pointer to PORTF Base Address */
			case PORTH: PortGpio_Ptr = GPIO_PORTH_BASE_ADDRESS;
			break;
			}

			/*
			 * Check if the pin is not on the default mode
			 * if it is on default mode, Nothing of GPIO Configuration sequence will happen
			 * Which means the pin will be not usable in this application
			 */
			if(Port_Channels[counter].direction != PORT_PIN_DEFAULT)
			{
				if( (Port_Channels[counter].mode == ANALOG_MODE_SELECTED) )
				{
					/*
					 * Analog Mode Selected
					 * Start Analog Mode initiation Procedures
					*/

					/*
					 * First Clear the corresponding bits then
					 * Set MODER corresponding bits for the Pin = 3
					 * as analog mode
					 * By left shift the value by the pin number * 2
					 * because every pin has 2 bits
					*/
					PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
																| ( (MODER_REGISTER_ANALOG_MODE << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) );

				}
				else
				{
					/*
					 * Normal Digital Mode
					 * Start Digital Mode initiation procedure
					 */

					/* Check if Alternative function selected or not*/
					if( (Port_Channels[counter].mode == DIO_PIN) )
					{
						/*
						 * Alternative function not selected
						 * Pin Configured as Normal PORT
						 */

						/*
						 * First Clear the corresponding bits then
						 * Set MODER corresponding bits for the Pin = 1
						 * as general purpose output
						 * By left shift the value by the pin number * 2
						 * because every pin has 2 bits
						*/
						PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
																	| ( (MODER_REGISTER_GENERAL_PURPOSE_OUT << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS)) ) );

					}

					else
					{
						/* Alternative function selected */

						/* 1- Select Alternative Function Option */
						/*
						 * First Clear the corresponding bits then
						 * Set MODER corresponding bits for the Pin = 2
						 * as general purpose output
						 * By left shift the value by the pin number * 2
						 * because every pin has 2 bits
						*/
						PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE   << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
																	| ( (MODER_REGISTER_ALTERNATIVE_FUNCTION << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) );

						/* 2- Set Alternative function selected */

						/*
						 * Check if the number of Pin is <= 7 or not
						 * if so, write its alternative function value
						 * in AFRL register
						*/
						if(Port_Channels[counter].pinNum < AFRL_REGISTER_MAX_PIN_NUM)
						{
							/* Work on AFRL Register */

							/*
							 * First Clear the corresponding bits then
							 * Set AFRL corresponding bits for the Pin by
							 * its alternative function (mode) value
							 * By left shift the value by the pin number * 4
							 * because every pin has 4 bits
							*/
							PortGpio_Ptr -> AFRL = ( ( (PortGpio_Ptr -> AFRL) & (~(AFR_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * AFR_REGISTER_BIT_NUMBERS) ) ) ) \
																		   | ( (Port_Channels[counter].mode << ( (Port_Channels[counter].pinNum) * AFR_REGISTER_BIT_NUMBERS) ) ) );
						}
						/*
						 * Then, check if the number of Pin is <= 15 or not
						 * if so, write its alternative function value
						 * in AFRL register
						*/
						else if(Port_Channels[counter].pinNum < AFRH_REGISTER_MAX_PIN_NUM)
						{
							/*
							 * Work on AFRL Register
							 * Note: you need to minus 8 from Pin number left shift by
							 * the correct pin number
							*/

							/*
							 * First Clear the corresponding bits then
							 * Set AFRH corresponding bits for the Pin by
							 * its alternative function (mode) value
							 * By left shift the value by the (pin number - 8) * 4
							 * because every pin has 4 bits
							*/
							PortGpio_Ptr -> AFRH = ( ( (PortGpio_Ptr -> AFRH) & (~(AFR_REGISTER_MASK_VALUE  << ( ( (Port_Channels[counter].pinNum) - AFRH_REGISTER_PIN_DIFFERENCE) * AFR_REGISTER_BIT_NUMBERS) ) ) ) \
																		   | ( (Port_Channels[counter].mode << ( ( (Port_Channels[counter].pinNum) - AFRH_REGISTER_PIN_DIFFERENCE) * AFR_REGISTER_BIT_NUMBERS) ) ) );

						}
						else
						{
							/* Do nothing, Pin number is wrong */
						}

					}
				}

				/* Set Output speed from the structure */
				/*
				 * First Clear the corresponding bits then
				 * Set OSPEEDR corresponding bits for the Pin by its Speed value
				 * By left shift the value by the (pin number) * 2
				 * because every pin has 2 bits
				*/
				PortGpio_Ptr -> OSPEEDR = ( ( (PortGpio_Ptr -> OSPEEDR) & (~(OSPEEDR_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * OSPEEDR_REGISTER_BIT_NUMBERS) ) ) ) \
						   	   	   	   	   	   	   	   	   	   	   	   	| ( (Port_Channels[counter].speed << ( (Port_Channels[counter].pinNum) * OSPEEDR_REGISTER_BIT_NUMBERS) ) ) );



				/* Check if Pin Input or Output */
				if(Port_Channels[counter].direction == PORT_PIN_OUT)
				{
					/* Output Pin Selected */

					/* Set Output Type from the structure */

					/*
					 * First Clear the corresponding bits then
					 * Set OTYPER corresponding bits for the Pin by its
					 * Output type value (Push Pull = 0 or Open Drain = 1)
					 * By left shift the value by the (pin number)
					*/
					PortGpio_Ptr -> OTYPER = ( ( (PortGpio_Ptr -> OTYPER) & (~(OTYPER_REGISTER_MASK_VALUE   << ( (Port_Channels[counter].pinNum) ) ) ) ) \
							   	   	   	   	   	   	   	   	   	   	 | ( (Port_Channels[counter].outputType << ( (Port_Channels[counter].pinNum) ) ) ) );

					/* Check for Initial Value */
					if(Port_Channels[counter].initialValue == INITIAL_VALUE_HIGH)
					{
						/*
						 * Set the corresponding bit initial value = 1
						 * By setting the corresponding bit in BSSR (Least significant 16 bits)
						*/
						SET_BIT( (PortGpio_Ptr -> BSRRL), Port_Channels[counter].pinNum);
					}
					else
					{
						/*
						 * Set the corresponding bit initial value = 0
						 * By setting the corresponding bit in BSSR (Most significant 16 bits)
						*/
						SET_BIT( (PortGpio_Ptr -> BSRRH), Port_Channels[counter].pinNum);

					}


				}
				else if (Port_Channels[counter].direction == PORT_PIN_IN)
				{
					/* Input Pin Selected */

					/* Clear the corresponding bit in the MODER register to configure it as input pin */
					PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) );

					/* Internal resistor Selection */

					/*
					 * First Clear the corresponding bits then
					 * Set PUDR corresponding bits for the Pin by
					 * its internal resistor value
					 * (Off = 0, Pull up = 1, Pull down = 2)
					 * then left shift the value by the (pin number) * 2
					 * because every pin has 2 bits
					*/
					PortGpio_Ptr -> PUPDR = ( ( (PortGpio_Ptr -> PUDR) & (~(PUDR_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * PUDR_REGISTER_BIT_NUMBERS) ) ) ) \
	   	   	   	   	   	   	   	   	   							 | ( (Port_Channels[counter].resistor << ( (Port_Channels[counter].pinNum) * PUDR_REGISTER_BIT_NUMBERS) ) ) );

				}
				else
				{
					/* Do nothing  */
				}

			}
			else
			{
				/*
				 *  This else for the first if in the loop
				 * if the flow goes here, then the pin is not used
				 * then nothing will happen to this pin (as GPIO Configurations)
				 * It should go to initial value (Reset value from Data sheet)
				 * Which should have gone to it at first
				 * when calling Port_RegInit() Static API
				 */

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
/************************************************************************************
 * @fn 	  	void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
 * @brief 	Function that sets the port pin direction
 * @note	This function can be deleted if
 *			PORT_SET_PIN_DIRECTION_API != STD_ON
 * @note  	Service ID[hex]: 0x02
 * @note  	Reentrancy:		 Reentrant
 * @note: 	Sync/Async: 	 Synchronous
 * @return	None
 * @note  	Return Value:	 None
 * @param	(in): Pin        - Port Pin ID Number
 * @param   (in): Direction  - Port Pin Direction
 ************************************************************************************/

/* check if Port_GetVersionAPI is selected from the tool */
#if(PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(Port_PinType Pin, Port_PinDirectionType Direction)
{
	/*
	 * Pointer to Requested Port Register
	 * Note: Type of Pointer is GPIO_REG which is a structure
	 * holds all GPIO registers with their offsets by saving them
	 * in the struct with their arrangement in the data sheet
	*/
	volatile GPIO_REG* PortGpio_Ptr = NULL_PTR;

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
		/* Point the pointer to PORTA Base Address */
		case PORTA:	PortGpio_Ptr = GPIO_PORTA_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTB Base Address */
		case PORTB:	PortGpio_Ptr = GPIO_PORTB_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTC Base Address */
		case PORTC:	PortGpio_Ptr = GPIO_PORTC_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTD Base Address */
		case PORTD:	PortGpio_Ptr = GPIO_PORTD_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTE Base Address */
		case PORTE:	PortGpio_Ptr = GPIO_PORTE_BASE_ADDRESS;
		break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429

		/* Point the pointer to PORTF Base Address */
		case PORTF: PortGpio_Ptr = GPIO_PORTF_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTG Base Address */
		case PORTG: PortGpio_Ptr = GPIO_PORTG_BASE_ADDRESS;
		break;
#endif
/****************************************************************************************/
		/* Point the pointer to PORTF Base Address */
		case PORTH: PortGpio_Ptr = GPIO_PORTH_BASE_ADDRESS;
		break;
		}

		/* Check for Pin Direction */
		if(Direction == PORT_PIN_OUT)
		{
			/* Output Pin Direction Selected */

			/*
			 * First Clear the corresponding bits then
			 * Set MODER corresponding bits for the Pin = 1
			 * as general purpose output
			 * By left shift the value by the pin number * 2
			 * because every pin has 2 bits
			*/
			PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Pin) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
														| ( (MODER_REGISTER_GENERAL_PURPOSE_OUT << ( (Pin) * MODER_REGISTER_BIT_NUMBERS)) ) );
		}
		else if (Direction == PORT_PIN_IN)
		{
			/*
			 * Clear the corresponding bits in
			 * MODER because its an input pin
			*/
			PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Pin) * MODER_REGISTER_BIT_NUMBERS) ) ) ) );

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
/***********************************************************************************
 * @fn 	  	void Port_RefreshPortDirection(void)
 * @brief 	Function used to refresh the direction of all
 * 			configured ports to configured direction
 * @note  	Service ID[hex]: 0x02
 * @note  	Reentrancy:		Non-Reentrant
 * @note: 	Sync/Async: 	Synchronous
 * @return	None
 * @note  	Return Value:	None
 * @param	None
 ***********************************************************************************/

void Port_RefreshPortDirection(void)
{
	/*
	 * Pointer to Requested Port Register
	 * Note: Type of Pointer is GPIO_REG which is a structure
	 * holds all GPIO registers with their offsets by saving them
	 * in the struct with their arrangement in the data sheet
	*/
	volatile GPIO_REG* PortGpio_Ptr = NULL_PTR;


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
			/* Point the pointer to PORTA Base Address */
			case PORTA:	PortGpio_Ptr = GPIO_PORTA_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTB Base Address */
			case PORTB:	PortGpio_Ptr = GPIO_PORTB_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTC Base Address */
			case PORTC:	PortGpio_Ptr = GPIO_PORTC_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTD Base Address */
			case PORTD:	PortGpio_Ptr = GPIO_PORTD_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTE Base Address */
			case PORTE:	PortGpio_Ptr = GPIO_PORTE_BASE_ADDRESS;
			break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429

			/* Point the pointer to PORTF Base Address */
			case PORTF: PortGpio_Ptr = GPIO_PORTF_BASE_ADDRESS;
			break;

			/* Point the pointer to PORTG Base Address */
			case PORTG: PortGpio_Ptr = GPIO_PORTG_BASE_ADDRESS;
			break;
#endif
/****************************************************************************************/
			/* Point the pointer to PORTF Base Address */
			case PORTH: PortGpio_Ptr = GPIO_PORTH_BASE_ADDRESS;
			break;
			}

			/* Check if the Pin direction is changeable or not */
			if(Port_Channels[counter].pinDirection_Changeable == PIN_DIRECTION_CHANGEABILITY_ON)
			{
				/* Check for Pin Direction */
				if(Port_Channels[counter].direction == PORT_PIN_OUT)
				{
					/* Set the corresponding bit in BSRRL Register to Set the Pin */
					SET_BIT( (PortGpio_Ptr -> BSRRL),  Port_Channels[counter].pinNum);
				}
				else if (Port_Channels[counter].direction == PORT_PIN_IN)
				{
					/* Set the corresponding bit in BSRRH Register to Clear the Pin */
					SET_BIT( (PortGpio_Ptr -> BSRRH),  Port_Channels[counter].pinNum);
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
/***********************************************************************************
 * @fn 	  	void Port_GetVersionInfo(Std_VersionInfoType *versioninfo)
 * @brief 	Function to get the version information of this module.
 * @note:   This function can be deleted if PORT_VERSION_INFO_API != STD_ON
 * @note  	Service ID[hex]: 0x03
 * @note  	Reentrancy:		 Reentrant
 * @note: 	Sync/Async:      Synchronous
 * @return	None
 * @note  	Return Value:	 None
 * @param (out): VersionInfo - Pointer to where to store the version information of this module.
 ***********************************************************************************/

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
/***********************************************************************************
 * @fn 	  	void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
 * @brief 	Function used to set port pin mode during run time
 * @note  	Service ID[hex]: 0x04
 * @note  	Reentrancy:		 Reentrant
 * @note: 	Sync/Async: Synchronous
 * @return	None
 * @note  	Return Value: None
 * @param   (in): Pin     - Port Pin ID Number
 * @param   (in): Mode    - New Port pin Mode to be set in port pin
 ***********************************************************************************/

void Port_SetPinMode(Port_PinType Pin, Port_PinModeType Mode)
{
	/*
	 * Pointer to Requested Port Register
	 * Note: Type of Pointer is GPIO_REG which is a structure
	 * holds all GPIO registers with their offsets by saving them
	 * in the struct with their arrangement in the data sheet
	*/
	volatile GPIO_REG* PortGpio_Ptr = NULL_PTR;


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
	if(Id > MAX_NUM_OF_PINS )
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
	if(Mode > DIO_PIN)
	{
		/*
		 * DIO_PIN is the biggest value in my enum
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
		/* Point the pointer to PORTA Base Address */
		case PORTA:	PortGpio_Ptr = GPIO_PORTA_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTB Base Address */
		case PORTB:	PortGpio_Ptr = GPIO_PORTB_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTC Base Address */
		case PORTC:	PortGpio_Ptr = GPIO_PORTC_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTD Base Address */
		case PORTD:	PortGpio_Ptr = GPIO_PORTD_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTE Base Address */
		case PORTE:	PortGpio_Ptr = GPIO_PORTE_BASE_ADDRESS;
		break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429

		/* Point the pointer to PORTF Base Address */
		case PORTF: PortGpio_Ptr = GPIO_PORTF_BASE_ADDRESS;
		break;

		/* Point the pointer to PORTG Base Address */
		case PORTG: PortGpio_Ptr = GPIO_PORTG_BASE_ADDRESS;
		break;
#endif
/****************************************************************************************/
		/* Point the pointer to PORTH Base Address */
		case PORTH: PortGpio_Ptr = GPIO_PORTH_BASE_ADDRESS;
		break;
		}

		/*
		 * Check if Analog mode Selected or Not
		 * ANALOG_MODE_SELECTED     = 16 -> ADC
		 */
		if( (Mode == ANALOG_MODE_SELECTED) )
		{
			/*
			 * Analog Mode Selected
			 * Start Analog Mode initiation Procedures
			*/

			/*
			 * First Clear the corresponding bits then
			 * Set MODER corresponding bits for the Pin = 3
			 * as analog mode
			 * By left shift the value by the pin number * 2
			 * because every pin has 2 bits
			*/
			PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
														| ( (MODER_REGISTER_ANALOG_MODE << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) );

		}
		else
		{
			/*
			 * Normal Digital Mode
			 * Start Digital Mode initiation procedure
			 */

			/* Check if Alternative function selected or not*/
			if(Mode == DIO_PIN)
			{
				/*
				 * Alternative function not selected
				 * Pin Configured as Normal PORT
				 */

				/*
				 * First Clear the corresponding bits then
				 * Set MODER corresponding bits for the Pin = 1
				 * as general purpose output
				 * By left shift the value by the pin number * 2
				 * because every pin has 2 bits
				*/
				PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
															| ( (MODER_REGISTER_GENERAL_PURPOSE_OUT << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS)) ) );

			}

			else
			{
				/* Alternative function selected */

				/* 1- Select Alternative Function Option */
				/*
				 * First Clear the corresponding bits then
				 * Set MODER corresponding bits for the Pin = 2
				 * as general purpose output
				 * By left shift the value by the pin number * 2
				 * because every pin has 2 bits
				*/
				PortGpio_Ptr -> MODER = ( ( (PortGpio_Ptr -> MODER) & (~(MODER_REGISTER_MASK_VALUE   << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) ) \
															| ( (MODER_REGISTER_ALTERNATIVE_FUNCTION << ( (Port_Channels[counter].pinNum) * MODER_REGISTER_BIT_NUMBERS) ) ) );

				/* 2- Set Alternative function selected */

				/*
				 * Check if the number of Pin is <= 7 or not
				 * if so, write its alternative function value
				 * in AFRL register
				*/
				if(Port_Channels[counter].pinNum < AFRL_REGISTER_MAX_PIN_NUM)
				{
					/* Work on AFRL Register */

					/*
					 * First Clear the corresponding bits then
					 * Set AFRL corresponding bits for the Pin by
					 * its alternative function (mode) value
					 * By left shift the value by the pin number * 4
					 * because every pin has 4 bits
					*/
					PortGpio_Ptr -> AFRL = ( ( (PortGpio_Ptr -> AFRL) & (~(AFR_REGISTER_MASK_VALUE  << ( (Port_Channels[counter].pinNum) * AFR_REGISTER_BIT_NUMBERS) ) ) ) \
																   | ( (Port_Channels[counter].mode << ( (Port_Channels[counter].pinNum) * AFR_REGISTER_BIT_NUMBERS) ) ) );
				}
				/*
				 * Then, check if the number of Pin is <= 15 or not
				 * if so, write its alternative function value
				 * in AFRL register
				*/
				else if(Port_Channels[counter].pinNum < AFRH_REGISTER_MAX_PIN_NUM)
				{
					/*
					 * Work on AFRL Register
					 * Note: you need to minus 8 from Pin number left shift by
					 * the correct pin number
					*/

					/*
					 * First Clear the corresponding bits then
					 * Set AFRH corresponding bits for the Pin by
					 * its alternative function (mode) value
					 * By left shift the value by the (pin number - 8) * 4
					 * because every pin has 4 bits
					*/
					PortGpio_Ptr -> AFRH = ( ( (PortGpio_Ptr -> AFRH) & (~(AFR_REGISTER_MASK_VALUE  << ( ( (Port_Channels[counter].pinNum) - AFRH_REGISTER_PIN_DIFFERENCE) * AFR_REGISTER_BIT_NUMBERS) ) ) ) \
																   | ( (Port_Channels[counter].mode << ( ( (Port_Channels[counter].pinNum) - AFRH_REGISTER_PIN_DIFFERENCE) * AFR_REGISTER_BIT_NUMBERS) ) ) );

				}
				else
				{
					/* Do nothing, Pin number is wrong */
				}
			}

		}

	}
	else
	{
		/* Do nothing, there is an error and reported by DET if DET is Enabled */
	}

}




/*****************************************************************
 * @fn 		STATIC void Port_RegInit(void)
 *
 * @brief	Function used to initialize all Ports Registers
 * 			with their initial Values
 *
 * @note	STATIC because it used in this file only
 * 			and it will be used in Port_Init API Only
 *
 * @param	None
 *
 * @return	None
 ****************************************************************/
STATIC void Port_RegInit(void)
{
/*------------------- Port B Registers Reset Value (init value) ---------------------*/

	GPIOA_BASE_ADDRESS -> MODER   = 0xA8000000; /* Reset value for MODER in Port   A */
	GPIOA_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset value for OTYPER in Port  A */
	GPIOA_BASE_ADDRESS -> OSPEEDR = 0x0C000000; /* Reset value for OSPEEDR in Port A */
	GPIOA_BASE_ADDRESS -> PUPDR	  = 0x64000000; /* Reset value for PUPDR in Port   A */
	GPIOA_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   A */
	GPIOA_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   A */
	GPIOA_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   A */
	GPIOA_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   A */
	GPIOA_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    A */
	GPIOA_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    A */
	GPIOA_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    A */

/*-----------------------------------------------------------------------------------*/

/*------------------- Port B Registers Reset Value (init value) ---------------------*/

	GPIOB_BASE_ADDRESS -> MODER	  = 0x00000280; /* Reset Value for MODER in Port   B */
	GPIOB_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  B */
	GPIOB_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port B */
	GPIOB_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   B */
	GPIOB_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   B */
	GPIOB_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   B */
	GPIOB_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   B */
	GPIOB_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   B */
	GPIOB_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    B */
	GPIOB_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    B */
	GPIOB_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    B */

/*-----------------------------------------------------------------------------------*/

/*------------------- Port C Registers Reset Value (init value) ---------------------*/

	GPIOC_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   C */
	GPIOC_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  C */
	GPIOC_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port C */
	GPIOC_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   C */
	GPIOC_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   C */
	GPIOC_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   C */
	GPIOC_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   C */
	GPIOC_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   C */
	GPIOC_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    C */
	GPIOC_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    C */
	GPIOC_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    C */

/*-----------------------------------------------------------------------------------*/

/*------------------- Port D Registers Reset Value (init value) ---------------------*/

	GPIOD_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   D */
	GPIOD_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  D */
	GPIOD_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port D */
	GPIOD_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   D */
	GPIOD_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   D */
	GPIOD_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   D */
	GPIOD_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   D */
	GPIOD_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   D */
	GPIOD_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    D */
	GPIOD_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    D */
	GPIOD_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    D */

/*----------------------------------------------------------------------------------*/

/*------------------- Port E Registers Reset Value (init value) --------------------*/

	GPIOE_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   E */
	GPIOE_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  E */
	GPIOE_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port E */
	GPIOE_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   E */
	GPIOE_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   E */
	GPIOE_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   E */
	GPIOE_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   E */
	GPIOE_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   E */
	GPIOE_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    E */
	GPIOE_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    E */
	GPIOE_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    E */
/*---------------------------------------------------------------------------------*/

/************** PORT F & G are available in STM32F429 not STM32F407 ****************/
#ifdef STM32F429
/*------------------- Port F Registers Reset Value (init value) ---------------------*/

	GPIOF_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   F */
	GPIOF_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  F */
	GPIOF_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port F */
	GPIOF_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   F */
	GPIOF_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   F */
	GPIOF_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   F */
	GPIOF_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   F */
	GPIOF_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   F */
	GPIOF_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    F */
	GPIOF_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    F */
	GPIOF_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    F */

/*-----------------------------------------------------------------------------------*/


/*------------------- Port G Registers Reset Value (init value) ---------------------*/

	GPIOF_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   F */
	GPIOF_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  F */
	GPIOF_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port F */
	GPIOF_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   F */
	GPIOF_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   F */
	GPIOF_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   F */
	GPIOF_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   F */
	GPIOF_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   F */
	GPIOF_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    F */
	GPIOF_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    F */
	GPIOF_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    F */

/*-----------------------------------------------------------------------------------*/
#endif
/*************************************************************************************/

/*------------------- Port H Registers Reset Value (init value) ---------------------*/

	GPIOH_BASE_ADDRESS -> MODER   = 0x00000000;	/* Reset value for MODER in Port   H */
	GPIOH_BASE_ADDRESS -> OTYPER  = 0x00000000; /* Reset Value for OTYPER in Port  H */
	GPIOH_BASE_ADDRESS -> OSPEEDR = 0x00000000; /* Reset value for OSPEEDR in Port H */
	GPIOH_BASE_ADDRESS -> PUPDR	  = 0x00000100; /* Reset value for PUPDR in Port   H */
	GPIOH_BASE_ADDRESS -> IDR	  = 0x00000000; /* Reset value for IDR in Port 	   H */
	GPIOH_BASE_ADDRESS -> ODR	  = 0x00000000; /* Reset value for ODR in Port 	   H */
	GPIOH_BASE_ADDRESS -> BSRRL	  = 0x00000000; /* Reset value for BSRRL in Port   H */
	GPIOH_BASE_ADDRESS -> BSRRH	  = 0x00000000; /* Reset value for BSRRH in Port   H */
	GPIOH_BASE_ADDRESS -> LCKR	  = 0x00000000; /* Reset value for LCKR in Port    H */
	GPIOH_BASE_ADDRESS -> AFRL 	  = 0x00000000; /* Reset value for AFRL in Port    H */
	GPIOH_BASE_ADDRESS -> AFRH 	  = 0x00000000; /* Reset value for AFRH in Port    H */

/*---------------------------------------------------------------------------------*/

}




