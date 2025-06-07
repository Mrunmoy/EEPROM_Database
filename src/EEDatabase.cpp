#include "EEDatabase.hpp"
#include <cstring>
#include <cstdio>

#define DEVICE_PRODUCT_MODEL_STR "Model String ....."
#define DEVICE_PRODUCT_NAME_STR  "Device Name ....."
#define DEVICE_PRODUCT_STR       "Product Description....."
#define DEVICE_MFGDATE_SEC   (0)
#define DEVICE_MFGDATE_MIN   (10)
#define DEVICE_MFGDATE_HOUR  (10)
#define DEVICE_MFGDATE_MDAY  (1)
#define DEVICE_MFGDATE_MON   (1)
#define DEVICE_MFGDATE_YEAR  (1)
#define DEVICE_MFGDATE_WDAY  (1)
#define DEVICE_MFGDATE_YDAY  (1)
#define DEVICE_MFGDATE_ISDST (0)
#define DEVICE_PC0  (0x00)
#define DEVICE_PC1  (0x01)
#define DEVICE_PC2  (0x02)
#define DEVICE_PC3  (0x03)
#define DB_SIGNATURE (0xAABBCCDD)

#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
UINT8_t EEPROM::EE_MEMORY[EE_PAGESIZE * EE_PAGES] = {0};
#endif

// EEPROM low level implementation
EE_ReturnCode_t EEPROM::ReadPage(UINT16_t Address, UINT8_t *pReadBuffer,
                                 size_t Size) {
    EE_ReturnCode_t result = EE_INVALIDADDRESS;
    if (Address <= (EE_DATABASE_SIZE - EE_PAGESIZE)) {
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
        memcpy(pReadBuffer, &EE_MEMORY[Address], Size);
#endif
        result = EE_OK;
    }
    return result;
}

EE_ReturnCode_t EEPROM::WritePage(UINT16_t Address, UINT8_t *pWriteBuffer,
                                  size_t Size) {
    EE_ReturnCode_t result = EE_INVALIDADDRESS;
    if (Address <= (EE_DATABASE_SIZE - EE_PAGESIZE)) {
#ifdef __SIMULATE_EE_MEMORY_AS_ARRAY
        memcpy(&EE_MEMORY[Address], pWriteBuffer, Size);
#endif
        result = EE_OK;
    }
    return result;
}

EE_ReturnCode_t EEPROM::Read(UINT16_t Address, UINT8_t *pReadBuffer,
                             size_t Size) {
    EE_ReturnCode_t result = EE_INVALIDADDRESS;
    UINT8_t CurrentPageNumber = Address / EE_PAGESIZE;
    UINT8_t CurrentPositionWithinPage = Address % EE_PAGESIZE;
    UINT8_t NumBytesWithinCurrentPage = 0;
    UINT16_t StartAddress = Address;
    UINT16_t byteIndex = 0;

    if ((Address + Size) <= EE_DATABASE_SIZE) {
        if ((CurrentPositionWithinPage + Size) < EE_PAGESIZE) {
            result = ReadPage(StartAddress, pReadBuffer, Size);
        } else {
            UINT16_t RemainingBytesToRead = Size;
            while (RemainingBytesToRead > 0) {
                if (RemainingBytesToRead > EE_PAGESIZE) {
                    NumBytesWithinCurrentPage = EE_PAGESIZE - CurrentPositionWithinPage;
                } else {
                    NumBytesWithinCurrentPage = RemainingBytesToRead;
                }
                result = ReadPage(StartAddress, &pReadBuffer[byteIndex], NumBytesWithinCurrentPage);
                StartAddress += NumBytesWithinCurrentPage;
                byteIndex += NumBytesWithinCurrentPage;
                RemainingBytesToRead -= NumBytesWithinCurrentPage;
                CurrentPositionWithinPage = 0;
                CurrentPageNumber++;
            }
        }
    }
    return result;
}

EE_ReturnCode_t EEPROM::Write(UINT16_t Address, UINT8_t *pWriteBuffer,
                              size_t Size) {
    EE_ReturnCode_t result = EE_INVALIDADDRESS;
    UINT8_t CurrentPageNumber = Address / EE_PAGESIZE;
    UINT8_t CurrentPositionWithinPage = Address % EE_PAGESIZE;
    UINT8_t NumBytesFitWithinCurrentPage = 0;
    UINT16_t StartAddress = Address;
    UINT16_t byteIndex = 0;

    if ((Address + Size) <= EE_DATABASE_SIZE) {
        if ((CurrentPositionWithinPage + Size) < EE_PAGESIZE) {
            result = WritePage(StartAddress, pWriteBuffer, Size);
        } else {
            UINT16_t RemainingBytesToWrite = Size;
            while (RemainingBytesToWrite > 0) {
                if (RemainingBytesToWrite > EE_PAGESIZE) {
                    NumBytesFitWithinCurrentPage = EE_PAGESIZE - CurrentPositionWithinPage;
                } else {
                    NumBytesFitWithinCurrentPage = RemainingBytesToWrite;
                }
                result = WritePage(StartAddress, &pWriteBuffer[byteIndex], NumBytesFitWithinCurrentPage);
                StartAddress += NumBytesFitWithinCurrentPage;
                byteIndex += NumBytesFitWithinCurrentPage;
                RemainingBytesToWrite -= NumBytesFitWithinCurrentPage;
                CurrentPositionWithinPage = 0;
                CurrentPageNumber++;
            }
        }
    }
    return result;
}

EE_ReturnCode_t EEPROM::ReadWrite(UINT16_t Address, UINT8_t *pBuffer,
                                  size_t Size, EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_OK;
    switch (operation) {
    case EEOP_READ:
        result = Read(Address, pBuffer, Size);
        break;
    case EEOP_WRITE:
        result = Write(Address, pBuffer, Size);
        break;
    default:
        result = EE_INVALIDOPERATION;
        break;
    }
    return result;
}

// EEDatabase implementation
UINT8_t EEDatabase::gReadWriteBuffer[EE_PAGESIZE] = {0};

EE_ReturnCode_t EEDatabase::ResetMfgDate() {
    EE_ReturnCode_t result = EE_OK;
    UINT16_t address;
    INT32_t tmp_pc = (INT32_t)DEVICE_MFGDATE_SEC;
    address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_SEC_OFFSET();
    if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
        tmp_pc = (INT32_t)DEVICE_MFGDATE_MIN;
        address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MIN_OFFSET();
        if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
            tmp_pc = (INT32_t)DEVICE_MFGDATE_HOUR;
            address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_HR_OFFSET();
            if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                tmp_pc = (INT32_t)DEVICE_MFGDATE_MDAY;
                address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MDAY_OFFSET();
                if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                    tmp_pc = (INT32_t)DEVICE_MFGDATE_MON;
                    address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_MON_OFFSET();
                    if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                        tmp_pc = (INT32_t)DEVICE_MFGDATE_YEAR;
                        address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_YEAR_OFFSET();
                        if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                            tmp_pc = (INT32_t)DEVICE_MFGDATE_WDAY;
                            address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_WDAY_OFFSET();
                            if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                                tmp_pc = (INT32_t)DEVICE_MFGDATE_YDAY;
                                address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_YDAY_OFFSET();
                                if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                                    tmp_pc = (INT32_t)DEVICE_MFGDATE_ISDST;
                                    address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEVMFG_ISDST_OFFSET();
                                    result = EEPROM::ReadWrite(address, (UINT8_t *)&tmp_pc, sizeof(tmp_pc), EEOP_WRITE);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::ResetProductStrings() {
    EE_ReturnCode_t result = EE_OK;
    UINT16_t address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_MODELSTR_OFFSET();
    const char model[] = DEVICE_PRODUCT_MODEL_STR;
    if ((result = EEPROM::ReadWrite(address, (UINT8_t *)model, sizeof(model), EEOP_WRITE)) == EE_OK) {
        address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_NAMESTR_OFFSET();
        const char name[] = DEVICE_PRODUCT_NAME_STR;
        if ((result = EEPROM::ReadWrite(address, (UINT8_t *)name, sizeof(name), EEOP_WRITE)) == EE_OK) {
            address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODSTR_OFFSET();
            const char prod[] = DEVICE_PRODUCT_STR;
            result = EEPROM::ReadWrite(address, (UINT8_t *)prod, sizeof(prod), EEOP_WRITE);
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::ResetProductCode() {
    EE_ReturnCode_t result = EE_OK;
    UINT16_t address;
    UINT8_t tmp_pc = DEVICE_PC0;
    address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC0_OFFSET();
    if ((result = EEPROM::ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
        tmp_pc = DEVICE_PC1;
        address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC1_OFFSET();
        if ((result = EEPROM::ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
            tmp_pc = DEVICE_PC2;
            address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC2_OFFSET();
            if ((result = EEPROM::ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                tmp_pc = DEVICE_PC3;
                address = EE_DEV_PRODUCT_DATA_OFFSET() + EE_DEV_PRODID_PC3_OFFSET();
                if ((result = EEPROM::ReadWrite(address, &tmp_pc, sizeof(tmp_pc), EEOP_WRITE)) == EE_OK) {
                    result = EE_OK;
                }
            }
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::ReinitFactorySettings() {
    EE_ReturnCode_t result = EE_OK;
    if ((result = ResetProductCode()) == EE_OK) {
        if ((result = ResetProductStrings()) == EE_OK) {
            if ((result = ResetMfgDate()) == EE_OK) {
                UINT16_t address = EE_DB_SIGNATURE_OFFSET();
                UINT32_t signature = EE_DATABASE_SIGNATURE;
                result = EEPROM::ReadWrite(address, (UINT8_t *)&signature, sizeof(signature), EEOP_WRITE);
            }
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ZeroFillEE() {
    EE_ReturnCode_t result = EE_OK;
    int address;
    memset(gReadWriteBuffer, 0, sizeof(gReadWriteBuffer));
    for (address = 0; address < EE_DATABASE_SIZE; address += EE_PAGESIZE) {
        if ((result = EEPROM::ReadWrite(address, gReadWriteBuffer, EE_PAGESIZE, EEOP_WRITE)) != EE_OK) {
            break;
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_Initialize() {
    EE_ReturnCode_t result = EE_OK;
    UINT32_t db_signature = 0;
    UINT16_t address = EE_DB_SIGNATURE_OFFSET();

    if ((result = EEPROM::ReadWrite(address, (UINT8_t *)&db_signature, sizeof(db_signature), EEOP_READ)) == EE_OK) {
        if (db_signature == DB_SIGNATURE) {
            result = EE_OK;
        } else {
            DB_ZeroFillEE();
            ReinitFactorySettings();
        }
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ReadWriteAppInfo(EEBootAppCommonDataStruct_t *pAppInfo,
                                                EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_INVALIDSOURCE;
    if (pAppInfo) {
        UINT16_t address = EE_DEV_SHARED_DATA_OFFSET() + EE_APP_OFFSET();
        result = EEPROM::ReadWrite(address, (UINT8_t *)pAppInfo, sizeof(*pAppInfo), operation);
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ReadWriteBootInfo(EEBootAppCommonDataStruct_t *pBootInfo,
                                                 EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_INVALIDSOURCE;
    if (pBootInfo) {
        UINT16_t address = EE_DEV_SHARED_DATA_OFFSET() + EE_BOOT_OFFSET();
        result = EEPROM::ReadWrite(address, (UINT8_t *)pBootInfo, sizeof(*pBootInfo), operation);
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ReadWriteProductInfo(EEDeviceProductData_t *pProductInfo,
                                                    EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_INVALIDSOURCE;
    if (pProductInfo) {
        UINT16_t address = EE_DEV_PRODUCT_DATA_OFFSET();
        result = EEPROM::ReadWrite(address, (UINT8_t *)pProductInfo, sizeof(*pProductInfo), operation);
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ReadWriteDatabaseSignature(UINT32_t *pSignature,
                                                          EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_INVALIDSOURCE;
    if (pSignature) {
        UINT16_t address = EE_DB_SIGNATURE_OFFSET();
        result = EEPROM::ReadWrite(address, (UINT8_t *)pSignature, sizeof(*pSignature), operation);
    }
    return result;
}

EE_ReturnCode_t EEDatabase::DB_ReadWriteSensorInfo(UINT8_t SensorIndex,
                                                   EESensorData_t *pSensorInfo,
                                                   EE_Opcode_t operation) {
    EE_ReturnCode_t result = EE_INVALIDSOURCE;
    if (pSensorInfo) {
        if (SensorIndex < NUM_SENSORS) {
            UINT16_t address = EE_SENSORDATA_OFFSET(SensorIndex);
            result = EEPROM::ReadWrite(address, (UINT8_t *)pSensorInfo, sizeof(*pSensorInfo), operation);
        } else {
            result = EE_INVALIDDATA;
        }
    }
    return result;
}


