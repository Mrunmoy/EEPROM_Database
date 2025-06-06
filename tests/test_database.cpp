#include <gtest/gtest.h>
extern "C" {
#include "database.h"
#include "EEPROM_Mapping.h"
}

TEST(EEReadWrite, WriteAndReadBack) {
    const UINT16_t addr = 0;
    UINT8_t write_buf[16];
    UINT8_t read_buf[16];

    for (UINT8_t i = 0; i < 16; ++i) {
        write_buf[i] = i;
        read_buf[i] = 0;
    }

    EXPECT_EQ(EE_ReadWrite(addr, write_buf, sizeof(write_buf), EEOP_WRITE), EE_OK);
    EXPECT_EQ(EE_ReadWrite(addr, read_buf, sizeof(read_buf), EEOP_READ), EE_OK);

    for (int i = 0; i < 16; ++i) {
        EXPECT_EQ(write_buf[i], read_buf[i]);
    }
}

TEST(Database, InitializeSetsSignature) {
    UINT32_t signature = 0;
    EXPECT_EQ(DB_Initialize(), EE_OK);
    UINT16_t addr = EE_DB_SIGNATURE_OFFSET();
    EXPECT_EQ(EE_ReadWrite(addr, (UINT8_t*)&signature, sizeof(signature), EEOP_READ), EE_OK);
    EXPECT_EQ(signature, EE_DATABASE_SIGNATURE);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
