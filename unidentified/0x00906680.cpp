// FUN_00906680: StreamManager::StreamManager
undefined4* __thiscall StreamManager::StreamManager(StreamManager* this, uint param_2) {
    // Call base class constructor (e.g., EntityDataManager::constructor)
    FUN_0046c590(param_2);

    // Set vtable pointers (multiple inheritance, offsets: 0x00, 0x3C, 0x48, 0x50)
    this->vtableBase = &PTR_FUN_00d82734;                 // offset 0x00
    this[0x0F] = (int*)&PTR_LAB_00d82724;                 // offset 0x3C (interface A)
    this[0x12] = (int*)&PTR_LAB_00d82720;                 // offset 0x48 (interface B)
    this[0x14] = (int*)&PTR_LAB_00d8271c;                 // offset 0x50 (interface C, overwrites previous)

    // Zero out metadata fields (mostly 16-bit counters/flags)
    this->field_0x58 = 0;                                 // +0x58 (int)
    *(uint16*)((uint8*)this + 0x5C) = 0;                  // +0x5C (short)
    *(uint16*)((uint8*)this + 0x5E) = 0;                  // +0x5E (short)
    this->field_0x60 = 0;                                 // +0x60 (int)
    *(uint16*)((uint8*)this + 0x64) = 0;                  // +0x64 (short)
    *(uint16*)((uint8*)this + 0x66) = 0;                  // +0x66 (short)

    // Copy a default 32KB buffer from global if available
    if (gDefaultBuffer != 0) {
        FUN_00408900((uint8*)this + 0x3C, gDefaultBuffer, 0x8000); // memcpy( bufferOffset, gDefaultBuffer, 32768 )
    }
    return this;
}