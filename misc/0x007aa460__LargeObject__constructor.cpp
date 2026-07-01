// FUNC_NAME: LargeObject::constructor
// Address: 0x007aa460
// This is a constructor for a large object with multiple arrays initialized with debug patterns.
// It sets up vtable, initializes fields, and calls a subobject initializer.

typedef struct LargeObject LargeObject;

// Forward declaration of subobject initializer
void __cdecl initSubObject(void* unknown);

LargeObject* __thiscall LargeObject::constructor(LargeObject* thisObj) {
    uint32_t* pointer;
    int32_t i;

    // +0x04: initialize first field to 1
    thisObj->field_04 = 1;
    // +0x08: second field to 0
    thisObj->field_08 = 0;
    // +0x0C: set pointer to some label (maybe alternate vtable or function table)
    thisObj->field_0C = &PTR_LAB_00d6b928; // +0x0C
    // Global reference to this instance (singleton?)
    DAT_01129954 = thisObj;
    // +0x00: set primary vtable
    thisObj->vtable = &PTR_FUN_00d6b92c;
    // +0x0C: re-set? Actually already set above, but this re-assigns to different pointer?
    thisObj->field_0C = &PTR_LAB_00d6b928; // duplicate? might be intentional

    // Fill array #1 (at offset +0x1C, 44 words) with debug sentinels
    pointer = (uint32_t*)(thisObj + 7); // +0x1C
    i = 10; // 11 iterations (10...0)
    do {
        *pointer = 0xBADBADBA;
        pointer[1] = 0xBEEFBEEF;
        pointer[2] = 0xEAC15A55;
        pointer[3] = 0x91100911;
        pointer += 4;
        i -= 1;
    } while (i >= 0);

    // Fill array #2 (at offset +0xCC, 56 words) with same sentinels
    pointer = (uint32_t*)(thisObj + 0x33); // +0xCC
    i = 0xE; // 14 iterations (0xE...0)
    do {
        *pointer = 0xBADBADBA;
        pointer[1] = 0xBEEFBEEF;
        pointer[2] = 0xEAC15A55;
        pointer[3] = 0x91100911;
        pointer += 4;
        i -= 1;
    } while (i >= 0);

    // Initialize some global subobject
    initSubObject(&DAT_01206940);

    // +0x10, +0x14, +0x18: set to 0
    thisObj->field_10 = 0;
    thisObj->field_14 = 0;
    thisObj->field_18 = 0;

    // Zero array #3 (starting at +0x24, 44 words)
    pointer = (uint32_t*)(thisObj + 9); // +0x24
    i = 0xB; // 11 iterations
    do {
        pointer[-2] = 0;
        pointer[-1] = 0;
        *pointer = 0;
        pointer[1] = 0;
        pointer += 4;
        i -= 1;
    } while (i != 0);

    // Zero array #4 (starting at +0xD4, 60 words)
    pointer = (uint32_t*)(thisObj + 0x35); // +0xD4
    i = 3; // 3 iterations
    do {
        pointer[-2] = 0;
        pointer[1] = 0;
        *pointer = 0;
        pointer[-1] = 0;
        pointer[5] = 0;
        pointer[4] = 0;
        pointer[3] = 0;
        pointer[2] = 0;
        pointer[9] = 0;
        pointer[8] = 0;
        pointer[7] = 0;
        pointer[6] = 0;
        pointer[0xD] = 0;
        pointer[0xC] = 0;
        pointer[0xB] = 0;
        pointer[0xA] = 0;
        pointer[0x11] = 0;
        pointer[0x10] = 0;
        pointer[0xF] = 0;
        pointer[0xE] = 0;
        pointer += 0x14; // 20 words per block
        i -= 1;
    } while (i != 0);

    return thisObj;
}