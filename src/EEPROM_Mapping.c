/*
 * EEPROM_Mapping.c
 *
 *  Created on: 09-May-2016
 *      Author: MSamal
 *
 *  LICENSE:-
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */





/*
 *----------------------------------------------------------------------
 *   Include Files
 *----------------------------------------------------------------------
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "database.h"
#include "EEPROM_Mapping.h"
/*
*----------------------------------------------------------------------
*   Private Defines
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Macros
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Private Data Types
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Public Variables
*----------------------------------------------------------------------
*/


/*
*----------------------------------------------------------------------
*   Private Variables (static)
*----------------------------------------------------------------------
*/
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
_STATIC UINT8_t EE_MEMORY[EE_PAGESIZE*EE_PAGES];
#endif
/*
*----------------------------------------------------------------------
*   Public Constants
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Constants (static)
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Private Function Prototypes (static)
*----------------------------------------------------------------------
*/
_STATIC EE_ReturnCode_t EE_ReadPage(UINT16_t Address, UINT8_t * pReadBuffer,
		size_t Size);
_STATIC EE_ReturnCode_t EE_WritePage(UINT16_t Address, UINT8_t * pWriteBuffer,
		size_t Size);
_STATIC EE_ReturnCode_t EE_Read(UINT16_t Address, UINT8_t * pReadBuffer,
		size_t Size);
_STATIC EE_ReturnCode_t EE_Write(UINT16_t Address, UINT8_t * pWriteBuffer,
		size_t Size);
/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

/*
 *----------------------------------------------------------------------
 *  Function: _STATIC EE_ReturnCode_t EE_ReadPage(UINT16_t Address,
 *            UINT8_t * pReadBuffer)
 *
 *  Summary	: This function reads a page from the EEPROM
 *
 *  Input	: Address - start address in EEPROM
 *            pReadBuffer - store the read data into this buffer
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t EE_ReadPage(UINT16_t Address, UINT8_t * pReadBuffer,
                size_t Size)
{
        EE_ReturnCode_t result = EE_INVALIDADDRESS;
        if ( (Address + Size) <= EE_DATABASE_SIZE )
        {
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
                memcpy((void*)pReadBuffer, (void*)&EE_MEMORY[Address], Size);
#endif
                result = EE_OK;
	}
	return result;
}



/*
 *----------------------------------------------------------------------
 *  Function: _STATIC EE_ReturnCode_t EE_WritePage(UINT16_t Address,
 *            UINT8_t * pWriteBuffer, size_t Size)
 *
 *  Summary	: This function writes a page in to the EEPROM
 *
 *  Input	: Address - start address in EEPROM
 *            pWriteBuffer - buffer containing data to write
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t EE_WritePage(UINT16_t Address, UINT8_t * pWriteBuffer,
                                             size_t Size)
{
        EE_ReturnCode_t result = EE_INVALIDADDRESS;
        if ( (Address + Size) <= EE_DATABASE_SIZE )
        {
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
                memcpy((void*)&EE_MEMORY[Address], (void*)pWriteBuffer, Size);
#endif
                result = EE_OK;
	}
	return result;
}




/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t EE_Read(UINT16_t Address,
 *                                     UINT8_t * pReadBuffer,
 *		                               size_t Size)
 *
 *  Summary	: This function reads data from the EEPROM
 *
 *  Input	: Address - start address in EEPROM
 *            pReadBuffer - buffer to read data in to
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t EE_Read(UINT16_t Address, UINT8_t * pReadBuffer,
		size_t Size)
{
	EE_ReturnCode_t result = EE_INVALIDADDRESS;
	UINT8_t CurrentPageNumber = Address / EE_PAGESIZE;
	UINT8_t CurrentPositionWithinPage = Address % EE_PAGESIZE;
	UINT8_t NumBytesWithinCurrentPage = 0;
	UINT16_t StartAddress = Address;
	UINT16_t byteIndex = 0;

	if ( (Address + Size) <= EE_DATABASE_SIZE )
	{
		/* Will it fit within the current page */
		if ((CurrentPositionWithinPage + Size) < EE_PAGESIZE)
		{
			/* Read into this page and be done */
			/* Call to Page Read */
			result = EE_ReadPage(StartAddress, pReadBuffer, Size);
		}
		else
		{
			UINT16_t RemainingBytesToRead = Size;

			while (RemainingBytesToRead > 0)
			{
				/* do we have more than one page of data to be written ? */
				if (RemainingBytesToRead > EE_PAGESIZE)
				{
					/* Read whatever fits within the current page */
					NumBytesWithinCurrentPage = EE_PAGESIZE - CurrentPositionWithinPage;
				}
				else
				{
					/* Read whatever is remaining */
					NumBytesWithinCurrentPage = RemainingBytesToRead;
				}

				/* Read Page */
				result = EE_ReadPage(StartAddress, &pReadBuffer[byteIndex], NumBytesWithinCurrentPage);

				StartAddress += NumBytesWithinCurrentPage;

				byteIndex += NumBytesWithinCurrentPage;

				/* update remaining bytes to Read */
				RemainingBytesToRead -= NumBytesWithinCurrentPage;

				/* since we are done with one full page, we can set start byte position of next page to 0 */
				CurrentPositionWithinPage = 0;

				CurrentPageNumber++;
			}
		}
	}
	return result;
}



/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t EE_Write(UINT16_t Address,
 *                                     UINT8_t * pWriteBuffer,
 *		                               size_t Size)
 *
 *  Summary	: This function writes data in to the EEPROM
 *
 *  Input	: Address - start address in EEPROM
 *            pWriteBuffer - buffer containing data to write
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t EE_Write(UINT16_t Address, UINT8_t * pWriteBuffer,
		size_t Size)
{
	EE_ReturnCode_t result = EE_INVALIDADDRESS;
	UINT8_t CurrentPageNumber = Address / EE_PAGESIZE;
	UINT8_t CurrentPositionWithinPage = Address % EE_PAGESIZE;
	UINT8_t NumBytesFitWithinCurrentPage = 0;
	UINT16_t StartAddress = Address;
	UINT16_t byteIndex = 0;

	if ( (Address + Size) <= EE_DATABASE_SIZE )
	{
		/* Will it fit within the current page */
		if ((CurrentPositionWithinPage + Size) < EE_PAGESIZE)
		{
			/* Write into this page and be done */
			/* Call to Page Write */
			result = EE_WritePage(StartAddress, pWriteBuffer, Size);
		}
		else
		{
			UINT16_t RemainingBytesToWrite = Size;

			while (RemainingBytesToWrite > 0)
			{
				/* do we have more than one page of data to be written ? */
				if (RemainingBytesToWrite > EE_PAGESIZE)
				{
					/* Write whatever fits within the current page */
					NumBytesFitWithinCurrentPage = EE_PAGESIZE - CurrentPositionWithinPage;
				}
				else
				{
					/* Write whatever is remaining */
					NumBytesFitWithinCurrentPage = RemainingBytesToWrite;
				}

				/* Write Page */
				result = EE_WritePage(StartAddress, &pWriteBuffer[byteIndex], NumBytesFitWithinCurrentPage);

				StartAddress += NumBytesFitWithinCurrentPage;

				byteIndex += NumBytesFitWithinCurrentPage;

				/* update remaining bytes to write */
				RemainingBytesToWrite -= NumBytesFitWithinCurrentPage;

				/* since we are done with one full page, we can set start byte position of next page to 0 */
				CurrentPositionWithinPage = 0;

				CurrentPageNumber++;
			}
		}
	}
	return result;
}
/*
*----------------------------------------------------------------------
*   Export Functions Definitions
*----------------------------------------------------------------------
*/
EE_ReturnCode_t EE_ReadWrite(UINT16_t Address, UINT8_t * pWriteBuffer,
		size_t Size, EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_OK;
	switch(operation)
	{
	case EEOP_READ:
		result = EE_Read(Address, pWriteBuffer, Size);
		break;

	case EEOP_WRITE:
		result = EE_Write(Address, pWriteBuffer, Size);
		break;

	default:
		result = EE_INVALIDOPERATION;
		break;
	}
	return result;
}
