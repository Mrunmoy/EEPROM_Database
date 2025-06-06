/*
 * database.h
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

#ifndef INC_DATABASE_H_
#define INC_DATABASE_H_

#include "porting.h"
#include <stddef.h>

/*
*----------------------------------------------------------------------
*   Public Defines
*----------------------------------------------------------------------
*/
/*! \var RESERVED_FILLER_SIZE
    \brief A Macro for using fillers for future expansion
*/
#define RESERVED_FILLER_SIZE	(16)
/*! \var DEV_MODEL_STRING_SIZE
    \brief A Macro for product model string size
*/
#define DEV_MODEL_STRING_SIZE	(64)
/*! \var RESERVED_FILLER_SIZE
    \brief A Macro for product name string size
*/
#define DEV_NAME_STRING_SIZE	(64)
/*! \var RESERVED_FILLER_SIZE
    \brief A Macro for product description string size
*/
#define DEV_PRODUCT_STRING_SIZE	(64)
/*! \var RESERVED_FILLER_SIZE
    \brief A Macro for maximum number of sensors
*/
#define NUM_SENSORS				(10)
/*! \var EE_DATABASE_SIGNATURE
    \brief A Macro for EEPROM Database size
*/
#define EE_DATABASE_SIGNATURE	(0xAABBCCDD)
/*! \var EE_DATABASE_SIZE
    \brief A Macro for EEPROM Database size
*/
#define EE_DATABASE_SIZE		(sizeof(EEDataLayout_t))

//#define __DEBUG_DB










/*
*----------------------------------------------------------------------
*   Public Macros
*----------------------------------------------------------------------
*/
/*! \var OFFSET_OF(datatype, member).
    \brief A Macro to get offset of a member field inside a data structure.
*/
#define OFFSET_OF(structname, structmember) ((UINT32_t)offsetof(structname, structmember))

/*! \struct DateTimeStamp_t
    \brief  Date Time Structure Definition.

    Date Time Structure Definition.
*/
struct DateTimeStamp_t
{
	//! tm_sec.
	/*!
		      seconds.
	 */
	INT32_t	tm_sec;
	//! tm_min.
	/*!
		      minute.
	 */
	INT32_t	tm_min;
	//! tm_hour.
	/*!
		      hour.
	 */
	INT32_t	tm_hour;
	//! tm_mday.
	/*!
		      day of month.
	 */
	INT32_t	tm_mday;
	//! tm_mon.
	/*!
		      month.
	 */
	INT32_t	tm_mon;
	//! tm_year.
	/*!
		      year.
	 */
	INT32_t	tm_year;
	//! tm_wday.
	/*!
		      day of week.
	 */
	INT32_t	tm_wday;
	//! tm_yday.
	/*!
		      Day of Year.
	 */
	INT32_t	tm_yday;
	//! tm_isdst.
	/*!
		      Is Daylight Time.
	 */
	INT32_t	tm_isdst;
	INT32_t	__extra_1;
	INT32_t	__extra_2;
}__ATTRIBUTE__((packed));
typedef struct DateTimeStamp_t DateTimeStamp_t;

#define EE_TIMESTAMP_OFFSET(Element) 		(OFFSET_OF(DateTimeStamp_t, Element))
	#define EE_SECONDS_OFFSET() 			(EE_TIMESTAMP_OFFSET(tm_sec))
	#define EE_MINUTES_OFFSET() 			(EE_TIMESTAMP_OFFSET(tm_min))
	#define EE_HOURS_OFFSET() 				(EE_TIMESTAMP_OFFSET(tm_hour))
	#define EE_MONTHDAY_OFFSET() 			(EE_TIMESTAMP_OFFSET(tm_mday))
	#define EE_MONTH_OFFSET() 				(EE_TIMESTAMP_OFFSET(tm_mon))
	#define EE_YEAR_OFFSET() 				(EE_TIMESTAMP_OFFSET(tm_year))
	#define EE_WEEKDAY_OFFSET() 			(EE_TIMESTAMP_OFFSET(tm_wday))
	#define EE_YEARDAY_OFFSET() 			(EE_TIMESTAMP_OFFSET(tm_yday))
	#define EE_ISDST_OFFSET() 				(EE_TIMESTAMP_OFFSET(tm_isdst))




/*! \struct Version_t
    \brief  Date Time Structure Definition.

    Date Time Structure Definition.
*/
struct Version_t
{
	//! major_ver.
	/*!
		      Major Version.
	 */
	UINT8_t	major_ver;
	//! major_rev.
	/*!
		      Major Revision.
	 */
	UINT8_t	major_rev;
	//! minor_ver.
	/*!
		      Minor Version.
	 */
	UINT8_t	minor_ver;
	//! minor_rev.
	/*!
		      Minor Revision.
	 */
	UINT8_t	minor_rev;
}__ATTRIBUTE__((packed));
typedef struct Version_t Version_t;

#define EE_REV_INFO_OFFSET(Element) 		(OFFSET_OF(Version_t, Element))
	#define EE_MAJOR_VER_OFFSET() 			(EE_REV_INFO_OFFSET(major_ver))
	#define EE_MAJOR_REV_OFFSET() 			(EE_REV_INFO_OFFSET(major_rev))
	#define EE_MINOR_VER_OFFSET() 			(EE_REV_INFO_OFFSET(minor_ver))
	#define EE_MINOR_REV_OFFSET() 			(EE_REV_INFO_OFFSET(minor_rev))




/*! \struct EEDeviceProductCode_t
    \brief  Product Identifier Structure Definition.

    Device Product Identifier Structure Definition.
    4-byte device identifier
*/
struct EEDeviceProductCode_t
{
	//! pc0.
	/*!
		      Product Code 0.
	 */
	UINT8_t pc0;
	//! pc1.
	/*!
		      Product Code 1.
	 */
	UINT8_t pc1;
	//! pc2.
	/*!
		      Product Code 2.
	 */
	UINT8_t pc2;
	//! pc3.
	/*!
		      Product Code 3.
	 */
	UINT8_t pc3;
}__ATTRIBUTE__((packed));
typedef struct EEDeviceProductCode_t EEDeviceProductCode_t;

#define EE_DEV_PRODUCTCODE_OFFSET(Element) 		(OFFSET_OF(EEDeviceProductCode_t, Element))
	#define EE_DEV_PINFO_PC0_OFFSET() 			(EE_DEV_PRODUCTCODE_OFFSET(pc0))
	#define EE_DEV_PINFO_PC1_OFFSET() 			(EE_DEV_PRODUCTCODE_OFFSET(pc1))
	#define EE_DEV_PINFO_PC2_OFFSET() 			(EE_DEV_PRODUCTCODE_OFFSET(pc2))
	#define EE_DEV_PINFO_PC3_OFFSET() 			(EE_DEV_PRODUCTCODE_OFFSET(pc3))




/*! \struct EEDeviceProductData_t
    \brief  Product Information Structure Definition.

    Device Product Information Structure Definition.
    This data should be written only once at the end
    of line during production.
*/
struct EEDeviceProductData_t
{
	//! dev_id.
	/*!
		      Device Identifier.
	 */
	EEDeviceProductCode_t 	dev_id;
	//! model_str.
	/*!
		      Product Model Number String.
	 */
	CHAR_t					model_str[DEV_MODEL_STRING_SIZE];
	//! name_str.
	/*!
		      Product Name String.
	 */
	CHAR_t					name_str[DEV_NAME_STRING_SIZE];
	//! product_str.
	/*!
		      Product DEscription String.
	 */
	CHAR_t					product_str[DEV_PRODUCT_STRING_SIZE];
	//! mfg_date.
	/*!
		      Manufactured Date.
	 */
	DateTimeStamp_t			mfg_date;
}__ATTRIBUTE__((packed));
typedef struct EEDeviceProductData_t EEDeviceProductData_t;

#define EE_DEV_PRODUCTDATA_OFFSET(Element) 		(OFFSET_OF(EEDeviceProductData_t, Element))
	#define EE_DEV_IDTAG_OFFSET() 				(EE_DEV_PRODUCTDATA_OFFSET(dev_id))
		#define EE_DEV_PRODID_PC0_OFFSET() 		(EE_DEV_IDTAG_OFFSET() + EE_DEV_PINFO_PC0_OFFSET())
		#define EE_DEV_PRODID_PC1_OFFSET() 		(EE_DEV_IDTAG_OFFSET() + EE_DEV_PINFO_PC1_OFFSET())
		#define EE_DEV_PRODID_PC2_OFFSET() 		(EE_DEV_IDTAG_OFFSET() + EE_DEV_PINFO_PC2_OFFSET())
		#define EE_DEV_PRODID_PC3_OFFSET() 		(EE_DEV_IDTAG_OFFSET() + EE_DEV_PINFO_PC3_OFFSET())
	#define EE_DEV_MODELSTR_OFFSET() 			(EE_DEV_PRODUCTDATA_OFFSET(model_str))
	#define EE_DEV_NAMESTR_OFFSET() 			(EE_DEV_PRODUCTDATA_OFFSET(name_str))
	#define EE_DEV_PRODSTR_OFFSET() 			(EE_DEV_PRODUCTDATA_OFFSET(product_str))
	#define EE_DEV_MFG_OFFSET() 				(EE_DEV_PRODUCTDATA_OFFSET(mfg_date))
		#define EE_DEVMFG_SEC_OFFSET() 			(EE_DEV_MFG_OFFSET() + EE_SECONDS_OFFSET())
		#define EE_DEVMFG_MIN_OFFSET() 			(EE_DEV_MFG_OFFSET() + EE_MINUTES_OFFSET())
		#define EE_DEVMFG_HR_OFFSET() 			(EE_DEV_MFG_OFFSET() + EE_HOURS_OFFSET())
		#define EE_DEVMFG_MDAY_OFFSET() 		(EE_DEV_MFG_OFFSET() + EE_MONTHDAY_OFFSET())
		#define EE_DEVMFG_MON_OFFSET() 			(EE_DEV_MFG_OFFSET() + EE_MONTH_OFFSET())
		#define EE_DEVMFG_YEAR_OFFSET() 		(EE_DEV_MFG_OFFSET() + EE_YEAR_OFFSET())
		#define EE_DEVMFG_WDAY_OFFSET() 		(EE_DEV_MFG_OFFSET() + EE_WEEKDAY_OFFSET())
		#define EE_DEVMFG_YDAY_OFFSET() 		(EE_DEV_MFG_OFFSET() + EE_YEARDAY_OFFSET())
		#define EE_DEVMFG_ISDST_OFFSET() 		(EE_DEV_MFG_OFFSET() + EE_ISDST_OFFSET())




/*! \struct EEBootModeSwitch_t
    \brief  Boot modes Structure Definition.

    Device boot mode Structure Definition.
*/
struct EEBootModeSwitch_t
{
	//! SW0-SW7.
	/*!
		      Boot mode configuration switches.
	 */
	UINT8_t SW0: 1;
	UINT8_t SW1: 1;
	UINT8_t SW2: 1;
	UINT8_t SW3: 1;
	UINT8_t SW4: 1;
	UINT8_t SW5: 1;
	UINT8_t SW6: 1;
	UINT8_t SW7: 1;
}__ATTRIBUTE__((packed));
typedef struct EEBootModeSwitch_t EEBootModeSwitch_t;

#define EE_BOOTMODE_SWBITS_OFFSET(Element) 		(OFFSET_OF(EEBootModeSwitch_t, Element))
	#define EE_SW0_MASK							(0x80)
	#define EE_SW1_MASK							(0x40)
	#define EE_SW2_MASK							(0x20)
	#define EE_SW3_MASK							(0x10)
	#define EE_SW4_MASK							(0x08)
	#define EE_SW5_MASK							(0x04)
	#define EE_SW6_MASK							(0x02)
	#define EE_SW7_MASK							(0x01)




/*! \struct EEBootAppCommonDataStruct_t
    \brief  Common Data Structure Definition for Boot and App Information.

    Common Data Structure Definition for Boot and App Information.
    This data should not be moved in any case.
*/
struct EEBootAppCommonDataStruct_t
{
	//! rev.
	/*!
		      binary revision (boot/app).
	 */
	Version_t 		rev;
	//! forced_initiated.
	/*!
		      Flag to initiate Firmware upgrade(boot only/unused in app).
	 */
	BOOL_t			forced_initiated;
	//! must_self_check.
	/*!
		      Flag to run checksum of binary at startup (boot/app).
	 */
	BOOL_t          must_self_check;
	//! signature.
	/*!
		      Binary Valid Signature (boot/app).
	 */
	UINT32_t        signature;
	//! signature_address.
	/*!
		      Address of binary signature in Flash (boot/app).
	 */
	UINT32_t        signature_address;
	//! start_address.
	/*!
		      Start Address in Flash (boot/app).
	 */
	UINT32_t        start_address;
	//! alt_start_address.
	/*!
		      Alternate Start Address in Flash(app only/unused in boot).
	 */
	UINT32_t        alt_start_address;
	//! install_date.
	/*!
		      Installed Date (boot/app).
	 */
	DateTimeStamp_t	install_date;
	//! checksum.
	/*!
		      checksum of binary (boot/app).
	 */
	UINT32_t        checksum;
}__ATTRIBUTE__((packed));
typedef struct EEBootAppCommonDataStruct_t EEBootAppCommonDataStruct_t;

#define EE_BOOTAPP_COMMON_OFFSET(Element) 		(OFFSET_OF(EEBootAppCommonDataStruct_t, Element))
	#define EE_BA_VER_OFFSET()					(EE_BOOTAPP_COMMON_OFFSET(rev))
	#define EE_BA_FORCED_INIT_OFFSET()			(EE_BOOTAPP_COMMON_OFFSET(forced_initiated))
	#define EE_BA_SELFCHECK_OFFSET()			(EE_BOOTAPP_COMMON_OFFSET(must_self_check))
	#define EE_BA_SIGNATURE_OFFSET()			(EE_BOOTAPP_COMMON_OFFSET(signature))
	#define EE_BA_SIGNATURE_ADDR_OFFSET()		(EE_BOOTAPP_COMMON_OFFSET(signature_address))
	#define EE_BA_START_ADDR_OFFSET()			(EE_BOOTAPP_COMMON_OFFSET(start_address))
	#define EE_BA_ALT_START_ADDR_OFFSET()		(EE_BOOTAPP_COMMON_OFFSET(alt_start_address))
	#define EE_BA_INST_DATE_OFFSET()			(EE_BOOTAPP_COMMON_OFFSET(install_date))
	#define EE_BA_CHECKSUM_OFFSET()				(EE_BOOTAPP_COMMON_OFFSET(checksum))




/*! \struct EEBootAndApplicationSharedData_t
    \brief  Shared Data Structure Definition.

    Shared Data between bootloader and application.
    This data should not be moved in any case.
*/
struct EEBootAndApplicationSharedData_t
{
	//! boot_mode.
	/*!
		      Boot Mode Settings.
	 */
	EEBootModeSwitch_t			boot_mode;
	//! boot.
	/*!
		      Boot information. See EEBootAppCommonDataStruct_t.
	 */
	EEBootAppCommonDataStruct_t boot;
	//! app.
	/*!
		      App information. See EEBootAppCommonDataStruct_t.
	 */
	EEBootAppCommonDataStruct_t app;
}__ATTRIBUTE__((packed));
typedef struct EEBootAndApplicationSharedData_t EEBootAndApplicationSharedData_t;

#define EE_BOOTAPP_SHARED_OFFSET(Element) 		(OFFSET_OF(EEBootAndApplicationSharedData_t, Element))
	#define EE_BOOTMODE_OFFSET()				(EE_BOOTAPP_SHARED_OFFSET(boot_mode))
	#define EE_BOOT_OFFSET()					(EE_BOOTAPP_SHARED_OFFSET(boot))
		#define EE_BOOT_REV_OFFSET()			(EE_BOOT_OFFSET() + EE_BA_VER_OFFSET())
		#define EE_BOOT_FORCEDINIT_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_FORCED_INIT_OFFSET())
		#define EE_BOOT_SELFCHECK_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_SELFCHECK_OFFSET())
		#define EE_BOOT_SIGNATURE_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_SIGNATURE_OFFSET())
		#define EE_BOOT_SIGNATURE_ADDR_OFFSET()	(EE_BOOT_OFFSET() + EE_BA_SIGNATURE_ADDR_OFFSET())
		#define EE_BOOT_START_ADDR_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_START_ADDR_OFFSET())
		#define EE_BOOT_ALT_START_ADDR_OFFSET()	(EE_BOOT_OFFSET() + EE_BA_ALT_START_ADDR_OFFSET())
		#define EE_BOOT_INST_DATE_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_INST_DATE_OFFSET())
		#define EE_BOOT_CHECKSUM_OFFSET()		(EE_BOOT_OFFSET() + EE_BA_CHECKSUM_OFFSET())
	#define EE_APP_OFFSET()						(EE_BOOTAPP_SHARED_OFFSET(app))
		#define EE_APP_REV_OFFSET()				(EE_APP_OFFSET() + EE_BA_VER_OFFSET())
		#define EE_APP_FORCEDINIT_OFFSET()		(EE_APP_OFFSET() + EE_BA_FORCED_INIT_OFFSET())
		#define EE_APP_SELFCHECK_OFFSET()		(EE_APP_OFFSET() + EE_BA_SELFCHECK_OFFSET())
		#define EE_APP_SIGNATURE_OFFSET()		(EE_APP_OFFSET() + EE_BA_SIGNATURE_OFFSET())
		#define EE_APP_SIGNATURE_ADDR_OFFSET()	(EE_APP_OFFSET() + EE_BA_SIGNATURE_ADDR_OFFSET())
		#define EE_APP_START_ADDR_OFFSET()		(EE_APP_OFFSET() + EE_BA_START_ADDR_OFFSET())
		#define EE_APP_ALT_START_ADDR_OFFSET()	(EE_APP_OFFSET() + EE_BA_ALT_START_ADDR_OFFSET())
		#define EE_APP_INST_DATE_OFFSET()		(EE_APP_OFFSET() + EE_BA_INST_DATE_OFFSET())
		#define EE_APP_CHECKSUM_OFFSET()		(EE_APP_OFFSET() + EE_BA_CHECKSUM_OFFSET())




/*! \struct SensorValue_t
    \brief  Sensor data Structure Definition.

    Sensor Value structure definition.
*/
struct SensorValue_t
{
	//! datetimestamp.
	/*!
		      date time stamp of value obtained.
	 */
	UINT32_t   	datetimestamp;
	//! value.
	/*!
		      actual sensor value.
	 */
	FLOAT32_t 	value;
}__ATTRIBUTE__((packed));
typedef struct SensorValue_t SensorValue_t;

#define SENSORDATA_OFFSET(Element) 			(OFFSET_OF(SensorValue_t, Element))
	#define SSRDATA_DATETIME_OFFSET() 		(SENSORDATA_OFFSET(datetimestamp))
	#define SSRDATA_VALUE_OFFSET() 			(SENSORDATA_OFFSET(value))




/*! \struct EESensorData_t
    \brief  EEProm Sensor data Structure Definition.

    EEProm Sensor Data structure definition.
*/
struct EESensorData_t
{
	//! address.
	/*!
		      Address of Sensor.
	 */
	UINT8_t			address;
	//! detected.
	/*!
		      Whether sensor was detected.
	 */
	BOOL_t 			detected;
	//! data.
	/*!
		      Sensor Dat.
	 */
	SensorValue_t	data;
}__ATTRIBUTE__((packed));
typedef struct EESensorData_t EESensorData_t;

#define EE_SENSORDATA_INFO_OFFSET(Element) 	(OFFSET_OF(EESensorData_t, Element))
	#define EE_SD_ADDRESS_OFFSET()			(EE_SENSORDATA_INFO_OFFSET(address))
	#define EE_SD_DETECTEDFLAG_OFFSET()		(EE_SENSORDATA_INFO_OFFSET(detected))
	#define EE_SD_DATETIMESTAMP_OFFSET()	(EE_SENSORDATA_INFO_OFFSET(data) + SSRDATA_DATETIME_OFFSET())
	#define EE_SD_VALUE_OFFSET()			(EE_SENSORDATA_INFO_OFFSET(data) + SSRDATA_VALUE_OFFSET())




/*! \struct EEDataLayout_t
    \brief  EEProm Layout Data Structure Definition.

    Device Runtime  Data Structure Definition.
*/
struct EEDataLayout_t
{
	/********* Should not move these ***********************/
	//! dev_prd_data.
	/*!
		      Device Product Information.
	 */
	EEDeviceProductData_t 				dev_prd_data;
	//! _filler0.
	/*!
		      Reserved for Future Expansion.
	 */
	UINT8_t               				_filler0[RESERVED_FILLER_SIZE];
	//! shared_data.
	/*!
		      Boot and Application Shared Information.
	 */
	EEBootAndApplicationSharedData_t 	shared_data;
	//! _filler1.
	/*!
		      Reserved for Future Expansion.
	 */
	UINT8_t               				_filler1[RESERVED_FILLER_SIZE];
	UINT32_t                            database_signature;
	/********* Should not move these ***********************/

	/* Create Device runtime data structure instances here */
	//! sensor_data.
	/*!
		      Array of Sensor Information.
	 */
	EESensorData_t 						sensor_data[NUM_SENSORS];
}__ATTRIBUTE__((packed));
typedef struct EEDataLayout_t EEDataLayout_t;

#define EE_LAYOUT_OFFSET(Element) 							(OFFSET_OF(EEDataLayout_t, Element))
	#define EE_DEV_PRODUCT_DATA_OFFSET()					(EE_LAYOUT_OFFSET(dev_prd_data))
	#define EE_DEV_SHARED_DATA_OFFSET()						(EE_LAYOUT_OFFSET(shared_data))
	#define EE_DB_SIGNATURE_OFFSET()						(EE_LAYOUT_OFFSET(database_signature))
	#define EE_SENSORDATA_OFFSET(index)						(EE_LAYOUT_OFFSET(sensor_data) + index*(sizeof(EESensorData_t)))
		#define EE_SENSORDATA_ADDRESS_OFFSET(index)			(EE_SENSORDATA_OFFSET(index) + EE_SD_ADDRESS_OFFSET())
		#define EE_SENSORDATA_DETECTEDFLAG_OFFSET(index)	(EE_SENSORDATA_OFFSET(index) + EE_SD_DETECTEDFLAG_OFFSET())
		#define EE_SENSORDATA_DATETIMESTAMP_OFFSET(index)	(EE_SENSORDATA_OFFSET(index) + EE_SD_DATETIMESTAMP_OFFSET())
		#define EE_SENSORDATA_VALUE_OFFSET(index)			(EE_SENSORDATA_OFFSET(index) + EE_SD_VALUE_OFFSET())



/*! \var typedef   enum  EE_ReturnCode_t.
    \brief A type definition for EEPROM Operation Return type.
*/
typedef enum EE_ReturnCode_t
{
	EE_OK = 0,
	EE_INVALIDSOURCE,
	EE_INVALIDADDRESS,
	EE_INVALIDDATA,
	EE_INVALIDOPERATION,
	EE_READERROR,
	EE_WRITEERROR,
	EE_MAX
}EE_ReturnCode_t;


/*! \var typedef   enum  EE_Opcode_t.
    \brief A type definition for EEPROM Operation type.
*/
typedef enum EE_Opcode_t
{
	EEOP_READ = 0,
	EEOP_WRITE,
	EEOP_MAX
}EE_Opcode_t;



_EXTERN EE_ReturnCode_t ReinitFactorySettings(_VOID);
_EXTERN EE_ReturnCode_t DB_ZeroFillEE(_VOID);
_EXTERN EE_ReturnCode_t DB_Initialize(_VOID);
_EXTERN EE_ReturnCode_t DB_ReadWriteBootInfo(EEBootAppCommonDataStruct_t *pBootInfo,
		EE_Opcode_t operation);
_EXTERN EE_ReturnCode_t DB_ReadWriteAppInfo(EEBootAppCommonDataStruct_t *pAppInfo,
		EE_Opcode_t operation);
_EXTERN EE_ReturnCode_t DB_ReadWriteProductInfo(EEDeviceProductData_t *pProductInfo,
		EE_Opcode_t operation);
_EXTERN EE_ReturnCode_t DB_ReadWriteDatabaseSignature(UINT32_t *pSignature,
		EE_Opcode_t operation);
_EXTERN EE_ReturnCode_t DB_ReadWriteSensorInfo(UINT8_t SensorIndex,
		EESensorData_t *pSensorInfo,
		EE_Opcode_t operation);


#endif /* INC_DATABASE_H_ */
