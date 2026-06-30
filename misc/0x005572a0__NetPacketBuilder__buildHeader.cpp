// FUNC_NAME: NetPacketBuilder::buildHeader
void __fastcall NetPacketBuilder::buildHeader(Object* connection, uint param2)
{
    // Stack local structure for packet header construction
    uint8_t localBuffer[12];                // +0x00
    int32_t field0 = 0;                    // +0x0C
    int32_t field1 = 0;                    // +0x1C
    int32_t field2 = 0;                    // +0x2C
    uint32_t globalValue = DAT_00e2b1a4;   // +0x3C (some global constant)
    uint32_t stackParam = 1;               // +0x54 (stored as 1)
    uint8_t* bufPtr = localBuffer;

    // Call virtual function on the Connection object (vtable offset 0x90)
    (**(code **)(*connection + 0x90))();

    // Write four values into some data structure pointed by unaff_ESI
    // Offsets: +0x30, +0x34, +0x38, +0x3C
    *(uint32_t*)(unaff_ESI + 0x30) = uStack_2c;   // from stack
    *(uint32_t*)(unaff_ESI + 0x34) = uStack_28;   // from stack
    *(uint32_t*)(unaff_ESI + 0x38) = field2;      // local_24
    *(uint32_t*)(unaff_ESI + 0x3C) = globalValue; // DAT_00e2b1a4

    // Serialize the local buffer via another function
    FUN_004b59d0(&bufPtr);
    return;
}