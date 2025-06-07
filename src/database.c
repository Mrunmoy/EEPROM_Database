/*
 * database.c
 *
 *  Created on: 06-May-2016
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
/*! \var DB_SIGNATURE
    \brief A Macro for EEPROM Database Valid Signature
*/
#define DB_SIGNATURE			(0xAABBCCDD)
/*! \var KICK_WATCHDOG
    \brief A Macro for kicking the watchdog
*/
#define KICK_WATCHDOG()


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
_STATIC UINT8_t gReadWriteBuffer[EE_PAGESIZE];

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



/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

/*
*----------------------------------------------------------------------
*   Export Functions Definitions
*----------------------------------------------------------------------
*/
/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ZeroFillEE(_VOID)
 *
 *  Summary	: This function initializes the database to Zero
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ZeroFillEE(_VOID)
{
	EE_ReturnCode_t result = EE_OK;
	int address;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	/* Clear the buffer to 0s */
	memset(gReadWriteBuffer, 0, sizeof(gReadWriteBuffer));

        /* for each page, fill with 0s */
        for(address=0; address<EE_DATABASE_SIZE; address+=EE_PAGESIZE)
        {
                size_t chunk = EE_PAGESIZE;
                if ((address + chunk) > EE_DATABASE_SIZE)
                {
                        chunk = EE_DATABASE_SIZE - address;
                }
                if ( (result = EE_ReadWrite(address, gReadWriteBuffer, chunk, EEOP_WRITE)) != EE_OK )
                {
                        break;
                }

		/* kick the watch dog if its enabled so that
		 * cpu reset doesn't happen during zero fill */
		KICK_WATCHDOG();
	}
	return result;
}

/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_Initialize(_VOID)
 *
 *  Summary	: This function checks and initializes the EEPROM database
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_Initialize(_VOID)
{
	EE_ReturnCode_t result = EE_OK;
	UINT32_t db_signature = 0;
	UINT16_t address = EE_DB_SIGNATURE_OFFSET();

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif


	/* Read the Database signature of EE Database */
	if ( (result = EE_ReadWrite(address, (UINT8_t *)&db_signature, sizeof(db_signature), EEOP_READ)) == EE_OK )
	{
		/* Check if the EE Database is valid */
		if (db_signature == DB_SIGNATURE)
		{
			result = EE_OK;

			/* signature matches, so database is OK
			 * Now, load sensor data from EEPROM */
		}
		else
		{
			/* Init the EE Database to 0s */
			DB_ZeroFillEE();

			/* Reset EE Database to Factory defaults settings */
			ReinitFactorySettings();
		}
	}

	return result;
}

/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ReadWriteAppInfo(
 *            EEBootAppCommonDataStruct_t *pAppInfo,
 *		      EE_Opcode_t operation)
 *
 *  Summary	: This function reads/writes Application Information in
 *            EEPROM database
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ReadWriteAppInfo(EEBootAppCommonDataStruct_t *pAppInfo,
		EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_INVALIDSOURCE;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if (pAppInfo)
	{
		UINT16_t address = EE_DEV_SHARED_DATA_OFFSET() + EE_APP_OFFSET();
		result = EE_ReadWrite(address, (UINT8_t*)pAppInfo, sizeof(*pAppInfo), operation);
	}

	return result;
}



/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ReadWriteBootInfo(
 *            EEBootAppCommonDataStruct_t *pBootInfo,
 *		      EE_Opcode_t operation)
 *
 *  Summary	: This function reads/writes Boot Information in
 *            EEPROM database
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ReadWriteBootInfo(EEBootAppCommonDataStruct_t *pBootInfo,
		EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_INVALIDSOURCE;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if (pBootInfo)
	{
		UINT16_t address = EE_DEV_SHARED_DATA_OFFSET() + EE_BOOT_OFFSET();
		result = EE_ReadWrite(address, (UINT8_t*)pBootInfo, sizeof(*pBootInfo), operation);
	}

	return result;
}




/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ReadWriteProductInfo(
 *            EEBootAppCommonDataStruct_t *pProductInfo,
 *		      EE_Opcode_t operation)
 *
 *  Summary	: This function reads/writes Product Information in
 *            EEPROM database
 *
 *  Input	: None
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ReadWriteProductInfo(EEDeviceProductData_t *pProductInfo,
		EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_INVALIDSOURCE;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if (pProductInfo)
	{
		UINT16_t address = EE_DEV_PRODUCT_DATA_OFFSET();
		result = EE_ReadWrite(address, (UINT8_t*)pProductInfo, sizeof(*pProductInfo), operation);
	}

	return result;
}




/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ReadWriteDatabaseSignature(
 *            EEBootAppCommonDataStruct_t *pSignature,
 *		      EE_Opcode_t operation)
 *
 *  Summary	: This function reads/writes Database-Valid Signature in
 *            EEPROM database
 *
 *  Input	: pSignature - Pointer to Database signature
 *            operation - Read or Write operation
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ReadWriteDatabaseSignature(UINT32_t *pSignature,
		EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_INVALIDSOURCE;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if (pSignature)
	{
		UINT16_t address = EE_DB_SIGNATURE_OFFSET();
		result = EE_ReadWrite(address, (UINT8_t*)pSignature, sizeof(*pSignature), operation);
	}

	return result;
}




/*
 *----------------------------------------------------------------------
 *  Function: EE_ReturnCode_t DB_ReadWriteSensorInfo(UINT8_t SensorIndex,
 *            EESensorData_t *pSensorInfo,
 *		      EE_Opcode_t operation)
 *
 *  Summary	: This function reads/writes Database-Valid Signature in
 *            EEPROM database
 *
 *  Input	: SensorIndex - Index of sensor to be modified/read
 *            pSensorInfo - Pointer to sensor information structure
 *            operation - Read or Write operation
 *
 *  Output	: Result of EEPROM Operation as Enum
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
EE_ReturnCode_t DB_ReadWriteSensorInfo(UINT8_t SensorIndex,
		EESensorData_t *pSensorInfo,
		EE_Opcode_t operation)
{
	EE_ReturnCode_t result = EE_INVALIDSOURCE;

#ifdef __DEBUG_DB
	printf("%s\n", __FUNCTION__);
#endif

	if (pSensorInfo)
	{
		if ( SensorIndex < NUM_SENSORS)
		{
			UINT16_t address = EE_SENSORDATA_OFFSET(SensorIndex);
			result = EE_ReadWrite(address, (UINT8_t*)pSensorInfo, sizeof(*pSensorInfo), operation);
		}
		else
		{
			result = EE_INVALIDDATA;
		}
	}

	return result;
}
