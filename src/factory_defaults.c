/*
 * factory_defaults.c
 *
 *  Created on: 09-May-2016
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
#define DEVICE_PRODUCT_MODEL_STR	("Model String .....")
#define DEVICE_PRODUCT_NAME_STR		("Device Name .....")
#define DEVICE_PRODUCT_STR			("Product Description.....")
#define DEVICE_MFGDATE_SEC			(0)
#define DEVICE_MFGDATE_MIN			(10)
#define DEVICE_MFGDATE_HOUR			(10)
#define DEVICE_MFGDATE_MDAY			(1)
#define DEVICE_MFGDATE_MON			(1)
#define DEVICE_MFGDATE_YEAR			(1)
#define DEVICE_MFGDATE_WDAY			(1)
#define DEVICE_MFGDATE_YDAY			(1)
#define DEVICE_MFGDATE_ISDST		(0)
#define DEVICE_PC0					(0x00)
#define DEVICE_PC1					(0x01)
#define DEVICE_PC2					(0x02)
#define DEVICE_PC3					(0x03)
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
_STATIC EE_ReturnCode_t ResetProductCode(_VOID);
_STATIC EE_ReturnCode_t ResetProductStrings(_VOID);
_STATIC EE_ReturnCode_t ResetMfgDate(_VOID);
/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

/*
 *----------------------------------------------------------------------
 *  Function: _STATIC EE_ReturnCode_t ResetMfgDate(_VOID)
 *
 *  Summary	: This function resets the device mfg dates
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t ResetMfgDate(_VOID)
{
	EE_ReturnCode_t result = EE_OK;
	UINT16_t address;
	INT32_t tmp_pc;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	tmp_pc = (INT32_t)DEVICE_MFGDATE_SEC;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_SEC_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_MIN;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MIN_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_HOUR;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_HR_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_MDAY;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MDAY_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_MON;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MON_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_YEAR;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_YEAR_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_WDAY;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_WDAY_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_YDAY;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_YDAY_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (INT32_t)DEVICE_MFGDATE_ISDST;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_ISDST_OFFSET();
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	return EE_OK;
}

/*
 *----------------------------------------------------------------------
 *  Function: _STATIC EE_ReturnCode_t ResetProductStrings(_VOID)
 *
 *  Summary	: This function resets the device product strings
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t ResetProductStrings(_VOID)
{
	EE_ReturnCode_t result = EE_OK;
	UINT16_t address;
	UINT8_t *tmp_pc;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	tmp_pc = (UINT8_t *)DEVICE_PRODUCT_MODEL_STR;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_MODELSTR_OFFSET();
	if ( (result = EE_ReadWrite(address, tmp_pc, DEV_MODEL_STRING_SIZE, EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (UINT8_t *)DEVICE_PRODUCT_NAME_STR;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_NAMESTR_OFFSET();
	if ( (result = EE_ReadWrite(address, tmp_pc, DEV_NAME_STRING_SIZE, EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = (UINT8_t *)DEVICE_PRODUCT_STR;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODSTR_OFFSET();
	if ( (result = EE_ReadWrite(address, tmp_pc, DEV_PRODUCT_STRING_SIZE, EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	return EE_OK;
}


/*
 *----------------------------------------------------------------------
 *  Function: _STATIC EE_ReturnCode_t ResetProductCode(_VOID)
 *
 *  Summary	: This function resets the device product code
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC EE_ReturnCode_t ResetProductCode(_VOID)
{
	EE_ReturnCode_t result = EE_OK;
	UINT16_t address;
	UINT8_t tmp_pc;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	tmp_pc = DEVICE_PC0;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC0_OFFSET();
	if ( (result = EE_ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = DEVICE_PC1;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC1_OFFSET();
	if ( (result = EE_ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = DEVICE_PC2;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC2_OFFSET();
	if ( (result = EE_ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	tmp_pc = DEVICE_PC3;
	address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC3_OFFSET();
	if ( (result = EE_ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) != EE_OK )
	{
		return result;
	}

	return EE_OK;
}


/*
*----------------------------------------------------------------------
*   Export Functions Definitions
*----------------------------------------------------------------------
*/

/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t ReinitFactorySettings(_VOID)
 *
 *  Summary	: This function reinitializes the database to factory defaults
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t ReinitFactorySettings(_VOID)
{
	EE_ReturnCode_t result;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if ( (result = ResetProductCode()) != EE_OK )
	{
		return result;
	}

	if ( (result = ResetProductStrings()) != EE_OK )
	{
		return result;
	}

	if ( (result = ResetMfgDate()) != EE_OK )
	{
		return result;
	}

	/* Finally validate the db signature */
	UINT16_t address = EE_DB_SIGNATURE_OFFSET();
	UINT32_t signature = EE_DATABASE_SIGNATURE;
	result = EE_ReadWrite(address, (UINT8_t *)&signature, sizeof(signature), EEOP_WRITE);
	return result;
}
