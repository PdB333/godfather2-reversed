// FUNC_NAME: AudioDataManager::AudioDataManager

struct AudioDataManager {
    // +0x00: vtable pointer
    void** vtable;

    // +0x3C: pointer to first callback table
    void* callbackTable1;

    // +0x48: pointer to second callback table
    void* callbackTable2;

    // +0x50: integer field
    int field50;

    // +0x54: short field (first of two shorts)
    unsigned short field54;

    // +0x56: short field (second of two shorts)
    unsigned short field56;

    // +0x58-0x64: array of 4 ints
    int array1[4];

    // +0x68-0x74: array of 4 ints
    int array2[4];

    // +0x78-0x84: array of 4 ints
    int array3[4];

    // +0x88: single int
    int field88;
};

__thiscall AudioDataManager::AudioDataManager(void* baseInitParam) {
    // Call base class initialization (FUN_0046c590)
    BaseClassInit(baseInitParam);

    // Set vtable and callback tables
    vtable = &PTR_FUN_00d5fe00; // +0x00
    callbackTable1 = &PTR_LAB_00d5fdf0; // +0x3C
    callbackTable2 = &PTR_LAB_00d5fdec; // +0x48

    // Initialize fields to zero
    field50 = 0;           // +0x50
    field54 = 0;           // +0x54 (short)
    field56 = 0;           // +0x56 (short)

    // Zero out three arrays of 4 ints each
    for (int i = 0; i < 4; i++) {
        array1[i] = 0;     // +0x58-0x64
        array2[i] = 0;     // +0x68-0x74
        array3[i] = 0;     // +0x78-0x84
    }

    field88 = 0;           // +0x88

    return this;
}