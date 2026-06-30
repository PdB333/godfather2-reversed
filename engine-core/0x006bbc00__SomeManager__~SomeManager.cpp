// FUNC_NAME: SomeManager::~SomeManager
void __fastcall SomeManager::~SomeManager(SomeManager* this)
{
    // Set vtable pointers to the destructor vtables (on destruction)
    this->vtable = &PTR_FUN_00d5e76c;
    this->field_3C = &PTR_LAB_00d5e75c;  // +0x3C
    this->field_48 = &PTR_LAB_00d5e758;  // +0x48
    this->field_80 = &PTR_LAB_00d5e73c;  // +0x80 (sub-object vtable?)

    // Check bit 29 of flags at +0x84
    if (((uint)this->flags >> 0x1d & 1) != 0) {
        subObjectDestructor(&this->subObject); // +0x80
    }

    // Call base class destructor
    baseClassDestructor(); // FUN_006bbb40

    // Clean up global list/manager reference
    globalListCleanup(&DAT_012069c4); // FUN_004086d0

    // Process fixed-size array of 10 slots (each 12 bytes) at +0xBC
    uint* slot = this->slotList; // +0x2f*4
    int slotCount = 10;
    do {
        slotCleanup(slot);    // FUN_004086d0
        slotReset(slot);      // FUN_00408310
        slot += 3;            // each slot is 3 ints (12 bytes)
        slotCount--;
    } while (slotCount != 0);

    // Clean up optional pointer at +0x9C
    if (this->somePointer != 0) { // +0x27*4
        somePointerDestructor(); // FUN_006b5790
    }

    // Delete another pointer at +0xAC
    if (this->anotherPointer != 0) { // +0x2b*4
        operatorDelete(this->anotherPointer); // FUN_009c8f10
    }

    // Delete dynamic array at +0xA0 (count at +0xA4)
    int count = this->dynamicArrayCount - 1;
    if (count >= 0) {
        int idx = count * 0x18; // each element 24 bytes
        do {
            if (*(int*)(this->dynamicArray + idx) != 0) {
                elementDestructor(this->dynamicArray + idx); // FUN_004daf90
            }
            count--;
            idx -= 0x18;
        } while (count >= 0);
    }

    // Free the array pointer
    if (this->dynamicArray != 0) {
        operatorDelete(this->dynamicArray); // FUN_009c8f10
    }

    // Final cleanup
    finalCleanup(); // FUN_006bcd70
}