/*
 * test.c
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
_STATIC _VOID UpdateApplicationInformation(_VOID);
_STATIC _VOID UpdateProductDetails(_VOID);
_STATIC _VOID UpdateSensorData(_VOID);
/*
*----------------------------------------------------------------------
*   Private Functions Definitions
*----------------------------------------------------------------------
*/

/*
 *----------------------------------------------------------------------
 *  Function: int main(int argc, char *argv[])
 *
 *  Summary	: This is the main test function
 *
 *  Input	: Not used
 *
 *  Output	: None
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
int main(int argc, char *argv[])
{
	/* Initialize the database */
	DB_Initialize();

	UpdateProductDetails();

	UpdateApplicationInformation();

	UpdateSensorData();

	return 0;
}


/*
 *----------------------------------------------------------------------
 *  Function: _STATIC _VOID UpdateApplicationInformation(_VOID)
 *
 *  Summary	: This function initializes the database app info and prints
 *            it after reading it back
 *
 *  Input	: None
 *
 *  Output	: None
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC _VOID UpdateApplicationInformation(_VOID)
{
	EEBootAppCommonDataStruct_t appInfo;

	memset((void*)&appInfo, 0, sizeof(appInfo));

	if ( DB_ReadWriteAppInfo(&appInfo, EEOP_READ) == EE_OK )
	{
		appInfo.start_address = 0x80000000; /* Change it to correct address for your project */
		appInfo.alt_start_address = 0x8C000000; /* Change it to correct address for your project */

		appInfo.forced_initiated = B_False;
		appInfo.must_self_check = B_False;

		appInfo.signature = 0xA1B2C3D4; /* Change it to correct signature for your project */
		appInfo.signature_address = 0x8000000C; /* Change it to correct address for your project */

		appInfo.rev.major_rev = 1; /* Change it to correct rev for your application */
		appInfo.rev.major_ver = 0; /* Change it to correct ver for your application */
		appInfo.rev.minor_rev = 0; /* Change it to correct rev for your application */
		appInfo.rev.minor_ver = 4; /* Change it to correct ver for your application */

		appInfo.install_date.tm_hour = 10;
		appInfo.install_date.tm_min = 10;
		appInfo.install_date.tm_sec = 0;
		appInfo.install_date.tm_mday = 11;
		appInfo.install_date.tm_mon = 5;
		appInfo.install_date.tm_wday = 2;
		appInfo.install_date.tm_yday = 132;
		appInfo.install_date.tm_year = 2016;
		appInfo.install_date.tm_isdst = 0;

		if ( DB_ReadWriteAppInfo(&appInfo, EEOP_WRITE) == EE_OK )
		{
			memset((void*)&appInfo, 0, sizeof(appInfo));

			if ( DB_ReadWriteAppInfo(&appInfo, EEOP_READ) == EE_OK )
			{
				printf("Application Details:-\n");
				printf("\tStart Address     : 0x%08x\n", appInfo.start_address);
				printf("\tAlt. Start Address: 0x%08x\n", appInfo.alt_start_address);
				printf("\tSignature Address : 0x%08x\n", appInfo.signature_address);
				printf("\tSignature         : 0x%08x\n", appInfo.signature);
				printf("\tRevision          : %d.%d.%d.%d\n", appInfo.rev.major_rev, appInfo.rev.major_ver, appInfo.rev.minor_rev, appInfo.rev.minor_ver);
				printf("\tInstallation Date : %d/%d/%d\n\n", appInfo.install_date.tm_mday, appInfo.install_date.tm_mon, appInfo.install_date.tm_year);
			}
		}
	}
}


/*
 *----------------------------------------------------------------------
 *  Function: _STATIC _VOID UpdateProductDetails(_VOID)
 *
 *  Summary	: This function initializes the database product info and prints
 *            it after reading it back
 *
 *  Input	: None
 *
 *  Output	: None
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC _VOID UpdateProductDetails(_VOID)
{
	EEDeviceProductData_t productData;

	memset((void*)&productData, 0, sizeof(productData));

	if ( DB_ReadWriteProductInfo(&productData, EEOP_READ) == EE_OK )
	{
		productData.dev_id.pc0 = 0x03;
		productData.dev_id.pc2 = 0x05;

		productData.mfg_date.tm_mday = 21;
		productData.mfg_date.tm_mon  = 5;
		productData.mfg_date.tm_year = 2016;

		if ( DB_ReadWriteProductInfo(&productData, EEOP_WRITE) == EE_OK )
		{
			memset((void*)&productData, 0, sizeof(productData));

			if ( DB_ReadWriteProductInfo(&productData, EEOP_READ) == EE_OK )
			{
				printf("Product Details:-\n");
				printf("\tIdentifier : %2d %2d %2d %2d\n",
						productData.dev_id.pc0,
						productData.dev_id.pc1,
						productData.dev_id.pc2,
						productData.dev_id.pc3);

				printf("\tMfg Date   : %d/%d/%d\n\n",
						productData.mfg_date.tm_mday,
						productData.mfg_date.tm_mon,
						productData.mfg_date.tm_year);
			}
		}
	}
}

/*
 *----------------------------------------------------------------------
 *  Function: _STATIC _VOID UpdateSensorData(_VOID)
 *
 *  Summary	: This function initializes the database sensor info and prints
 *            it after reading it back
 *
 *  Input	: None
 *
 *  Output	: None
 *
 *  Notes	:
 *
 *----------------------------------------------------------------------
 */
_STATIC _VOID UpdateSensorData(_VOID)
{
	EESensorData_t sensorData;

	memset((void*)&sensorData, 0, sizeof(sensorData));

	sensorData.address 				= 0x01;
	sensorData.data.value 			= 55.45f;
	sensorData.data.datetimestamp 	= 1462939739;
	sensorData.detected 			= B_True;
	DB_ReadWriteSensorInfo(0, &sensorData, EEOP_WRITE);

	sensorData.address 				= 0x02;
	sensorData.data.value 			= 0.0f;
	sensorData.detected 			= B_False;
	DB_ReadWriteSensorInfo(1, &sensorData, EEOP_WRITE);

	sensorData.address 				= 0x03;
	sensorData.data.value 			= 14.33f;
	sensorData.detected 			= B_True;
	DB_ReadWriteSensorInfo(2, &sensorData, EEOP_WRITE);

	sensorData.address 				= 0x04;
	sensorData.data.value 			= 0.0f;
	sensorData.detected 			= B_False;
	DB_ReadWriteSensorInfo(3, &sensorData, EEOP_WRITE);

	memset((void*)&sensorData, 0, sizeof(sensorData));

	printf("Sensor Data:-\n");

	if ( DB_ReadWriteSensorInfo(0, &sensorData, EEOP_READ) == EE_OK )
	{
		printf("\tAddress           : 0x%02x \n", sensorData.address);
		printf("\tDetection Status  : ");
		(sensorData.detected == B_True) ? printf("Found\n") : printf("Not found\n");
		printf("\tValue             : %0.2f \n", sensorData.data.value);
		printf("\tTimestamp         : %d\n\n", sensorData.data.datetimestamp);
	}

	if ( DB_ReadWriteSensorInfo(1, &sensorData, EEOP_READ) == EE_OK )
	{
		printf("\tAddress           : 0x%02x \n", sensorData.address);
		printf("\tDetection Status  : ");
		(sensorData.detected == B_True) ? printf("Found\n") : printf("Not found\n");
		printf("\tValue             : %0.2f \n", sensorData.data.value);
		printf("\tTimestamp         : %d\n\n", sensorData.data.datetimestamp);
	}

	if ( DB_ReadWriteSensorInfo(2, &sensorData, EEOP_READ) == EE_OK )
	{
		printf("\tAddress           : 0x%02x \n", sensorData.address);
		printf("\tDetection Status  : ");
		(sensorData.detected == B_True) ? printf("Found\n") : printf("Not found\n");
		printf("\tValue             : %0.2f \n", sensorData.data.value);
		printf("\tTimestamp         : %d\n\n", sensorData.data.datetimestamp);
	}

	if ( DB_ReadWriteSensorInfo(3, &sensorData, EEOP_READ) == EE_OK )
	{
		printf("\tAddress           : 0x%02x \n", sensorData.address);
		printf("\tDetection Status  : ");
		(sensorData.detected == B_True) ? printf("Found\n") : printf("Not found\n");
		printf("\tValue             : %0.2f \n", sensorData.data.value);
		printf("\tTimestamp         : %d\n\n", sensorData.data.datetimestamp);
	}
}

/*
*----------------------------------------------------------------------
*   Export Functions Definitions
*----------------------------------------------------------------------
*/
