 /******************************************************************************
 *
 * Module: 		Dio
 *
 * File Name: 	Dio.h
 *
 * Description: Header file for STM32F429 Microcontroller - Dio Driver
 *
 * Author: 		Islam Ehab
 *
 * Date:		12/12/2020
 ******************************************************************************/
/*******************************************************************************
 * @file:	Dio.h
 *
 * @brief:	Header file for STM32F429 Microcontroller - Dio Driver
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 ******************************************************************************/
#ifndef DIO_H
#define DIO_H

/*
 * ID of Company in AUTOSAR Website
 * Islam Ehab's ID = 1024
*/
#define DIO_VENDOR_ID    (1024U)

/* Dio Module Id */
#define DIO_MODULE_ID    (120U)

/* Dio Instance Id */
#define DIO_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define DIO_SW_MAJOR_VERSION           (1U)
#define DIO_SW_MINOR_VERSION           (0U)
#define DIO_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define DIO_AR_RELEASE_MAJOR_VERSION   (4U)
#define DIO_AR_RELEASE_MINOR_VERSION   (3U)
#define DIO_AR_RELEASE_PATCH_VERSION   (1U)

/*
 * Macros for Dio Status
 */
#define DIO_INITIALIZED                (1U)
#define DIO_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Dio Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Dio Pre-Compile Configuration Header file */
#include "Dio_Cfg.h"

/* AUTOSAR Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_CFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Dio_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Dio_Cfg.h and Dio.h files */
#if ((DIO_CFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_CFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_CFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of Dio_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
/* Service ID for DIO read Channel */
#define DIO_READ_CHANNEL_SID           (uint8)0x00

/* Service ID for DIO write Channel */
#define DIO_WRITE_CHANNEL_SID          (uint8)0x01

/* Service ID for DIO read Port */
#define DIO_READ_PORT_SID              (uint8)0x02

/* Service ID for DIO write Port */
#define DIO_WRITE_PORT_SID             (uint8)0x03

/* Service ID for DIO read Channel Group */
#define DIO_READ_CHANNEL_GROUP_SID     (uint8)0x04

/* Service ID for DIO write Channel Group */
#define DIO_WRITE_CHANNEL_GROUP_SID    (uint8)0x05

/* Service ID for DIO GetVersionInfo */
#define DIO_GET_VERSION_INFO_SID       (uint8)0x12

/*
 * Service ID for DIO Init Channel
 * Note: This API is removed from DIO AUTOSAR Version 4.3.1
*/

/* Service ID for DIO flip Channel */
#define DIO_FLIP_CHANNEL_SID           (uint8)0x11

/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET code to report Invalid Channel */
#define DIO_E_PARAM_INVALID_CHANNEL_ID (uint8)0x0A

/*
 * Dio_Init API service called with NULL pointer parameter
 * Note: This DET Error is removed from DIO AUTOSAR Version 4.3.1
*/

/* DET code to report Invalid Port */
#define DIO_E_PARAM_INVALID_PORT_ID    (uint8)0x14

/* DET code to report Invalid Channel Group */
#define DIO_E_PARAM_INVALID_GROUP      (uint8)0x1F

/*
 * The API service shall return immediately without any further action,
 * beside reporting this development error.
 */
#define DIO_E_PARAM_POINTER             (uint8)0x20

/*
 * API service used without module initialization is reported using following
 * error code (Not exist in AUTOSAR 4.0.3 DIO SWS Document.
 */
#define DIO_E_UNINIT                   (uint8)0xF0
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/


/**
 * @enum    Dio_PinNumEnum
 *
 * @brief   This enum used to numbering the pins on the STM32F429
 *
 */
#ifdef STM32F429
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    DIO_PORT_A_PIN_0                = 0, 			 //!< PORT_A_PIN_0
    DIO_PORT_A_PIN_1                = 1,			 //!< PORT_A_PIN_1
    DIO_PORT_A_PIN_2                = 2,			 //!< DIO_PORT_A_PIN_2
    DIO_PORT_A_PIN_3                = 3,			 //!< DIO_PORT_A_PIN_3
    DIO_PORT_A_PIN_4                = 4, 			 //!< DIO_PORT_A_PIN_4
    DIO_PORT_A_PIN_5                = 5, 		 	 //!< DIO_PORT_A_PIN_5
    DIO_PORT_A_PIN_6                = 6, 		 	 //!< DIO_PORT_A_PIN_6
    DIO_PORT_A_PIN_7                = 7, 		     //!< DIO_PORT_A_PIN_7
    DIO_PORT_A_PIN_8				= 8,           	 //!< DIO_PORT_A_PIN_8
	DIO_PORT_A_PIN_9				= 9,             //!< DIO_PORT_A_PIN_9
	DIO_PORT_A_PIN_10				= 10,            //!< DIO_PORT_A_PIN_10
	DIO_PORT_A_PIN_11				= 11,            //!< DIO_PORT_A_PIN_11
	DIO_PORT_A_PIN_12				= 12,            //!< DIO_PORT_A_PIN_12
	DIO_PORT_A_PIN_13				= 13,            //!< DIO_PORT_A_PIN_13
	DIO_PORT_A_PIN_14				= 14,            //!< DIO_PORT_A_PIN_14
	DIO_PORT_A_PIN_15				= 15,            //!< DIO_PORT_A_PIN_15
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    DIO_PORT_B_PIN_0                = 0,			 //!< DIO_PORT_B_PIN_0
    DIO_PORT_B_PIN_1                = 1,			 //!< DIO_PORT_B_PIN_1
    DIO_PORT_B_PIN_2                = 2,			 //!< DIO_PORT_B_PIN_2
    DIO_PORT_B_PIN_3                = 3,			 //!< DIO_PORT_B_PIN_3
    DIO_PORT_B_PIN_4                = 4,			 //!< DIO_PORT_B_PIN_4
    DIO_PORT_B_PIN_5                = 5,			 //!< DIO_PORT_B_PIN_5
    DIO_PORT_B_PIN_6                = 6,			 //!< DIO_PORT_B_PIN_6
    DIO_PORT_B_PIN_7                = 7,			 //!< DIO_PORT_B_PIN_7
    DIO_PORT_B_PIN_8				= 8,             //!< DIO_PORT_B_PIN_8
	DIO_PORT_B_PIN_9				= 9,             //!< DIO_PORT_B_PIN_9
	DIO_PORT_B_PIN_10				= 10,            //!< DIO_PORT_B_PIN_10
	DIO_PORT_B_PIN_11				= 11,            //!< DIO_PORT_B_PIN_11
	DIO_PORT_B_PIN_12				= 12,            //!< DIO_PORT_B_PIN_12
	DIO_PORT_B_PIN_13				= 13,            //!< DIO_PORT_B_PIN_13
	DIO_PORT_B_PIN_14				= 14,            //!< DIO_PORT_B_PIN_14
	DIO_PORT_B_PIN_15				= 15,            //!< DIO_PORT_B_PIN_15
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
    DIO_PORT_C_PIN_0                = 0, 			 //!< DIO_PORT_B_PIN_0
    DIO_PORT_C_PIN_1                = 1,			 //!< DIO_PORT_B_PIN_1
    DIO_PORT_C_PIN_2                = 2,			 //!< DIO_PORT_B_PIN_2
    DIO_PORT_C_PIN_3                = 3,			 //!< DIO_PORT_B_PIN_3
    DIO_PORT_C_PIN_4                = 4,			 //!< DIO_PORT_B_PIN_4
    DIO_PORT_C_PIN_5                = 5,			 //!< DIO_PORT_B_PIN_5
    DIO_PORT_C_PIN_6                = 6,			 //!< DIO_PORT_B_PIN_6
    DIO_PORT_C_PIN_7                = 7,			 //!< DIO_PORT_B_PIN_7
    DIO_PORT_C_PIN_8				= 8,             //!< DIO_PORT_C_PIN_8
	DIO_PORT_C_PIN_9				= 9,             //!< DIO_PORT_C_PIN_9
	DIO_PORT_C_PIN_10				= 10,            //!< DIO_PORT_C_PIN_10
	DIO_PORT_C_PIN_11				= 11,            //!< DIO_PORT_C_PIN_11
	DIO_PORT_C_PIN_12				= 12,            //!< DIO_PORT_C_PIN_12
	DIO_PORT_C_PIN_13				= 13,            //!< DIO_PORT_C_PIN_13
	DIO_PORT_C_PIN_14				= 14,            //!< DIO_PORT_C_PIN_14
	DIO_PORT_C_PIN_15				= 15,            //!< DIO_PORT_C_PIN_15
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    DIO_PORT_D_PIN_0                = 0,			 //!< DIO_PORT_D_PIN_0
    DIO_PORT_D_PIN_1                = 1,			 //!< DIO_PORT_D_PIN_1
    DIO_PORT_D_PIN_2                = 2,  			 //!< DIO_PORT_D_PIN_2
    DIO_PORT_D_PIN_3                = 3,			 //!< DIO_PORT_D_PIN_3
    DIO_PORT_D_PIN_4                = 4,			 //!< DIO_PORT_D_PIN_4
    DIO_PORT_D_PIN_5                = 5,			 //!< DIO_PORT_D_PIN_5
    DIO_PORT_D_PIN_6                = 6,			 //!< DIO_PORT_D_PIN_6
    DIO_PORT_D_PIN_7                = 7,			 //!< DIO_PORT_D_PIN_7
    DIO_PORT_D_PIN_8				= 8,             //!< DIO_PORT_D_PIN_8
	DIO_PORT_D_PIN_9				= 9,             //!< DIO_PORT_D_PIN_9
	DIO_PORT_D_PIN_10				= 10,            //!< DIO_PORT_D_PIN_10
	DIO_PORT_D_PIN_11				= 11,            //!< DIO_PORT_D_PIN_11
	DIO_PORT_D_PIN_12				= 12,            //!< DIO_PORT_D_PIN_12
	DIO_PORT_D_PIN_13				= 13,            //!< DIO_PORT_D_PIN_13
	DIO_PORT_D_PIN_14				= 14,            //!< DIO_PORT_D_PIN_14
	DIO_PORT_D_PIN_15				= 15,            //!< DIO_PORT_D_PIN_15
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/

    DIO_PORT_E_PIN_0                = 0,			 //!< DIO_PORT_E_PIN_0
    DIO_PORT_E_PIN_1                = 1,			 //!< DIO_PORT_E_PIN_1
    DIO_PORT_E_PIN_2                = 2,			 //!< DIO_PORT_E_PIN_2
    DIO_PORT_E_PIN_3                = 3,			 //!< DIO_PORT_E_PIN_3
    DIO_PORT_E_PIN_4                = 4,			 //!< DIO_PORT_E_PIN_4
    DIO_PORT_E_PIN_5                = 5,			 //!< DIO_PORT_E_PIN_5
    DIO_PORT_E_PIN_6                = 6,			 //!< DIO_PORT_E_PIN_6
    DIO_PORT_E_PIN_7                = 7,			 //!< DIO_PORT_E_PIN_7
    DIO_PORT_E_PIN_8				= 8,             //!< DIO_PORT_E_PIN_8
	DIO_PORT_E_PIN_9				= 9,             //!< DIO_PORT_E_PIN_9
	DIO_PORT_E_PIN_10				= 10,            //!< DIO_PORT_E_PIN_10
	DIO_PORT_E_PIN_11				= 11,            //!< DIO_PORT_E_PIN_11
	DIO_PORT_E_PIN_12				= 12,            //!< DIO_PORT_E_PIN_12
	DIO_PORT_E_PIN_13				= 13,            //!< DIO_PORT_E_PIN_13
	DIO_PORT_E_PIN_14				= 14,            //!< DIO_PORT_E_PIN_14
	DIO_PORT_E_PIN_15				= 15,            //!< DIO_PORT_E_PIN_15
/********************************************************************/

/*********************** PORT F Pin Numbering ***********************/

    DIO_PORT_F_PIN_0                = 0,			 //!< DIO_PORT_F_PIN_0
    DIO_PORT_F_PIN_1                = 1,			 //!< DIO_PORT_F_PIN_1
    DIO_PORT_F_PIN_2                = 2,			 //!< DIO_PORT_F_PIN_2
    DIO_PORT_F_PIN_3                = 3, 			 //!< DIO_PORT_F_PIN_3
    DIO_PORT_F_PIN_4                = 4,			 //!< DIO_PORT_F_PIN_4
	DIO_PORT_F_PIN_5                = 5,   			 //!< DIO_PORT_F_PIN_5
    DIO_PORT_F_PIN_6                = 6,			 //!< DIO_PORT_F_PIN_6
    DIO_PORT_F_PIN_7                = 7,			 //!< DIO_PORT_F_PIN_7
    DIO_PORT_F_PIN_8				= 8,             //!< DIO_PORT_F_PIN_8
	DIO_PORT_F_PIN_9				= 9,             //!< DIO_PORT_F_PIN_9
	DIO_PORT_F_PIN_10				= 10,            //!< DIO_PORT_F_PIN_10
	DIO_PORT_F_PIN_11				= 11,            //!< DIO_PORT_F_PIN_11
	DIO_PORT_F_PIN_12				= 12,            //!< DIO_PORT_F_PIN_12
	DIO_PORT_F_PIN_13				= 13,            //!< DIO_PORT_F_PIN_13
	DIO_PORT_F_PIN_14				= 14,            //!< DIO_PORT_F_PIN_14
	DIO_PORT_F_PIN_15				= 15,            //!< DIO_PORT_F_PIN_15
/********************************************************************/

/*********************** PORT G Pin Numbering ***********************/

	DIO_PORT_G_PIN_0                = 0,   			 //!< DIO_PORT_G_PIN_0
	DIO_PORT_G_PIN_1                = 1,	         //!< DIO_PORT_G_PIN_1
	DIO_PORT_G_PIN_2                = 2,   			 //!< DIO_PORT_G_PIN_2
	DIO_PORT_G_PIN_3                = 3, 		     //!< DIO_PORT_G_PIN_3
	DIO_PORT_G_PIN_4                = 4,   			 //!< DIO_PORT_G_PIN_4
	DIO_PORT_G_PIN_5                = 5,   			 //!< DIO_PORT_G_PIN_5
	DIO_PORT_G_PIN_6                = 6,   			 //!< DIO_PORT_G_PIN_6
	DIO_PORT_G_PIN_7                = 7,   			 //!< DIO_PORT_G_PIN_7
	DIO_PORT_G_PIN_8				= 8,             //!< DIO_PORT_G_PIN_8
	DIO_PORT_G_PIN_9				= 9,             //!< DIO_PORT_G_PIN_9
	DIO_PORT_G_PIN_10				= 10,            //!< DIO_PORT_G_PIN_10
	DIO_PORT_G_PIN_11				= 11,            //!< DIO_PORT_G_PIN_11
	DIO_PORT_G_PIN_12				= 12,            //!< DIO_PORT_G_PIN_12
	DIO_PORT_G_PIN_13				= 13,            //!< DIO_PORT_G_PIN_13
	DIO_PORT_G_PIN_14				= 14,            //!< DIO_PORT_G_PIN_14
	DIO_PORT_G_PIN_15				= 15,            //!< DIO_PORT_G_PIN_15
/********************************************************************/

/*********************** PORT H Pin Numbering ***********************/

/*
 * Note: Port H has only PH0 & PH1 and they mostly used as
 * OSC_IN & OSC_OUT Pins
*/
	DIO_PORT_H_PIN_0                = 0,   			 //!< DIO_PORT_H_PIN_0
	DIO_PORT_H_PIN_1                = 1   			 //!< DIO_PORT_H_PIN_1
/********************************************************************/

}Dio_PinNumEnum;

#elif defined STM32F07
typedef enum{

/*********************** PORT A Pin Numbering ***********************/
    DIO_PORT_A_PIN_0                = 0, 			 //!< DIO_PORT_A_PIN_0
    DIO_PORT_A_PIN_1                = 1,			 //!< DIO_PORT_A_PIN_1
    DIO_PORT_A_PIN_2                = 2,			 //!< DIO_PORT_A_PIN_2
    DIO_PORT_A_PIN_3                = 3,			 //!< DIO_PORT_A_PIN_3
    DIO_PORT_A_PIN_4                = 4, 			 //!< DIO_PORT_A_PIN_4
    DIO_PORT_A_PIN_5                = 5, 		 	 //!< DIO_PORT_A_PIN_5
    DIO_PORT_A_PIN_6                = 6, 		 	 //!< DIO_PORT_A_PIN_6
    DIO_PORT_A_PIN_7                = 7, 		     //!< DIO_PORT_A_PIN_7
    DIO_PORT_A_PIN_8				= 8,           	 //!< DIO_PORT_A_PIN_8
	DIO_PORT_A_PIN_9				= 9,             //!< DIO_PORT_A_PIN_9
	DIO_PORT_A_PIN_10				= 10,            //!< DIO_PORT_A_PIN_10
	DIO_PORT_A_PIN_11				= 11,            //!< DIO_PORT_A_PIN_11
	DIO_PORT_A_PIN_12				= 12,            //!< DIO_PORT_A_PIN_12
	DIO_PORT_A_PIN_13				= 13,            //!< DIO_PORT_A_PIN_13
	DIO_PORT_A_PIN_14				= 14,            //!< DIO_PORT_A_PIN_14
	DIO_PORT_A_PIN_15				= 15,            //!< DIO_PORT_A_PIN_15
/********************************************************************/

/*********************** PORT B Pin Numbering ***********************/
    DIO_PORT_B_PIN_0                = 0,			 //!< DIO_PORT_B_PIN_0
    DIO_PORT_B_PIN_1                = 1,			 //!< DIO_PORT_B_PIN_1
    DIO_PORT_B_PIN_2                = 2,			 //!< DIO_PORT_B_PIN_2
    DIO_PORT_B_PIN_3                = 3,			 //!< DIO_PORT_B_PIN_3
    DIO_PORT_B_PIN_4                = 4,			 //!< DIO_PORT_B_PIN_4
    DIO_PORT_B_PIN_5                = 5,			 //!< DIO_PORT_B_PIN_5
    DIO_PORT_B_PIN_6                = 6,			 //!< DIO_PORT_B_PIN_6
    DIO_PORT_B_PIN_7                = 7,			 //!< DIO_PORT_B_PIN_7
    DIO_PORT_B_PIN_8				= 8,             //!< DIO_PORT_B_PIN_8
	DIO_PORT_B_PIN_9				= 9,             //!< DIO_PORT_B_PIN_9
	DIO_PORT_B_PIN_10				= 10,            //!< DIO_PORT_B_PIN_10
	DIO_PORT_B_PIN_11				= 11,            //!< DIO_PORT_B_PIN_11
	DIO_PORT_B_PIN_12				= 12,            //!< DIO_PORT_B_PIN_12
	DIO_PORT_B_PIN_13				= 13,            //!< DIO_PORT_B_PIN_13
	DIO_PORT_B_PIN_14				= 14,            //!< DIO_PORT_B_PIN_14
	DIO_PORT_B_PIN_15				= 15,            //!< DIO_PORT_B_PIN_15
/********************************************************************/

/*********************** PORT C Pin Numbering ***********************/
    DIO_PORT_C_PIN_0                = 0, 			 //!< DIO_PORT_B_PIN_0
    DIO_PORT_C_PIN_1                = 1,			 //!< DIO_PORT_B_PIN_1
    DIO_PORT_C_PIN_2                = 2,			 //!< DIO_PORT_B_PIN_2
    DIO_PORT_C_PIN_3                = 3,			 //!< DIO_PORT_B_PIN_3
    DIO_PORT_C_PIN_4                = 4,			 //!< DIO_PORT_B_PIN_4
    DIO_PORT_C_PIN_5                = 5,			 //!< DIO_PORT_B_PIN_5
    DIO_PORT_C_PIN_6                = 6,			 //!< DIO_PORT_B_PIN_6
    DIO_PORT_C_PIN_7                = 7,			 //!< DIO_PORT_B_PIN_7
    DIO_PORT_C_PIN_8				= 8,             //!< DIO_PORT_C_PIN_8
	DIO_PORT_C_PIN_9				= 9,             //!< DIO_PORT_C_PIN_9
	DIO_PORT_C_PIN_10				= 10,            //!< DIO_PORT_C_PIN_10
	DIO_PORT_C_PIN_11				= 11,            //!< DIO_PORT_C_PIN_11
	DIO_PORT_C_PIN_12				= 12,            //!< DIO_PORT_C_PIN_12
	DIO_PORT_C_PIN_13				= 13,            //!< DIO_PORT_C_PIN_13
	DIO_PORT_C_PIN_14				= 14,            //!< DIO_PORT_C_PIN_14
	DIO_PORT_C_PIN_15				= 15,            //!< DIO_PORT_C_PIN_15
/********************************************************************/

/*********************** PORT D Pin Numbering ***********************/
    DIO_PORT_D_PIN_0                = 0,			 //!< DIO_PORT_D_PIN_0
    DIO_PORT_D_PIN_1                = 1,			 //!< DIO_PORT_D_PIN_1
    DIO_PORT_D_PIN_2                = 2,  			 //!< DIO_PORT_D_PIN_2
    DIO_PORT_D_PIN_3                = 3,			 //!< DIO_PORT_D_PIN_3
    DIO_PORT_D_PIN_4                = 4,			 //!< DIO_PORT_D_PIN_4
    DIO_PORT_D_PIN_5                = 5,			 //!< DIO_PORT_D_PIN_5
    DIO_PORT_D_PIN_6                = 6,			 //!< DIO_PORT_D_PIN_6
    DIO_PORT_D_PIN_7                = 7,			 //!< DIO_PORT_D_PIN_7
    DIO_PORT_D_PIN_8				= 8,             //!< DIO_PORT_D_PIN_8
	DIO_PORT_D_PIN_9				= 9,             //!< DIO_PORT_D_PIN_9
	DIO_PORT_D_PIN_10				= 10,            //!< DIO_PORT_D_PIN_10
	DIO_PORT_D_PIN_11				= 11,            //!< DIO_PORT_D_PIN_11
	DIO_PORT_D_PIN_12				= 12,            //!< DIO_PORT_D_PIN_12
	DIO_PORT_D_PIN_13				= 13,            //!< DIO_PORT_D_PIN_13
	DIO_PORT_D_PIN_14				= 14,            //!< DIO_PORT_D_PIN_14
	DIO_PORT_D_PIN_15				= 15,            //!< DIO_PORT_D_PIN_15
/********************************************************************/

/*********************** PORT E Pin Numbering ***********************/

    DIO_PORT_E_PIN_0                = 0,			 //!< DIO_PORT_E_PIN_0
    DIO_PORT_E_PIN_1                = 1,			 //!< DIO_PORT_E_PIN_1
    DIO_PORT_E_PIN_2                = 2,			 //!< DIO_PORT_E_PIN_2
    DIO_PORT_E_PIN_3                = 3,			 //!< DIO_PORT_E_PIN_3
    DIO_PORT_E_PIN_4                = 4,			 //!< DIO_PORT_E_PIN_4
    DIO_PORT_E_PIN_5                = 5,			 //!< DIO_PORT_E_PIN_5
    DIO_PORT_E_PIN_6                = 6,			 //!< DIO_PORT_E_PIN_6
    DIO_PORT_E_PIN_7                = 7,			 //!< DIO_PORT_E_PIN_7
    DIO_PORT_E_PIN_8				= 8,             //!< DIO_PORT_E_PIN_8
	DIO_PORT_E_PIN_9				= 9,             //!< DIO_PORT_E_PIN_9
	DIO_PORT_E_PIN_10				= 10,            //!< DIO_PORT_E_PIN_10
	DIO_PORT_E_PIN_11				= 11,            //!< DIO_PORT_E_PIN_11
	DIO_PORT_E_PIN_12				= 12,            //!< DIO_PORT_E_PIN_12
	DIO_PORT_E_PIN_13				= 13,            //!< DIO_PORT_E_PIN_13
	DIO_PORT_E_PIN_14				= 14,            //!< DIO_PORT_E_PIN_14
	DIO_PORT_E_PIN_15				= 15,            //!< DIO_PORT_E_PIN_15
/********************************************************************/

/** Note: in STM32F407, There is no availability for PORTF & PORTG **/

/*********************** PORT H Pin Numbering ***********************/

	DIO_PORT_H_PIN_0                = 0,   			 //!< DIO_PORT_H_PIN_0
	DIO_PORT_H_PIN_1                = 1,   			 //!< DIO_PORT_H_PIN_1
	DIO_PORT_H_PIN_2                = 2,   			 //!< DIO_PORT_H_PIN_2
	DIO_PORT_H_PIN_3                = 3,   			 //!< DIO_PORT_H_PIN_3
	DIO_PORT_H_PIN_4                = 4,   			 //!< DIO_PORT_H_PIN_4
	DIO_PORT_H_PIN_5                = 5,   			 //!< DIO_PORT_H_PIN_5
	DIO_PORT_H_PIN_6                = 6,   			 //!< DIO_PORT_H_PIN_6
	DIO_PORT_H_PIN_7                = 7,		     //!< DIO_PORT_H_PIN_7
	DIO_PORT_H_PIN_8				= 8,             //!< DIO_PORT_H_PIN_8
	DIO_PORT_H_PIN_9				= 9,             //!< DIO_PORT_H_PIN_9
	DIO_PORT_H_PIN_10				= 10,            //!< DIO_PORT_H_PIN_10
	DIO_PORT_H_PIN_11				= 11,            //!< DIO_PORT_H_PIN_11
	DIO_PORT_H_PIN_12				= 12,            //!< DIO_PORT_H_PIN_12
	DIO_PORT_H_PIN_13				= 13,            //!< DIO_PORT_H_PIN_13
	DIO_PORT_H_PIN_14				= 14,            //!< DIO_PORT_H_PIN_14
	DIO_PORT_H_PIN_15				= 15             //!< DIO_PORT_H_PIN_15
/********************************************************************/


}Dio_PinNumEnum;

#endif

/**
 * @enum    Dio_PortNumEnum
 *
 * @addindex Dio_PortNumEnum
 *
 * @brief   Used to decide the Port Number used to numbering the port on the STM32F429
 */
#ifdef STM32F429
typedef enum{

    DIO_PORTA,//!< PORTA
	DIO_PORTB,//!< PORTB
	DIO_PORTC,//!< PORTC
	DIO_PORTD,//!< PORTD
	DIO_PORTE,//!< PORTE
	DIO_PORTF,//!< PORTF
	DIO_PORTG,//!< PORTG
	DIO_PORTH //!< PORTH

}Dio_PortNumEnum;

#elif defined STM32F407
/*
 * Redefine the Enum to be suitable with STM32F407
 * Which does not have PORTF & PORTG
*/
typedef enum{

	DIO_PORTA,//!< PORTA
	DIO_PORTB,//!< PORTB
	DIO_PORTC,//!< PORTC
	DIO_PORTD,//!< PORTD
	DIO_PORTE,//!< PORTE
	DIO_PORTH //!< PORTH

}Dio_PortNumEnum;

#endif

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
typedef uint8 Dio_PortLevelType;

/* Structure for Dio_ChannelGroup */
typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;

typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	Dio_PortType Port_Num;
	/* Member contains the ID of the Channel*/
	Dio_ChannelType Ch_Num;
}Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */
typedef struct Dio_ConfigType
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNLES];
} Dio_ConfigType;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* Function for DIO read Channel API */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Function for DIO write Channel API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function for DIO read Port API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);


#if (DIO_FLIP_CHANNEL_API == STD_ON)
/* Function for DIO flip channel API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

/* Function for DIO Get Version Info API */
#if (DIO_VERSION_INFO_API == STD_ON)
void Dio_GetVersionInfo(Std_VersionInfoType *versioninfo);
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Dio and other modules */
extern const Dio_ConfigType Dio_Configuration;

#endif /* DIO_H */
