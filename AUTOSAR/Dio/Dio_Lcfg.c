 /******************************************************************************
 *
 * Module: 		Dio
 *
 * File Name: 	Dio_Lcfg.c
 *
 * Description: Link time (Post Build) Configuration Source file for
 * 				STM32F429 Microcontroller - Dio Driver
 *
 * Author: 		Islam Ehab
 *
 * Date;		12/12/2020
 ******************************************************************************/
/*******************************************************************************
 * @file:	Dio_Lcfg.c
 *
 * @brief:	Link time (Post Build) Configuration Source file for
 * 			STM32F429 Microcontroller - Dio Driver
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 ******************************************************************************/
#include "Dio.h"

/*
 * Module Version 1.0.0
 */
#define DIO_PBCFG_SW_MAJOR_VERSION              (1U)
#define DIO_PBCFG_SW_MINOR_VERSION              (0U)
#define DIO_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define DIO_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define DIO_PBCFG_AR_RELEASE_MINOR_VERSION     (3U)
#define DIO_PBCFG_AR_RELEASE_PATCH_VERSION     (1U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_AR_RELEASE_MAJOR_VERSION != DIO_AR_RELEASE_MAJOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_MINOR_VERSION != DIO_AR_RELEASE_MINOR_VERSION)\
 ||  (DIO_PBCFG_AR_RELEASE_PATCH_VERSION != DIO_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((DIO_PBCFG_SW_MAJOR_VERSION != DIO_SW_MAJOR_VERSION)\
 ||  (DIO_PBCFG_SW_MINOR_VERSION != DIO_SW_MINOR_VERSION)\
 ||  (DIO_PBCFG_SW_PATCH_VERSION != DIO_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Dio_Init API */
const Dio_ConfigType Dio_Configuration = {
                                             DioConf_LED1_PORT_NUM,DioConf_LED1_CHANNEL_NUM,
											 DioConf_LED2_PORT_NUM,DioConf_LED2_CHANNEL_NUM,
											 DioConf_SW1_PORT_NUM,DioConf_SW1_CHANNEL_NUM,
											 DioConf_SW2_PORT_NUM,DioConf_SW2_CHANNEL_NUM
				         };
