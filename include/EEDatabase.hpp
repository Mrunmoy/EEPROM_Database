#ifndef EEDATABASE_HPP
#define EEDATABASE_HPP

#include "database.h"
#include "EEPROM_Mapping.h"

class EEPROM {
public:
    static EE_ReturnCode_t ReadWrite(UINT16_t Address, UINT8_t *pBuffer,
                                     size_t Size, EE_Opcode_t operation);
private:
    static EE_ReturnCode_t ReadPage(UINT16_t Address, UINT8_t *pReadBuffer,
                                    size_t Size);
    static EE_ReturnCode_t WritePage(UINT16_t Address, UINT8_t *pWriteBuffer,
                                     size_t Size);
    static EE_ReturnCode_t Read(UINT16_t Address, UINT8_t *pReadBuffer,
                                size_t Size);
    static EE_ReturnCode_t Write(UINT16_t Address, UINT8_t *pWriteBuffer,
                                 size_t Size);
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
    static UINT8_t EE_MEMORY[EE_PAGESIZE * EE_PAGES];
#endif
};

class EEDatabase {
public:
    static EE_ReturnCode_t ReinitFactorySettings();
    static EE_ReturnCode_t DB_ZeroFillEE();
    static EE_ReturnCode_t DB_Initialize();
    static EE_ReturnCode_t DB_ReadWriteBootInfo(EEBootAppCommonDataStruct_t *pBootInfo,
                                               EE_Opcode_t operation);
    static EE_ReturnCode_t DB_ReadWriteAppInfo(EEBootAppCommonDataStruct_t *pAppInfo,
                                              EE_Opcode_t operation);
    static EE_ReturnCode_t DB_ReadWriteProductInfo(EEDeviceProductData_t *pProductInfo,
                                                  EE_Opcode_t operation);
    static EE_ReturnCode_t DB_ReadWriteDatabaseSignature(UINT32_t *pSignature,
                                                        EE_Opcode_t operation);
    static EE_ReturnCode_t DB_ReadWriteSensorInfo(UINT8_t SensorIndex,
                                                 EESensorData_t *pSensorInfo,
                                                 EE_Opcode_t operation);
private:
    static EE_ReturnCode_t ResetProductCode();
    static EE_ReturnCode_t ResetProductStrings();
    static EE_ReturnCode_t ResetMfgDate();
    static UINT8_t gReadWriteBuffer[EE_PAGESIZE];
};

#endif // EEDATABASE_HPP
