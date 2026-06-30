// FUN_NAME: ObjectPoolManager::clearActiveObjects
void ObjectPoolManager::clearActiveObjects() {
    // Free linked list of pool nodes starting from offset +0x11c
    for (int poolNode = *(int*)((char*)this + 0x11c); poolNode != 0; poolNode = *(int*)(poolNode + 0x10)) {
        int childList = *(int*)(poolNode + 0x18);
        *(int*)(poolNode + 0x18) = 0; // clear child list pointer
        while (childList != 0) {
            int nextChild = *(int*)(childList + 0xc);
            releaseObject(childList); // FUN_009c8eb0
            childList = nextChild;
        }
    }

    // Base address of array of 1024 entries (0xC000 bytes, stride 0x30)
    int* baseArray = *(int**)((char*)this + 0x214);
    int* indexArray = *(int**)((char*)this + 0x1fc); // pointer array for swaps
    int maxCount = *(int*)((char*)this + 0x200);
    int currentCount = *(int*)((char*)this + 0x204);

    for (int slotOffset = 0; slotOffset < 0xC000; slotOffset += 0x30) {
        // Each slot has a field at offset 0x2c which stores an index into the array (or sentinel 0x400)
        int* slotBase = (int*)((char*)baseArray + slotOffset);
        int slotIndex = *(slotBase + 0x2c / 4); // offset +0x2c

        if (slotIndex < currentCount) {
            // This slot is currently active, remove it
            onElementRemoved(slotBase); // FUN_006501f0
            *(slotBase + 0x8 / 4) = 0; // clear field at offset +0x08

            int idx = slotIndex;
            int* idxPtr = slotBase + 0x2c/4; // pointer to index field

            if (idx != 0x400 && idx < maxCount) {
                *(slotBase + 0x4 / 4) = 0; // clear field at offset +0x04
                onElementDeactivated(); // FUN_0064d500
            }

            currentCount--;
            *(int*)((char*)this + 0x204) = currentCount;

            // If the element we removed is not the last one, swap it with the last active element
            if (slotIndex != currentCount) {
                // Get the last active element's address
                int lastIndex = currentCount;
                int lastElementPtr = *(int*)((char*)indexArray + lastIndex * 4);
                int* lastSlot = (int*)((char*)baseArray + lastElementPtr);

                // Update last element's index to match the slot we just vacated
                *(lastSlot + 0x2c / 4) = slotIndex;
                // Move the pointer of the last element to the vacated slot's position in the index array
                *(int*)((char*)indexArray + slotIndex * 4) = lastElementPtr;
                // Place the vacated slot into the last position (though it's now dead)
                *(int*)((char*)indexArray + currentCount * 4) = (int)slotBase;
                // Update the slot's own index to the last position (which will be overwritten by next removal)
                *(slotBase + 0x2c / 4) = currentCount;
            }
        }
    }
}