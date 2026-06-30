// FUN_004248a0: registerHandler
void registerHandler()
{
    // Local struct for initialization parameters (size 0x170 object)
    struct InitParams {
        int field0;     // +0x00: usually 2
        void* field1;   // +0x04: usually 0x10 (maybe flags?)
        int field2;     // +0x08: initially 0, later set to 8
    };
    InitParams params;
    params.field0 = 2;
    params.field1 = (void*)0x10;
    params.field2 = 0;

    // Allocate 0x170 bytes (size of an engine object?) 
    int allocResult = FUN_009c8ed0(0x170, &params);
    if (allocResult != 0) {
        FUN_004249d0(); // call constructor on the allocated object
    }

    // Global handler table
    // Each entry: 12 bytes: uint32 reserved (offset 0), uint32 handlerFunc (offset 4), uint32 handlerType (offset 8)
    static HandlerEntry* s_handlerTable = (HandlerEntry*)&DAT_01222330; // base at 0x01222330
    static int s_handlerCount = *(int*)&DAT_012224a8; // count at 0x012224a8

    params.handlerType = 8; // after CONCAT31 trick, low byte becomes 8

    // Validate existing entries: all types must be <= 8
    for (int i = 0; i < s_handlerCount; i++) {
        if ((s_handlerTable[i].handlerType & 0xFF) > 8) {
            FUN_00609bf0(); // error/assertion failure
            return;
        }
    }

    // Add new entry if table not full (max 32)
    if (s_handlerCount < 32) {
        int idx = s_handlerCount;
        // Write 8 bytes at entry start: first uint32 = 0, second uint32 = address 0x00424870 (callback function)
        *(uint64_t*)&s_handlerTable[idx] = 0x0042487000000000ULL;
        // Write type field at offset 8 (within 12-byte entry)
        s_handlerTable[idx].handlerType = params.handlerType; // 8
        s_handlerCount++;
    }
}