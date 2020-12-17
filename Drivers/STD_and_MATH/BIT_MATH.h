#ifndef _BIT_MATH_H
#define _BIT_MATH_H

#define CLR_PORT(VAR)             		(VAR) &= ~(0x11111111)
#define SET_PORT(VAR,VALUE,BITNO) 		(VAR) |=  (VALUE << (BITNO))
#define SET_BIT(VAR,BITNO)        		(VAR) |=  (1 << (BITNO))
#define CLR_BIT(VAR,BITNO)        		(VAR) &= ~(1 << (BITNO))
#define TOG_BIT(VAR,BITNO)        		(VAR) ^=  (1 << (BITNO))
#define GET_BIT(VAR,BITNO)        		(((VAR) >> (BITNO)) & 0x01)

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Rotate right the register value with specific number of rotates */
#define ROR(REG,num) ( REG= (REG>>num) | (REG<<(8-num)) )

/* Rotate left the register value with specific number of rotates */
#define ROL(REG,num) ( REG= (REG<<num) | (REG>>(8-num)) )

/* Check if a specific bit is set in any register and return true if yes */
#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

/* Check if a specific bit is cleared in any register and return true if yes */
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )

#define SET_CONFIG(VAR,BITNO,CONFIG)	(VAR) |= (CONFIG <<(BITNO))

#endif
