/*
 * datatypes.h
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

#ifndef INC_DATATYPES_H_
#define INC_DATATYPES_H_

/*! \var typedef  signed char    CHAR_t.
    \brief A type definition for Signed character data.
*/
typedef  signed char    CHAR_t;


/*! \var typedef  signed char    INT8_t.
    \brief A type definition for Signed 8-bit data.
*/
typedef  signed char    INT8_t;


/*! \var typedef  unsigned char  UINT8_t.
    \brief A type definition for Unsigned 8-bit data.
*/
typedef  unsigned char  UINT8_t;


/*! \var typedef  short          INT16_t.
    \brief A type definition for Signed 16-bit data.
*/
typedef  short          INT16_t;


/*! \var typedef  unsigned short UINT16_t.
    \brief A type definition for Unsigned 16-bit data.
*/
typedef  unsigned short UINT16_t;


/*! \var typedef  int INT32_t.
    \brief A type definition for Signed 32-bit data.
*/
typedef  int            INT32_t;


/*! \var typedef  unsigned int UINT32_t.
    \brief A type definition for Unsigned 32-bit data.
*/
typedef  unsigned int   UINT32_t;


/*! \var typedef  signed long long INT64_t.
    \brief A type definition for Signed 64-bit data data.
*/
typedef  signed long long INT64_t;


/*! \var typedef  unsigned long long UINT64_t.
    \brief A type definition for Unsigned 64-bit.
*/
typedef  unsigned long long UINT64_t;


/*! \var typedef  float   FLOAT32_t.
    \brief A type definition for float data.
*/
typedef  float   FLOAT32_t;


/*! \var typedef  double   FLOAT64_t.
    \brief A type definition for double data.
*/
typedef  double   FLOAT64_t;


/*! \var typedef   enum  BOOL_t.
    \brief A type definition for boolean type.
*/
typedef  enum  BOOL_t
{
	B_False = 0,	/**< enum value B_False = 0. Indicates Boolean value = False. */
	B_True = 1		/**< enum value B_True = 1. Indicates Boolean value = True. */
}BOOL_t;



#endif /* INC_DATATYPES_H_ */
