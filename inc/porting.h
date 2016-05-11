/*
 * porting.h
 *
 *  Created on: 05-Apr-2016
 *      Author: Mrunmoy Samal
 *
 *  LICENSE:-
 *  The MIT License (MIT)
 *  Copyright (c) 2016 Mrunmoy Samal
 *
 *  Permission is hereby granted, free of charge, to any person
 *  obtaining a copy of this software and associated documentation
 *  files (the "Software"), to deal in the Software without
 *  restriction, including without limitation the rights to use,
 *  copy, modify, merge, publish, distribute, sublicense, and/or
 *  sell copies of the Software, and to permit persons to whom
 *  the Software is furnished to do so, subject to the following
 *  conditions:
 *
 *  The above copyright notice and this permission notice shall
 *  be included in all copies or substantial portions of the
 *  Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 *  OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef INC_PORTING_H_
#define INC_PORTING_H_

//! __ATTRIBUTE__(x).
/*!
		      uncomment to use structure packing.
		      make sure it is defined to the
		      supported attribute keyword for
		      your compiler.
		      __attribute__ is supported by gnu c.
 */
#define __ATTRIBUTE__(x)
//#define __ATTRIBUTE__(x)    __attribute__(x)


#include "datatypes.h"

//! _STATIC.
/*!
	  A macro defined for static keyword.
 */
#define _STATIC				static
//! _CONST.
/*!
	  A macro defined for const keyword.
 */
#define _CONST				const
//! _EXTERN.
/*!
	  A macro defined for extern keyword.
 */
#define _EXTERN				extern
//! _VOID.
/*!
	  A macro defined for void keyword.
 */
#define _VOID				void
//! B_FALSE.
/*!
	  A macro defined for boolean 0.
 */
#define B_FALSE				(0)
//! B_TRUE.
/*!
	  A macro defined for boolean 1.
 */
#define B_TRUE				(1)
//! BE_BIG_END.
/*!
	  A macro defined for Big endian Big End.
 */
#define BE_BIG_END				(0)
//! BE_LITTLE_END.
/*!
	  A macro defined for Big endian Little End.
 */
#define BE_LITTLE_END			(1)
//! LE_BIG_END.
/*!
	  A macro defined for Little endian Big End.
 */
#define LE_BIG_END				(1)
//! LE_LITTLE_END.
/*!
	  A macro defined for Little endian Little End.
 */
#define LE_LITTLE_END			(0)
//! CRC_HIGH_BYTE.
/*!
	  A macro defined for crc high byte.
 */
#define CRC_HIGH_BYTE			(0)
//! CRC_LOW_BYTE.
/*!
	  A macro defined for crc low byte.
 */
#define CRC_LOW_BYTE			(1)

//! _ENDIAN.
/*!
	  A type define for Endian types Enumeration.
 */
typedef enum _ENDIAN
{
	__ENDIAN_LITTLE = 0,	/**< enum value __ENDIAN_LITTLE = 0. Indicates Little Endian. */
	__ENDIAN_BIG,			/**< enum value __ENDIAN_BIG = 0. Indicates Big Endian. */
	__ENDIAN_MAX			/**< enum value __ENDIAN_MAX = 0. Endian Enum Senitnel. */
}_ENDIAN;

//! DataType_t.
/*!
	  A type define for Data types Enumeration.
 */
typedef enum DataType_t
{
	DT_BOOL = 0,	/**< enum value DT_BOOL = 0. Indicates Boolean data type. */
	DT_CHAR,		/**< enum value DT_CHAR = 1. Indicates char data type. */
	DT_UINT8,		/**< enum value DT_UINT8 = 2. Indicates unsigned int 8-bit data type. */
	DT_INT8,		/**< enum value DT_INT8 = 3. Indicates signed int 8-bit data type. */
	DT_UINT16,		/**< enum value DT_UINT16 = 4. Indicates unsigned int 16-bit data type. */
	DT_INT16,		/**< enum value DT_INT16 = 5. Indicates signed int 16-bit data type. */
	DT_UINT32,		/**< enum value DT_UINT32 = 6. Indicates unsigned int 32-bit data type. */
	DT_INT32,		/**< enum value DT_INT32 = 7. Indicates signed int 32-bit data type. */
	DT_FLOAT,		/**< enum value DT_FLOAT = 8. Indicates float data type. */
	DT_DOUBLE,		/**< enum value DT_DOUBLE = 9. Indicates double data type. */
	DT_MAX			/**< enum value DT_MAX = 10. Max Count. */
}DataType_t;

#endif /* INC_PORTING_H_ */
