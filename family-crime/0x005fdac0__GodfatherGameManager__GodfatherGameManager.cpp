// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
// Function address: 0x005fdac0 - Constructor that zeros a large block of fields and sets up function pointers. 
// Object size at least 0x140 bytes (0x50 * 4). Likely initializes a manager with multiple sub-arrays and callbacks.

GodfatherGameManager::GodfatherGameManager()
{
    // Zero the base fields (first 4 dwords)
    this->field00 = 0;
    this->field04 = 0;
    this->field08 = 0;
    this->field0C = 0;

    // Zero fields at offset 0x30 (4 dwords)
    this->field30 = 0;
    this->field34 = 0;
    this->field38 = 0;
    this->field3C = 0;

    // Zero byte at offset 0x40
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x40) = 0;

    // Clear the first block of 23 fields starting at offset 0x44 (0x11 * 4) up to offset 0x9C (0x27 * 4)
    uint32_t* block1 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x44);
    for (int i = 0; i < 23; i++) {
        block1[i] = 0;
    }

    // Set up function pointers at offset 0xA0 and 0xA8
    this->funcPtrA0 = reinterpret_cast<void*>(0x005fe070);   // callback 1
    this->fieldA4 = 0;
    this->funcPtrA8 = reinterpret_cast<void*>(0x005fda60);   // callback 2
    this->fieldAC = 0;
    this->fieldB0 = 0;
    this->fieldB4 = 0;
    this->fieldB8 = 0;
    this->fieldBC = 0;

    // Clear 12 fields from offset 0xE0 (0x38 * 4) to 0x10C (0x43 * 4)
    uint32_t* block2 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0xE0);
    for (int i = 0; i < 12; i++) {
        block2[i] = 0;
    }

    // Set flag at offset 0x110 to 0x9000
    this->field110 = 0x9000;

    // Zero next four fields at 0x114, 0x118, 0x11C, 0x120
    this->field114 = 0;
    this->field118 = 0;
    this->field11C = 0;
    this->field120 = 0;

    // Zero fields at offset 0x60 (4 dwords)
    uint32_t* block3 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x60);
    for (int i = 0; i < 4; i++) {
        block3[i] = 0;
    }

    // Zero fields at offset 0xD0 (4 dwords)
    uint32_t* block4 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0xD0);
    for (int i = 0; i < 4; i++) {
        block4[i] = 0;
    }

    // Zero fields at offset 0x20 (4 dwords)
    uint32_t* block5 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x20);
    for (int i = 0; i < 4; i++) {
        block5[i] = 0;
    }

    // Possibly free a sub-object if the pointer at offset 0x44 is non-zero (though we just zeroed it)
    uint32_t* subObjPtr = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x44);
    if (*subObjPtr != 0) {
        FUN_004daf90(subObjPtr);   // destructor/free for sub-object
        *subObjPtr = 0;
    }

    // Zero fields at offset 0x10 (4 dwords)
    uint32_t* block6 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x10);
    for (int i = 0; i < 4; i++) {
        block6[i] = 0;
    }

    // Zero fields at offset 0x130 (4 dwords)
    uint32_t* block7 = reinterpret_cast<uint32_t*>(reinterpret_cast<uintptr_t>(this) + 0x130);
    for (int i = 0; i < 4; i++) {
        block7[i] = 0;
    }
}