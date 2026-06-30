// FUNC_NAME: ArrayHolder::~ArrayHolder
void __fastcall ArrayHolder::~ArrayHolder(int* thisPtr) {
    // Set vtable to current class vtable (offset +0x00)
    *(int*)thisPtr = (int)&PTR_LAB_00e397fc;

    int arrayCount = *(int*)(thisPtr + 0x18); // +0x18: number of elements in array
    if (arrayCount >= 0) {
        // Get thread-local allocator (return value unused directly)
        TlsGetValue(DAT_01139810);

        // Deallocate array at +0x10; each element is 0x30 bytes
        // The count mask 0x3fffffff strips high flags (2 bits)
        int totalSize = (arrayCount & 0x3fffffff) * 0x30;
        FUN_00aa26e0(
            *(int*)(thisPtr + 0x10),   // +0x10: pointer to allocated array
            totalSize,
            0x17                        // allocation class (0x17 = 23)
        );
    }

    // Switch vtable to base class for continued destruction
    *(int*)thisPtr = (int)&PTR_LAB_00dc4710;
    return;
}