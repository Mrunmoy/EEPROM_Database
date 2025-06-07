#include <gtest/gtest.h>
#include <string.h>
#include "EEDatabase.hpp"

TEST(EEReadWrite, WriteAndReadBack) {
    const UINT16_t addr = 0;
    UINT8_t write_buf[16];
    UINT8_t read_buf[16];

    for (UINT8_t i = 0; i < 16; ++i) {
        write_buf[i] = i;
        read_buf[i] = 0;
    }

    EXPECT_EQ(EEPROM::ReadWrite(addr, write_buf, sizeof(write_buf), EEOP_WRITE), EE_OK);
    EXPECT_EQ(EEPROM::ReadWrite(addr, read_buf, sizeof(read_buf), EEOP_READ), EE_OK);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(write_buf[i], read_buf[i]);
    }
}

TEST(Database, InitializeSetsSignature) {
    UINT32_t signature = 0;
    EXPECT_EQ(EEDatabase::DB_Initialize(), EE_OK);
    UINT16_t addr = EE_DB_SIGNATURE_OFFSET();
    EXPECT_EQ(EEPROM::ReadWrite(addr, (UINT8_t*)&signature, sizeof(signature), EEOP_READ), EE_OK);
    EXPECT_EQ(signature, EE_DATABASE_SIGNATURE);
}

TEST(EEReadWrite, InvalidOperation) {
    UINT8_t buf[1] = {0};
    EXPECT_EQ(EEPROM::ReadWrite(0, buf, sizeof(buf), (EE_Opcode_t)EEOP_MAX), EE_INVALIDOPERATION);
}

TEST(EEReadWrite, InvalidAddress) {
    UINT8_t buf[2] = {1, 2};
    UINT16_t addr = EE_DATABASE_SIZE - 1;
    EXPECT_EQ(EEPROM::ReadWrite(addr, buf, sizeof(buf), EEOP_WRITE), EE_INVALIDADDRESS);
}

TEST(EEReadWrite, CrossPageWriteRead) {
    const UINT16_t addr = EE_PAGESIZE - 8;
    UINT8_t write_buf[40];
    UINT8_t read_buf[40];
    for (int i = 0; i < 40; ++i) {
        write_buf[i] = static_cast<UINT8_t>(i + 1);
        read_buf[i] = 0;
    }
    EXPECT_EQ(EEPROM::ReadWrite(addr, write_buf, sizeof(write_buf), EEOP_WRITE), EE_OK);
    EXPECT_EQ(EEPROM::ReadWrite(addr, read_buf, sizeof(read_buf), EEOP_READ), EE_OK);
    for (int i = 0; i < 40; ++i) {
        EXPECT_EQ(write_buf[i], read_buf[i]);
    }
}

TEST(Database, ZeroFillSucceeds) {
    EXPECT_EQ(EEDatabase::DB_ZeroFillEE(), EE_OK);
}

TEST(Database, DatabaseSignatureNull) {
    EXPECT_EQ(EEDatabase::DB_ReadWriteDatabaseSignature(NULL, EEOP_READ), EE_INVALIDSOURCE);
}

TEST(Database, DatabaseSignatureWriteRead) {
    UINT32_t sig_write = 0x12345678;
    EXPECT_EQ(EEDatabase::DB_ReadWriteDatabaseSignature(&sig_write, EEOP_WRITE), EE_OK);
    UINT32_t sig_read = 0;
    EXPECT_EQ(EEDatabase::DB_ReadWriteDatabaseSignature(&sig_read, EEOP_READ), EE_OK);
    EXPECT_EQ(sig_write, sig_read);
}

TEST(Database, AppInfoNull) {
    EXPECT_EQ(EEDatabase::DB_ReadWriteAppInfo(NULL, EEOP_READ), EE_INVALIDSOURCE);
}

TEST(Database, AppInfoWriteRead) {
    EEBootAppCommonDataStruct_t app_write{};
    app_write.rev.major_ver = 1;
    app_write.rev.major_rev = 2;
    app_write.rev.minor_ver = 3;
    app_write.rev.minor_rev = 4;
    app_write.forced_initiated = B_TRUE;
    app_write.must_self_check = B_FALSE;
    app_write.signature = 0xDEADBEEF;
    app_write.signature_address = 0x1000;
    app_write.start_address = 0x2000;
    app_write.alt_start_address = 0x3000;
    app_write.install_date.tm_year = 2023;
    app_write.checksum = 0xAA55AA55;
    EXPECT_EQ(EEDatabase::DB_ReadWriteAppInfo(&app_write, EEOP_WRITE), EE_OK);
    EEBootAppCommonDataStruct_t app_read{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteAppInfo(&app_read, EEOP_READ), EE_OK);
    EXPECT_EQ(app_read.signature, app_write.signature);
    EXPECT_EQ(app_read.start_address, app_write.start_address);
    EXPECT_EQ(app_read.checksum, app_write.checksum);
}

TEST(Database, BootInfoNull) {
    EXPECT_EQ(EEDatabase::DB_ReadWriteBootInfo(NULL, EEOP_READ), EE_INVALIDSOURCE);
}

TEST(Database, BootInfoWriteRead) {
    EEBootAppCommonDataStruct_t boot_write{};
    boot_write.rev.major_ver = 5;
    boot_write.rev.major_rev = 6;
    boot_write.rev.minor_ver = 7;
    boot_write.rev.minor_rev = 8;
    boot_write.forced_initiated = B_FALSE;
    boot_write.must_self_check = B_TRUE;
    boot_write.signature = 0xAABBCCDD;
    boot_write.signature_address = 0x4000;
    boot_write.start_address = 0x5000;
    boot_write.alt_start_address = 0x6000;
    boot_write.install_date.tm_year = 2024;
    boot_write.checksum = 0x55AA55AA;
    EXPECT_EQ(EEDatabase::DB_ReadWriteBootInfo(&boot_write, EEOP_WRITE), EE_OK);
    EEBootAppCommonDataStruct_t boot_read{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteBootInfo(&boot_read, EEOP_READ), EE_OK);
    EXPECT_EQ(boot_read.signature, boot_write.signature);
    EXPECT_EQ(boot_read.start_address, boot_write.start_address);
    EXPECT_EQ(boot_read.checksum, boot_write.checksum);
}

TEST(Database, ProductInfoNull) {
    EXPECT_EQ(EEDatabase::DB_ReadWriteProductInfo(NULL, EEOP_READ), EE_INVALIDSOURCE);
}

TEST(Database, ProductInfoWriteRead) {
    EEDeviceProductData_t prod_write{};
    prod_write.dev_id.pc0 = 1;
    prod_write.dev_id.pc1 = 2;
    prod_write.dev_id.pc2 = 3;
    prod_write.dev_id.pc3 = 4;
    strcpy(prod_write.model_str, "MODEL");
    strcpy(prod_write.name_str, "NAME");
    strcpy(prod_write.product_str, "PRODUCT");
    prod_write.mfg_date.tm_year = 2025;
    EXPECT_EQ(EEDatabase::DB_ReadWriteProductInfo(&prod_write, EEOP_WRITE), EE_OK);
    EEDeviceProductData_t prod_read{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteProductInfo(&prod_read, EEOP_READ), EE_OK);
    EXPECT_STREQ(prod_read.model_str, prod_write.model_str);
    EXPECT_STREQ(prod_read.name_str, prod_write.name_str);
    EXPECT_STREQ(prod_read.product_str, prod_write.product_str);
}

TEST(Database, SensorInfoNull) {
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(0, NULL, EEOP_READ), EE_INVALIDSOURCE);
}

TEST(Database, SensorInfoInvalidIndex) {
    EESensorData_t dummy{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(NUM_SENSORS, &dummy, EEOP_WRITE), EE_INVALIDDATA);
}

TEST(Database, SensorInfoWriteRead) {
    EESensorData_t sensor_write{};
    sensor_write.address = 0x12;
    sensor_write.detected = B_TRUE;
    sensor_write.data.datetimestamp = 1234;
    sensor_write.data.value = 56.78f;
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(0, &sensor_write, EEOP_WRITE), EE_OK);
    EESensorData_t sensor_read{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(0, &sensor_read, EEOP_READ), EE_OK);
    EXPECT_EQ(sensor_read.address, sensor_write.address);
    EXPECT_EQ(sensor_read.detected, sensor_write.detected);
    EXPECT_EQ(sensor_read.data.datetimestamp, sensor_write.data.datetimestamp);
    EXPECT_FLOAT_EQ(sensor_read.data.value, sensor_write.data.value);
}

TEST(Database, SensorInfoWriteReadHighIndex) {
    EESensorData_t sensor_write{};
    sensor_write.address = 0x34;
    sensor_write.detected = B_TRUE;
    sensor_write.data.datetimestamp = 4321;
    sensor_write.data.value = 11.22f;
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(NUM_SENSORS - 1, &sensor_write, EEOP_WRITE), EE_OK);
    EESensorData_t sensor_read{};
    EXPECT_EQ(EEDatabase::DB_ReadWriteSensorInfo(NUM_SENSORS - 1, &sensor_read, EEOP_READ), EE_OK);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
