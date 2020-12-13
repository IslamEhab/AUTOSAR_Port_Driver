 /******************************************************************************
 *
 * Module: 		Common - Platform Abstraction
 *
 * File Name: 	Platform_Types.h
 *
 * Description: Platform types for ARM Cortex-M4F
 *
 * Author: 		Islam Ehab
 *
 * Date:	 	12/12/2020
 *******************************************************************************/

/*******************************************************************************
 * @file:	Platform_Types.h
 *
 * @brief:	Platform types for ARM Cortex-M4F
 *
 * @author:	Islam Ehab
 *
 * @date:	12/12/2020
 ******************************************************************************/

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/*
 * This driver should be compatible with STM32F4 Family
 * there are some differences between Kits which will be
 * defined using this static configuration (#define)
 * Note: This is NOT an AUTOSAR Requirement
*/
#ifndef STM32F407
#define STM32F429
#endif

/*
 * ID of Company in AUTOSAR Website
 * Islam Ehab's ID = 1024
*/
#define PLATFORM_VENDOR_ID                          (1024U)

/*
 * Module Version 1.0.0
 */
#define PLATFORM_SW_MAJOR_VERSION                   (1U)
#define PLATFORM_SW_MINOR_VERSION                   (0U)
#define PLATFORM_SW_PATCH_VERSION                   (0U)

/*
 * AUTOSAR Version 4.3.1
 */
#define PLATFORM_AR_RELEASE_MAJOR_VERSION           (4U)
#define PLATFORM_AR_RELEASE_MINOR_VERSION           (3U)
#define PLATFORM_AR_RELEASE_PATCH_VERSION           (1U)

/*
 * CPU register type width
 */
#define CPU_TYPE_8                                  (8U)
#define CPU_TYPE_16                                 (16U)
#define CPU_TYPE_32                                 (32U)

/*
 * Bit order definition
 */
#define MSB_FIRST                   (0u)        /* Big endian bit ordering        */
#define LSB_FIRST                   (1u)        /* Little endian bit ordering     */

/*
 * Byte order definition
 */
#define HIGH_BYTE_FIRST             (0u)        /* Big endian byte ordering       */
#define LOW_BYTE_FIRST              (1u)        /* Little endian byte ordering    */

/*
 * Platform type and endianess definitions, specific for ARM Cortex-M4F
 */
#define CPU_TYPE            CPU_TYPE_32

#define CPU_BIT_ORDER       LSB_FIRST
#define CPU_BYTE_ORDER      LOW_BYTE_FIRST

/*
 * Boolean Values
 */
#ifndef FALSE
#define FALSE       (0u)
#endif
#ifndef TRUE
#define TRUE        (1u)
#endif

typedef unsigned char         boolean;

typedef unsigned char         uint8;          /*           0 .. 255             */
typedef signed char           sint8;          /*        -128 .. +127            */
typedef unsigned short        uint16;         /*           0 .. 65535           */
typedef signed short          sint16;         /*      -32768 .. +32767          */
typedef unsigned long         uint32;         /*           0 .. 4294967295      */
typedef signed long           sint32;         /* -2147483648 .. +2147483647     */
typedef unsigned long long    uint64;         /*       0..18446744073709551615  */
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

#endif /* PLATFORM_TYPES_H */
