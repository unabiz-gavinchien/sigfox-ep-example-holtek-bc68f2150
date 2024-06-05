
#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
/*
#define	uint8	volatile unsigned char
#define	uint16	volatile unsigned int
#define	uint32	volatile unsigned long

#define	BYTE		volatile unsigned char
#define	WORD		volatile unsigned int
*/
typedef volatile unsigned char uint8;
typedef volatile unsigned int uint16;
typedef volatile unsigned long uint32;
typedef volatile unsigned char BYTE;
typedef volatile unsigned int WORD;

typedef volatile signed char int8;
typedef volatile signed int int16;
typedef volatile signed long int32;

#define	HIGH		1
#define	LOW		0
#define	TRUE		1
#define	FALSE		0

#define BIT_0 	0x01 		/**< The value of bit 0 */
#define BIT_1 	0x02 		/**< The value of bit 1 */
#define BIT_2 	0x04 		/**< The value of bit 2 */
#define BIT_3 	0x08 		/**< The value of bit 3 */
#define BIT_4 	0x10 		/**< The value of bit 4 */
#define BIT_5 	0x20 		/**< The value of bit 5 */
#define BIT_6 	0x40 		/**< The value of bit 6 */
#define BIT_7 	0x80 		/**< The value of bit 7 */
#define BIT_8 	0x0100 	/**< The value of bit 8 */
#define BIT_9 	0x0200 	/**< The value of bit 9 */
#define BIT_10 0x0400 	/**< The value of bit 10 */
#define BIT_11 0x0800 	/**< The value of bit 11 */
#define BIT_12 0x1000 	/**< The value of bit 12 */
#define BIT_13 0x2000 	/**< The value of bit 13 */
#define BIT_14 0x4000 	/**< The value of bit 14 */
#define BIT_15 0x8000 	/**< The value of bit 15 */



typedef struct {
	unsigned char b0 : 1;
	unsigned char b1 : 1;
	unsigned char b2 : 1;
	unsigned char b3 : 1;
	unsigned char b4 : 1;
	unsigned char b5 : 1;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} _byte_bits;

typedef union 
{
	volatile unsigned char value;
	volatile _byte_bits bits;
} byte_t;


typedef union 
{
   volatile unsigned int value;
	struct 
   {
		volatile unsigned char low;
		volatile unsigned char high;
	} bytes;
} word_t;

// mov A,m 
#define ASM_M2A(varname)	asm volatile("mov A,%0"::"m"(varname))
// mov m,A
#define ASM_A2M(varname)	asm volatile("mov %0,A"::"m"(varname))
// 
#define ASM_CLR(varname)	asm volatile("clr %0"::"m"(varname))
#define ASM_INC(varname)	asm volatile("inc %0"::"m"(varname))
#define ASM_DEC(varname)	asm volatile("dec %0"::"m"(varname))
#define ASM_OFFSETL2A(varname)	asm volatile("mov A,offset %0"::"m"(varname))   
#define ASM_OFFSETH2A(varname)	asm volatile("mov A,(offset %0 >> 8)"::"m"(varname))

#define  Movm2m(d,s) \
         asm volatile("mov A,%0"::"m"(s)); \
         asm volatile("mov %0,A"::"m"(d))

#define  GetOffsetLow(d,s) \
         asm volatile("mov A,low(offset %0)":"=m"(s)); \
         asm volatile("mov %0,A"::"m"(d))

#define  GetOffsetHigh(d,s) \
         asm volatile("mov A,high(offset %0)":"=m"(s)); \
         asm volatile("mov %0,A"::"m"(d))

#define  GetOffset2bpmp1(sa) \
         asm volatile("mov A,high(offset %0)":"=m"(sa)); \
         asm volatile("mov %0,A"::"m"(_bp)); \
         asm volatile("mov A,low(offset %0)":"=m"(sa)); \
         asm volatile("mov %0,A"::"m"(_mp1))

#define  MovMatrixmp0(da,sa,ix) \
         asm volatile("mov A,low(offset %0)":"=m"(sa)); \
         asm volatile("add A,%0"::"m"(ix)); \
         asm volatile("mov %0,A":"=m"(_mp0)); \
         asm volatile("mov A,%0":"=m"(_iar0)); \
         asm volatile("mov %0,A"::"m"(da))


#endif // _TYPEDEF_H_

