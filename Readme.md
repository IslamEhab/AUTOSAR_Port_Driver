
# DIO & Port AUTOSAR Drivers Version 4.3.1
## This driver still under development
## 												AUTOSAR Layers 
![Image of AUTOSAR](https://automotiveembeddedsite.files.wordpress.com/2016/12/autosar_layered_architecture_details.jpg?w=840)

In AUTOSAR, ordinary GPIO Driver is divided into 2 drivers:
- **Dio Driver**  which responsible of writing/reading digital 0 or 1.
- **Port Driver** which responsible of setting all HW pins configurations (General Purpose DIO or alternative function, Analog or digital, input or output, etc.)

From the picture you can relate that Port & Dio are HW dependant, so that for every HW you need to build a new Dio & Port drivers

This projects implements both Dio and Port Drivers for STM32F429 and STM32F407 using static configuration (#define) in Platform_Types.h file, this approach made just to save time to implement another AUTOSAR Drivers.

**At the end of development, there will be a PDF generated by doxygen that describes the Port & Dio drivers components like:**
- Structures & Enums used in the code
- API names and its parameters
- How to use these APIs, structures and enums 

**Note: AF Function & Ordinary GPIO works properly on STM32F429**

====================================================================

**Note: This driver needs:**

1. Testing on STM32F429 & STM32F407

1. Write Test cases for Both HW to ensure that Port & Dio works properly
1. Start Alternative Function Enum for STM32F407

