// FUNC_NAME: NetConnection::initializeFromPacket
void __fastcall NetConnection::initializeFromPacket(int param_1)
{
    // local buffer for packet data (0x400 bytes)
    char packetBuffer[1028]; // actually 0x400 = 1024, but decompiled shows 1028? maybe alignment
    char *packetData = packetBuffer;
    int packetSize = 0;
    int someFlag = 0;
    int maxSize = 0x400;
    char terminator = 0;
    int unknown1 = 0x2000;
    int unknown2 = 0x2000;
    int bitCount = 0; // local_524
    char flag1 = 0;
    char flag2 = 0;
    char flag3 = 0;
    char flag4 = 0;
    int unknown3 = 0;
    char **someTable = &PTR_LAB_00e42f38; // global table pointer
    char someByte = 0;

    // Initialize 8 bytes at local_53d (someByte)
    FUN_0064b810(8, &someByte); // likely memset

    // Initialize 0x40 bytes at this+0x133
    FUN_0064b810(0x40, reinterpret_cast<char*>(this) + 0x133);

    // Clear flags at offsets 0x160 and 0x161
    FUN_0064bb50(*reinterpret_cast<char*>(this) + 0x160);
    FUN_0064bb50(*reinterpret_cast<char*>(this) + 0x161);

    // Increment counter at +0x19c
    *reinterpret_cast<int*>(this) + 0x19c += 1;

    // Set value at +0x1a0 from param_1+100
    *reinterpret_cast<int*>(this) + 0x1a0 = *reinterpret_cast<int*>(param_1 + 100);

    // Copy data from param_1+0x5c into packetBuffer, size = (bitCount+7)/8 (but bitCount=0 so size=0? Possibly a bug or missing assignment)
    FUN_00658230(param_1 + 0x5c, packetBuffer, (bitCount + 7) >> 3, 0);

    // Cleanup or finalize
    FUN_0064b440();
}