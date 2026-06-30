// FUN_004c2790: ObjectManager::addObject

void __thiscall ObjectManager::addObject(int* thisManager, int* object)
{
    // Increment two reference-like counters on the object
    object[0] = object[0] + 1;   // +0x00: refCountA
    object[1] = object[1] + 1;   // +0x04: refCountB

    // Allocate a zeroed buffer sized by object's field at offset 0x108
    size_t bufferSize = object[0x42] + 1;  // +0x108: bufferSize (elements or bytes)
    int zeroVal = 0;
    void* buffer = allocateMemory(bufferSize);  // FUN_009c8e80 – custom allocator
    memset(buffer, zeroVal, bufferSize);

    // Add object to internal list (max 64 entries)
    unsigned int currentCount = thisManager[0x81];  // +0x204: objectCount
    if (currentCount < 0x40) {  // 0x40 = 64
        // The list is an array of 2-int structures: { field, pointer }
        // Index into the list: each entry occupies 2 ints
        thisManager[currentCount * 2 + 1] = 0;            // field0 = 0
        thisManager[currentCount * 2 + 2] = (int)object;  // field1 = pointer to object
        thisManager[0x81] = currentCount + 1;             // update count
    }

    // Call virtual method at vtable offset 0x24 on the object
    void (*virtualMethod)(int*) = (void (*)(int*))(*(int**)object)[0x24 / 4];
    virtualMethod(object);
}