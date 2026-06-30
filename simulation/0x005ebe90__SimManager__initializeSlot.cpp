// FUNC_NAME: SimManager::initializeSlot
// Address: 0x005ebe90
// Initializes a slot at the given index. The slot is part of an array at offset 0x5A0 from this.
// Each slot is 0xF8 bytes. The slot's transform and data are set from the base object pointer at +0x580.
// Returns 1 on success, 0 on failure or if already initialized.

struct Slot {
    uint8_t pad_0x00[0xA4];
    uint32_t field_0xA4; // used as parameter in transform function
    uint8_t pad_0xA8[0x08];
    uint64_t field_0xB0; // copied from base object +8
    uint8_t initialized; // +0xB8
};

uint __thiscall SimManager::initializeSlot(int thisPtr, ushort slotIndex)
{
    Slot* slot = reinterpret_cast<Slot*>(thisPtr + 0x5A0 + slotIndex * 0xF8);
    uint result;

    if (!slot->initialized) {
        int factoryResult = FUN_005e9d10(); // create or find a supporting object
        if (factoryResult != 0) {
            // Setup a local transform structure
            TransformData localTransform;
            FUN_00c9cbe0(*(void**)(thisPtr + 0x580), *(void**)(factoryResult + 0x10), 0, &localTransform);
            localTransform = {0};
            localTransform.someValue = slot->field_0xA4;
            localTransform.zero1 = 0;
            localTransform.zero2 = 0;
            FUN_00c9eac0();            // push matrix stack
            FUN_00c9cd40(0, &localTransform); // apply transform
            FUN_00c9eae0();            // pop matrix stack

            // Copy 8 bytes from base object (at offset 8) into slot
            void* baseObj = *(void**)(thisPtr + 0x580);
            slot->field_0xB0 = *reinterpret_cast<uint64_t*>(reinterpret_cast<uint8_t*>(baseObj) + 8);
            slot->initialized = 1;
            result = 1;
        }
        else {
            result = 0;
        }
    }
    else {
        result = 0;
    }
    return result;
}