// FUNC_NAME: NetSession::initEncryptionKeys
void __fastcall NetSession::initEncryptionKeys(NetSession* thisPtr)
{
    // Initialize encryption key table at offset +0x2A78
    // This appears to be a 40-entry (0xA0 bytes) table of 32-bit key values
    // used for packet encryption/decryption in the networking layer
    
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A78) = 0xFE451260;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A7C) = 0x20C508CB;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A80) = 0x3191F9D1;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A84) = 0x8543EDED;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A88) = 0xE8170D13;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A8C) = 0x3C1DA0F0;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A90) = 0x53FC0610;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A94) = 0xD0910886;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A98) = 0xAFE130E7;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2A9C) = 0xD21E7820;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AA0) = 0x9AAA232E;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AA4) = 0x8DF5DA1E;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AA8) = 0x704F0D05;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AAC) = 0x911CE631;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AB0) = 0x5A501DFB;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AB4) = 0xA37CD31A;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AB8) = 0x53698B6B;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2ABC) = 0x201CA3FA;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AC0) = 0xB315D1E8;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AC4) = 0x7FC8EA77;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AC8) = 0xE2D8CA3D;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2ACC) = 0xAF8BE2CC;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AD0) = 0x3E484796;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AD4) = 0x0AFB6025;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AD8) = 0xDA00FF46;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2ADC) = 0xA6B417D5;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AE0) = 0xEFA95C36;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AE4) = 0xBC5C74C5;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AE8) = 0x2AF84DD8;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AEC) = 0x491364B1;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AF0) = 0xCC70D532;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AF4) = 0xF0BD5FFB;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AF8) = 0xB8B5BDD6;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2AFC) = 0x8184171D;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B00) = 0x650BC395;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B04) = 0x019C8608;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B08) = 0x9CE37D63;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B0C) = 0x291312A6;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B10) = 0x159D6273;
    *(uint32_t*)((uint8_t*)thisPtr + 0x2B14) = 0x6DCE9423;
}