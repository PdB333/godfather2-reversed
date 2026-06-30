// FUNC_NAME: ObjectNode::registerInGlobalList

void __thiscall ObjectNode::registerInGlobalList(int thisPtr, int* lockPtr) {
    // Acquire lock on the global list mutex
    MutexLock(lockPtr); // 0x0046c6a0

    int* globalListBase = (int*)DAT_011298cc; // Global dynamic array container

    // Check if lockPtr points to the global mutex (recursive lock check?)
    if (*lockPtr == DAT_0120e93c) { // DAT_0120e93c likely a mutex handle
        // Resize array if needed
        int* arrayPtr = (int*)(globalListBase + 0x18); // +0x18: pointer to element array
        int curSize = *(int*)(globalListBase + 0x1c);  // +0x1c: number of elements
        int capacity = *(int*)(globalListBase + 0x20); // +0x20: capacity
        if (curSize == capacity) {
            int newCapacity = (capacity == 0) ? 1 : capacity * 2;
            ResizeGlobalArray(newCapacity); // 0x006e9220
        }

        // Add this object (the containing object at thisPtr - 0x3c) to the array
        int idx = *(int*)(globalListBase + 0x1c);
        *(int*)(*arrayPtr + idx * 4) = thisPtr - 0x3c; // Store pointer to the base object
        *(int*)(globalListBase + 0x1c) = idx + 1;      // Increment size
    }

    // If object type is 0 or 0x48, also register in hash table
    int typeField = *(int*)(thisPtr + 0x28); // +0x28: type identifier
    if (typeField == 0 || typeField == 0x48) {
        int key = GetHashKey(thisPtr + 0x18, 0); // 0x00445ff0: generate hash from subobject at +0x18
        int* insertedNode = nullptr;
        char success = InsertIntoHashTable(key, 0xa7039c8, &insertedNode); // 0x004480d0
        if (success) {
            IncrementRefCount((uint)insertedNode); // 0x006e9170
        }
    }

    // Release the global mutex
    UnlockMutex((int*)&DAT_0120e93c); // 0x004086d0
}