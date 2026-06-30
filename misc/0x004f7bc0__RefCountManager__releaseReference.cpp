// FUNC_NAME: RefCountManager::releaseReference
// Address: 0x004f7bc0
// Role: Decrements a reference count for a given handle/index.
//       If the count reaches zero, calls the actual delete/free routine (FUN_00519340).
//       Uses thread-local storage to access per-thread reference count table.

void RefCountManager::releaseReference(int handleIndex, int param2)
{
    // Check if handle is valid
    if (handleIndex == 0) {
        return;
    }

    // Get per-thread data pointer from TLS (FS segment offset 0x2c)
    int* tlsData = *(int**)(__readfsdword(0x2c));
    // The actual reference count table is at offset 0x30 from the base at tlsData[2] (i.e., tlsData[1]? Wait: iVar2 = *tlsData? Let's analyze.)
    // In the decompiled: iVar2 = **(int **)(unaff_FS_OFFSET + 0x2c);
    // That means: dereference the pointer at FS:0x2c twice to get iVar2.
    // Then piVar1 = (int *)(*(int *)(iVar2 + 8) + 0x30 + handleIndex);
    // So the structure is: TLS points to a struct that contains a pointer at offset 0 (first deref).
    // That pointer points to another struct whose +8 is a pointer to an array at +0x30.
    // For clarity, let's use intermediate variables.

    int* basePtr = *(int**)(__readfsdword(0x2c)); // first deref -> points to a struct
    int* refCountBase = *(int**)((char*)basePtr + 8); // offset 8 -> pointer to array
    int* refCount = refCountBase + 0x30 + handleIndex; // array starts at +0x30, indexed by handleIndex

    // Decrement reference count
    *refCount = *refCount - 1;

    // If reference count becomes zero, call the cleanup function
    if (*refCount == 0) {
        FUN_00519340(handleIndex, param2);
    }
}