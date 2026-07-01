// FUNC_NAME: ObjectContainer::findObjectIndex
uint __thiscall ObjectContainer::findObjectIndex(int thisPtr, int objectPtr) {
    int tmp;
    uint index;
    int* entryPtr;

    // If the container has no elements, return -1
    if (*(uint*)(thisPtr + 0x6c) == 0) {
        return 0xffffffff;
    }

    // Pointer to the array of entries (each entry is two ints)
    entryPtr = *(int**)(thisPtr + 0x68);
    index = 0;

    while (true) {
        // Derive the object base from the stored pointer
        // The stored pointer points to a member at offset 0x48 inside the object
        if (*entryPtr == 0) {
            tmp = 0;
        } else {
            tmp = *entryPtr - 0x48; // Subtract offset to get object base
        }

        // Check if this matches the target object pointer
        if (tmp == objectPtr) {
            break;
        }

        index++;
        entryPtr += 2; // Each entry is 8 bytes (two ints)

        // If we've reached the end, return not found
        if (*(uint*)(thisPtr + 0x6c) <= index) {
            return 0xffffffff;
        }
    }

    return index;
}