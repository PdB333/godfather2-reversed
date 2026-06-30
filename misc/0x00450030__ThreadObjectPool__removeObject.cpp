// FUNC_NAME: ThreadObjectPool::removeObject
// Function at 0x00450030: Removes an object from a per-thread fixed-size pool by its ID.
// Pool layout: 1024 slots of 16 bytes each (first int is the object ID), 
// then an int count at offset 0x4000 from the start.
// Pool base is obtained via Thread Local Storage (TLS) using FS:[0x2c], 
// plus an offset from the object's member at +0x68.
// Removal is unordered: the last slot is copied into the hole, then count decremented.
void __thiscall ThreadObjectPool::removeObject(int objectId) {
    // Step 1: Retrieve pool base address from TLS
    // FS:[0x2c] -> pointer to TLS array, then dereference twice, add 8, get base value,
    // then add 0x110 and this->field68 (pool index).
    int* poolBase = (int*)(*(int*)(**(int**)(__readfsdword(0x2c) + 0) + 8) + 0x110 + *(int*)(this + 0x68));

    // Step 2: Get current number of active slots
    int count = poolBase[0x1000]; // count stored at offset 0x4000 bytes
    int index = 0;
    int* currentSlot = poolBase;

    if (count == 0) return;

    // Step 3: Linear search for slot with matching ID
    while (*currentSlot != objectId) {
        index++;
        currentSlot = (int*)((char*)currentSlot + 0x10); // advance 16 bytes
        if (index >= count) return; // not found
    }

    // Step 4: Remove found slot (index < count guaranteed)
    if (index < count - 1) {
        // Slot is not the last; copy last slot over it
        int* lastSlot = (int*)((char*)poolBase + (count - 1) * 16); // last slot
        int* destSlot = (int*)((char*)poolBase + index * 16);
        // Copy 16 bytes (4 ints)
        for (int i = 0; i < 4; i++) {
            *destSlot++ = *lastSlot++;
        }
    }

    // Step 5: Decrement count
    poolBase[0x1000]--;
}