// FUNC_NAME: PtrArray::clear (or similar container cleanup)

void __fastcall PtrArray::clear(int* thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of elements in array
    int* items = (int*)*thisPtr; // +0x00: pointer to array of pointers

    // Loop backwards over all entries
    while (count-- > 0)
    {
        int* entry = (int*)(items[count]); // each element is a pointer to an object
        if (entry != nullptr)
        {
            // Clear reference field at offset +8 in the object (e.g., ref count, handle, or next pointer)
            *(int*)(entry + 2) = 0; // offset 8 in bytes: entry[2]
            // Clear the array slot
            items[count] = 0;
        }
    }

    thisPtr[1] = 0; // reset count
    // free the dynamically allocated array of pointers
    MemoryManager::deallocate((void*)items);
    *thisPtr = 0; // null out the array pointer
    thisPtr[2] = 0; // +0x08: reset capacity or some other member
}