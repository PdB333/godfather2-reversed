// FUNC_NAME: EntityDataManager::registerObject
// Function address: 0x0066e580
// Role: Adds an object pointer to internal registration arrays,
//   storing it in a sequential slot and associating a sub-object pointer
//   from a pre-allocated pool of 0xA0-byte structures.

void __thiscall EntityDataManager::registerObject(void* objectPtr)
{
    // +0x18: current active object pointer
    currentObject = objectPtr;

    // +0x49d08 (uint16): current slot index (copy of next index before increment)
    // +0x49d0a (uint16): next slot index (incremented after each addition)
    currentSlotIndex = nextSlotIndex;
    ++nextSlotIndex;

    // +0x49d00: most recently added object pointer (duplicate of param)
    lastAddedObject = objectPtr;

    // +0x49d10: array of pointers to registered objects (size unknown)
    // Indexed by currentSlotIndex; stores the incoming object pointer.
    objectEntryArray[currentSlotIndex] = objectPtr;

    // +0x49d04 (uint16): slot index into the sub-object pool
    // +0x4a510: array of pointers to sub-objects (each 0xA0 bytes)
    // +0x4ad10: base of sub-object pool (array of 0xA0-byte structures)
    // Store a pointer to the sub-object corresponding to the current slot.
    subObjectPtrArray[currentSlotIndex] =
        &subObjectPool[ currentSubObjectSlot ];
}