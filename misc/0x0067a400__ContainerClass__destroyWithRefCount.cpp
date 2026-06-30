// FUNC_NAME: ContainerClass::destroyWithRefCount
void __thiscall ContainerClass::destroyWithRefCount(void) {
    // This function appears to be a destructor for an object that manages
    // a list of sub-objects with reference counting. The object structure:
    // +0x00: pointer to an allocator/manager (called 'allocator' here)
    // +0x0C: a single sub-object pointer (called 'singleSubObject')
    // +0x1C: ushort count of array elements
    // +0x20: pointer to an array of 12-byte element headers (each containing a pointer to sub-object data)
    // +0xF8: another single sub-object pointer (called 'extraSubObject')
    // The object itself is allocated with a 4-byte header (allocatedSize?).

    if (this == nullptr) {
        return;
    }

    // Release the single sub-object at offset +0x0C
    int* singleObj = (int*)this->singleSubObject;  // +0x0C
    if (singleObj != 0) {
        // The allocator at +0x00 has a reference table at +0x0C that we clear
        int* allocator = (int*)this->allocator;  // +0x00
        *(int*)(*(int*)(allocator + 3) + *(int*)(singleObj + (-2)) * 4) = 0;  // Clear reference in table
        allocator[1]--;  // Decrement reference count
        deallocate((char*)singleObj - 0x10);  // Free the object (16-byte header before data)
    }

    // Release the array of sub-objects (array at +0x20, count at +0x1E)
    unsigned short count = *(unsigned short*)(this + 0x1E);  // +0x1E
    if (count != 0) {
        char* arrayBase = (char*)this->arrayPointer;  // +0x20
        int byteOffset = count * 12;  // Each element is 12 bytes
        do {
            // Read the pointer to the sub-object data from the 4-byte header before each element
            int* objPtr = *(int**)(arrayBase - 4 + byteOffset);
            if (objPtr != 0) {
                int* allocator = (int*)this->allocator;  // +0x00
                *(int*)(*(int*)(allocator + 3) + *(int*)(objPtr + (-2)) * 4) = 0;  // Clear reference
                allocator[1]--;  // Decrement reference count
                deallocate((char*)objPtr - 0x10);  // Free the sub-object
            }
            count--;
            byteOffset -= 12;
        } while (count > 0);
    }

    // Release the array pointer itself (if array was allocated separately)
    if (*(unsigned short*)(this + 0x1E) != 0) {
        int* arrayPtr = (int*)this->arrayPointer;  // +0x20
        if (arrayPtr != 0) {
            int* allocator = (int*)this->allocator;  // +0x00
            *(int*)(*(int*)(allocator + 3) + *(int*)(arrayPtr + (-2)) * 4) = 0;  // Clear reference
            allocator[1]--;  // Decrement reference count
            deallocate((char*)arrayPtr - 0x10);  // Free the array memory
        }
    }

    // Release the extra sub-object at offset +0xF8
    int* extraObj = (int*)this->extraSubObject;  // +0xF8
    if (extraObj != 0) {
        int* allocator = (int*)this->allocator;  // +0x00
        *(int*)(*(int*)(allocator + 3) + *(int*)(extraObj + (-2)) * 4) = 0;  // Clear reference
        allocator[1]--;  // Decrement reference count
        deallocate((char*)extraObj - 0x10);
    }

    // Finally free the container object itself
    int* allocator = (int*)this->allocator;  // +0x00
    *(int*)(*(int*)(allocator + 3) + *(int*)(((int)this) - 2) * 4) = 0;  // Clear reference for this object
    allocator[1]--;  // Decrement reference count
    deallocate((char*)this - 4);  // Free this object (4-byte header before data)

    return;
}