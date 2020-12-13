/******************************************************************************
 *
 * Module: 		Dio
 *
 * File Name: 	Dio.c
 *
 * Description: Source file for STM32F429 Microcontroller - Dio Driver
 *
 * Author: 		Islam Ehab
 *
 * Date:		12/12/2020
 *
 * Note:	- Dio_Init API is no longer available on AUTOSAR DIO Version 4.3.1
 * 	    	- This Driver should be compatible with STM32F429 & STM32F407
 * 			- This driver does NOT Tested Yet on STM32F429 or STM32F407 HW Kits
 ******************************************************************************/

/*******************************************************************************
 * @file:	Dio.c
 *
 * @brief:	Source file for STM32F429 Microcontroller - Dio Driver
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 *
 * @note: 	Dio_Init API is no longer available on AUTOSAR DIO Version 4.3.1
 *
 * @note:   This Driver should be compatible with STM32F429 & STM32F407
 *
 * @note:   This driver does NOT Tested Yet on STM32F429 or STM32F407 HW Kits
 ******************************************************************************/

#include <Dio_Reg.h>
#include "Dio.h"

#if (DIO_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Dio Modules */
#if ((DET_AR_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
		|| (DET_AR_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
		|| (DET_AR_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Dio_ConfigChannel * Dio_PortChannels = Dio_Configuration.Channels;

/*** Note: Dio_Init API is no longer available on AUTOSAR DIO Version 4.3.1 ***/


/************************************************************************************
 * Service Name: Dio_ReadChannel
 * Service ID[hex]: 0x00
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to return the value of the specified DIO channel.
 ************************************************************************************/
/***********************************************************************************
 * @fn 	  	Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
 * @brief 	Function to return the value of the specified DIO channel.
 * @note  	Service ID[hex]: 0x00
 * @note  	Reentrancy: 	 Reentrant
 * @note: 	Sync/Async: 	 Synchronous
 * @return					 Level of the channel
 * @note  	Return Value: 	 Dio_LevelType
 * @param   (in): ChannelId - ID of DIO channel.
 ***********************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean error = FALSE;

	/* output variable to read channel value */
	uint8 output = 0;


#if (DIO_DEV_ERROR_DETECT == STD_ON)

	/*
	 * Check if the Driver is initialized before using this function
	 * This Error not a DET on but it will be reported with DET
	 * Note: This Error detection is removed in AUTOSAR 4.3.1
	*/


	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/* Check if the given Port is within specified values */
	if ( PORTH < Dio_PortChannels[ChannelId].Port_Num )
	{
		/* Port Given is more than specified on This HW, Report a DIO_E_PARAM_INVALID_PORT_ID DET Error */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_PORT_ID);

		/* Set Error variable to true */
		error = TRUE;
	}
	else
	{
		/* No Action needed */
	}

#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
		case PORTA:    Port_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;
		break;
		case PORTB:    Port_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;
		break;
		case PORTC:    Port_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;
		break;
		case PORTD:    Port_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;
		break;
		case PORTE:    Port_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
		break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429
		case PORTF:    Port_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
		break;
		case PORTG:    Port_Ptr = (volatile uint32*)GPIO_PORTG_BASE_ADDRESS;
		break;
#endif
/****************************************************************************************/

		case PORTH:    Port_Ptr = (volatile uint32*)GPIO_PORTH_BASE_ADDRESS;
		break;
		}

		/* Get Bit value from Input register */


        /*
		 * First, Port_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
		 * because if it is not type casted, adding Lock Register offset will make it
		 * DIO_INPUT_DATA_REGISTER_OFFSET value * 4 because it will behave as uint32*,
		 * so it is a must to type cast the base address to uint8*
		 *
		 * Second the whole pointer is type casted again to uint32*
		 * Lastly the last asterisk on the left is used to dereference the pointer
	    */

		/* Check if the bit value is High */
		if(BIT_IS_SET(*(volatile uint32*)((volatile uint8*)Port_Ptr + DIO_INPUT_DATA_REGISTER_OFFSET), Dio_PortChannels[ChannelId].Ch_Num) )
		{
			/* Bit value is high, save its value on output variable */
			output = STD_HIGH;
		}
		else
		{
			/* Bit value is low, save its value on output variable */
			output = STD_LOW;
		}
	}
	else
	{
		/* No Action Required */
	}

	/* Return Channel Value */
	return output;

}

/************************************************************************************
 * Service Name: Dio_WriteChannel
 * Service ID[hex]: 0x01
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 *                  Level - Value to be written.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: None
 * Description: Function to set a level of a channel.
 ************************************************************************************/
/***********************************************************************************
 * @fn 	  	void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
 * @brief 	Function to set a level of a channel.
 * @note  	Service ID[hex]:	0x01
 * @note: 	Sync/Async: 		Synchronous
 * @note  	Reentrancy:			Reentrant
 * @return	None
 * @note  	Return Value:		None
 * @param	 (in): ChannelId - ID of DIO channel.
 * @param	 (in): Level - Value to be written.
 ***********************************************************************************/
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean error = FALSE;

#if (DIO_DEV_ERROR_DETECT == STD_ON)

	/*
	 * Check if the Driver is initialized before using this function
	 * This Error not a DET on but it will be reported with DET
	 * Note: This Error detection is removed in AUTOSAR 4.3.1
	*/


	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/* Check if the given Port is within specified values */
	if ( PORTH < Dio_PortChannels[ChannelId].Port_Num )
	{
		/* Port Given is more than specified on This HW, Report a DIO_E_PARAM_INVALID_PORT_ID DET Error */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_PORT_ID);

		/* Set Error variable to true */
		error = TRUE;
	}
	else
	{
		/* No Action needed */
	}

#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
		case PORTA:    Port_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;
		break;
		case PORTB:    Port_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;
		break;
		case PORTC:    Port_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;
		break;
		case PORTD:    Port_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;
		break;
		case PORTE:    Port_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
		break;

/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429
		case PORTF:    Port_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
		break;
		case PORTG:    Port_Ptr = (volatile uint32*)GPIO_PORTG_BASE_ADDRESS;
		break;
#endif
/****************************************************************************************/

		case PORTH:    Port_Ptr = (volatile uint32*)GPIO_PORTH_BASE_ADDRESS;
		break;
		}
		if(Level == STD_HIGH)
		{
	        /*
			 * First, Port_Ptr type casted to uint8* to do the ordinary arithmetic operations on pointer
			 * because if it is not type casted, adding Lock Register offset will make it
			 * DIO_BIT_SET_REGISTER_OFFSET value * 4 because it will behave as uint32*,
			 * so it is a must to type cast the base address to uint8*
			 *
			 * Second the whole pointer is type casted again to uint32*
			 * Lastly the last asterisk on the left is used to dereference the pointer
		    */

			/* Write Logic High */
			SET_BIT( *(volatile uint32*)((volatile uint8*)Port_Ptr + DIO_BIT_SET_REGISTER_OFFSET), Dio_PortChannels[ChannelId].Ch_Num);

		}
		else if(Level == STD_LOW)
		{
			/* Write Logic Low ( By Setting the corresponding bit in BSRR Most significant 16 bits ) */
			SET_BIT( *(volatile uint32*)((volatile uint8*)Port_Ptr + DIO_BIT_CLEAR_REGISTER_OFFSET), Dio_PortChannels[ChannelId].Ch_Num );
		}
	}
	else
	{
		/* No Action Required */
	}

}



/************************************************************************************
 * Service Name: Dio_GetVersionInfo
 * Service ID[hex]: 0x12
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): None
 * Parameters (inout): None
 * Parameters (out): VersionInfo - Pointer to where to store the version information of this module.
 * Return value: None
 * Description: Function to get the version information of this module.
 ************************************************************************************/
/***********************************************************************************
 * @fn 	  	void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
 * @brief	Function to get the version information of this module.
 * @note  	Service ID[hex]: 0x12
 * @note  	Reentrancy: 	 Reentrant
 * @note: 	Sync/Async: 	 Synchronous
 * @return	None
 * @note  	Return Value: 	 None
 * @note	This function can be removed from the code if the
 * 			#define DIO_VERSION_INFO_API = STD_OFF From Dio_Cfg.h file
 * @param	(in): versioninfo - Pointer to Std_VersionInfoType struct that will fill this
 * 						  		structure with info values
 ***********************************************************************************/
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo)
{
#if (DIO_DEV_ERROR_DETECT == STD_ON)
	/* Check if input pointer is not Null pointer */
	if(NULL_PTR == versioninfo)
	{
		/* Report to DET  */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_GET_VERSION_INFO_SID, DIO_E_PARAM_POINTER);
	}
	else
#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	{
		/* Copy the vendor Id */
		versioninfo->vendorID = (uint16)DIO_VENDOR_ID;
		/* Copy the module Id */
		versioninfo->moduleID = (uint16)DIO_MODULE_ID;
		/* Copy Software Major Version */
		versioninfo->sw_major_version = (uint8)DIO_SW_MAJOR_VERSION;
		/* Copy Software Minor Version */
		versioninfo->sw_minor_version = (uint8)DIO_SW_MINOR_VERSION;
		/* Copy Software Patch Version */
		versioninfo->sw_patch_version = (uint8)DIO_SW_PATCH_VERSION;
	}
}
#endif

/************************************************************************************
 * Service Name: Dio_FlipChannel
 * Service ID[hex]: 0x11
 * Sync/Async: Synchronous
 * Reentrancy: Reentrant
 * Parameters (in): ChannelId - ID of DIO channel.
 * Parameters (inout): None
 * Parameters (out): None
 * Return value: Dio_LevelType
 * Description: Function to flip the level of a channel and return the level of the channel after flip.
 ************************************************************************************/
/***********************************************************************************
 * @fn 	  	Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
 * @brief 	Function to flip the level of a channel and return the level
 * 			of the channel after flip.
 * @note  	Service ID[hex]:	0x11
 * @note  	Reentrancy:			Reentrant
 * @note: 	Sync/Async: 		Synchronous
 * @return	None
 * @note  	Return Value: 		None
 * @param	(in): ChannelId - Holds th channel number
 ***********************************************************************************/
#if (DIO_FLIP_CHANNEL_API == STD_ON)
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId)
{
	volatile uint32 * Port_Ptr = NULL_PTR;
	boolean error = FALSE;

	/* Temp variable to get bit value */
	uint8 output = 0;


#if (DIO_DEV_ERROR_DETECT == STD_ON)

	/*
	 * Check if the Driver is initialized before using this function
	 * This Error not a DET on but it will be reported with DET
	 * Note: This Error detection is removed in AUTOSAR 4.3.1
	*/


	/* Check if the used channel is within the valid range */
	if (DIO_CONFIGURED_CHANNLES <= ChannelId)
	{

		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_CHANNEL_ID);
		error = TRUE;
	}
	else
	{
		/* No Action Required */
	}

	/*
	 * Check if the given Port is within specified values
	 * Checking with PORTH Value because it is the biggest one
	 * (Last Port available on HW)
	*/
	if ( PORTH < Dio_PortChannels[ChannelId].Port_Num )
	{
		/* Port Given is more than specified on This HW, Report a DIO_E_PARAM_INVALID_PORT_ID DET Error */
		Det_ReportError(DIO_MODULE_ID, DIO_INSTANCE_ID,
				DIO_READ_CHANNEL_SID, DIO_E_PARAM_INVALID_PORT_ID);

		/* Set Error variable to true */
		error = TRUE;
	}
	else
	{
		/* No Action needed */
	}

#endif

	/* In-case there are no errors */
	if(FALSE == error)
	{
		/* Point to the correct PORT register according to the Port Id stored in the Port_Num member */
		switch(Dio_PortChannels[ChannelId].Port_Num)
		{
		case PORTA:    Port_Ptr = (volatile uint32*)GPIO_PORTA_BASE_ADDRESS;
		break;
		case PORTB:    Port_Ptr = (volatile uint32*)GPIO_PORTB_BASE_ADDRESS;
		break;
		case PORTC:    Port_Ptr = (volatile uint32*)GPIO_PORTC_BASE_ADDRESS;
		break;
		case PORTD:    Port_Ptr = (volatile uint32*)GPIO_PORTD_BASE_ADDRESS;
		break;
		case PORTE:    Port_Ptr = (volatile uint32*)GPIO_PORTE_BASE_ADDRESS;
		break;
/************ These 2 Ports are only available on STM32F429 not in STM32F407 ************/
#ifdef STM32F429
		case PORTF:    Port_Ptr = (volatile uint32*)GPIO_PORTF_BASE_ADDRESS;
		break;
		case PORTG:    Port_Ptr = (volatile uint32*)GPIO_PORTG_BASE_ADDRESS;
		break;
#endif
/****************************************************************************************/

		break;
		case PORTH:    Port_Ptr = (volatile uint32*)GPIO_PORTH_BASE_ADDRESS;
		break;
		}

		/* Toggle Selected pin */
		TOGGLE_BIT( *(volatile uint32*)((volatile uint8*)Port_Ptr + DIO_BIT_SET_REGISTER_OFFSET), Dio_PortChannels[ChannelId].Ch_Num  );

		/* Get Bit Value after toggling */

		/* Check if the bit value is High */
		if(BIT_IS_SET(*(volatile uint32*)((volatile uint8*)Port_Ptr + DIO_INPUT_DATA_REGISTER_OFFSET), Dio_PortChannels[ChannelId].Ch_Num) )
		{
			/* Bit value is high, save its value on output variable */
			output = STD_HIGH;
		}
		else
		{
			/* Bit value is low, save its value on output variable */
			output = STD_LOW;
		}

	}

	else
	{
		/* No Action Required */
	}

	/* Return Bit value */
	return output;
}
#endif
