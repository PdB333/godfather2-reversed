// FUNC_NAME: SequencePlayer::reset
void SequencePlayer::reset() {
    // +0x490: clear some byte flag
    *(uint8_t*)((uint8_t*)this + 0x490) = 0;
    // +0x48C: clear dword
    *(uint32_t*)((uint8_t*)this + 0x48C) = 0;

    // Release two global objects (likely shared pointers)
    releaseSomething1();
    releaseSomething1();

    // Clear and release a dynamically allocated resource block
    if (*(void**)((uint8_t*)this + 0x494) != nullptr) {
        (*(void(__thiscall**)(void*))(*(uint32_t*)((uint8_t*)this + 0x4A0)))(*(void**)((uint8_t*)this + 0x494));
    }
    *(uint32_t*)((uint8_t*)this + 0x494) = 0;
    *(uint32_t*)((uint8_t*)this + 0x49C) = 0;
    *(uint32_t*)((uint8_t*)this + 0x498) = 0;

    releaseManagedResources();

    // Array of 4 SequenceItem structures, each 108 bytes, starting at offset 0x1C
    static const char* sequenceItemNames[] = { "SequenceItem1", "SequenceItem2", "SequenceItem3", "SequenceItem4" };
    SequenceItem* items = (SequenceItem*)((uint8_t*)this + 0x1C);
    for (int i = 0; i < 4; ++i) {
        SequenceItem& item = items[i];

        // Clear and release first sub-object group (offset -24 relative to item start, i.e. item.pData1)
        if (item.pData1 != nullptr) {
            (*(void(__thiscall**)(void*))item.dtor1)(item.pData1);
        }
        item.pData1 = nullptr;
        item.field0 = 0;       // +0x0 (where field0 is the first of three)
        item.field4 = 0;       // +0x4

        // Second sub-object group (offset -8 from item start)
        if (item.pData2 != nullptr) {
            (*(void(__thiscall**)(void*))item.dtor2)(item.pData2);
        }
        item.pData2 = nullptr;
        item.field8 = 0;       // +0x8
        item.fieldC = 0;       // +0xC

        // Third sub-object group (offset +8 from item start)
        if (item.pData3 != nullptr) {
            (*(void(__thiscall**)(void*))item.dtor3)(item.pData3);
        }
        item.pData3 = nullptr;
        item.field10 = 0;      // +0x10
        item.field14 = 0;      // +0x14

        // Fourth sub-object group (offset +24 from item start)
        if (item.pData4 != nullptr) {
            (*(void(__thiscall**)(void*))item.dtor4)(item.pData4);
        }
        item.pData4 = nullptr;
        item.field18 = 0;      // +0x18
        item.field1C = 0;      // +0x1C

        // Reinitialize item state (offset +0x3C relative to item)
        item.field3C = 0;                               // +0x3C
        item.field40 = globalPtr1;                      // +0x40 from global DAT_00e2b04c
        item.field44 = globalPtr2;                      // +0x44 from global DAT_00e2b050
        item.field48_byte = 1;                          // +0x48 byte flag
        item.field49 = 0;                               // +0x49
        item.field4A = 0;                               // +0x4A

        // Release the sequence item name string reference
        releaseStringReference(sequenceItemNames[i]);
    }

    // Zero out first field (vtable? or base flags)
    *(uint32_t*)this = 0;
}