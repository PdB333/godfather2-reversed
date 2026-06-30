// FUNC_NAME: ManagerClass::destroy
void __fastcall ManagerClass::destroy(ManagerClass* thisPtr)
{
    // Set vtable pointers (base class inheritance)
    thisPtr->vtableBase = &__vtbl_0;    // +0x00: PTR_FUN_00d6244c
    thisPtr->vtableDerived = &__vtbl_1; // +0x0C: PTR_LAB_00d62448

    // Lock global mutex
    enterCriticalSection(&g_managerLock); // DAT_012069c4

    // Clean up three dynamic arrays (stored at decreasing offsets)
    // Array 2: pointer at +0x34, count at +0x38
    // Array 1: pointer at +0x28, count at +0x2C
    // Array 0: pointer at +0x1C, count at +0x20
    int* arrays[3] = { thisPtr->m_array0, thisPtr->m_array1, thisPtr->m_array2 };
    int  counts[3] = { thisPtr->m_count0, thisPtr->m_count1, thisPtr->m_count2 };

    for (int idx = 2; idx >= 0; --idx)
    {
        int* arr = arrays[idx];
        int   cnt = counts[idx];

        // Delete each 8-byte element in the array if its first field is non-zero
        for (int i = cnt - 1; i >= 0; --i)
        {
            int* elem = &arr[i * 2]; // each element is 8 bytes (two ints)
            if (elem[0] != 0)
            {
                FUN_004daf90(elem); // destroy the element object
            }
        }

        // Delete the array itself
        if (arr != nullptr)
        {
            FUN_009c8f10(arr); // operator delete[]
        }

        // Nullify pointers and counts (optional, but safe)
        arrays[idx] = nullptr;
        counts[idx] = 0;
    }

    // Reset vtable to base class (destructor cleanup)
    thisPtr->vtableDerived = &__vtbl_2; // +0x0C: PTR_LAB_00d62444

    // Reset global singleton active flag
    g_managerActive = 0; // DAT_01129964

    // Unlock global mutex
    leaveCriticalSection(&g_managerLock); // FUN_004083d0
}