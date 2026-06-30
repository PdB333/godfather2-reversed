// FUNC_NAME: SequenceItemManager::release
void SequenceItemManager::release() {
    // +0x124: some byte flag (set to 0)
    *reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(this) + 0x490) = 0;
    // +0x123: some integer field (set to 0)
    this->field_0x48C = 0;

    // Release shared resources (called twice deliberately)
    this->releaseSharedResource();
    this->releaseSharedResource();

    // If we own a child object at +0x125, release it via its stored vtable-like pointer at +0x128
    if (this->childObject != nullptr) {
        // The function pointer is stored at +0x128 (4 bytes after the pointer)
        reinterpret_cast<void (*)(void*)>(this->childVtableFunc)(this->childObject);
    }
    this->childObject = nullptr;
    this->field_0x49C = 0; // +0x127
    this->field_0x498 = 0; // +0x126

    // Release another manager/group
    this->releaseSecondaryManager();

    // Iterate over 4 SequenceItem objects in the array starting at offset 0x1C (28 bytes)
    // Each element is 0x6C bytes (27 DWORDs)
    static const char* itemNames[] = { "SequenceItem1", "SequenceItem2", "SequenceItem3", "SequenceItem4" };
    int* arrayBase = reinterpret_cast<int*>(reinterpret_cast<uint8_t*>(this) + 0x1C);
    for (int i = 0; i < 4; ++i) {
        int* item = arrayBase + (i * 0x6C); // step by 27 DWORDs

        // Release first group of pointers (offsets -24, -20, -16, -12)
        if (item[-6] != 0) {
            reinterpret_cast<void (*)(void*)>(item[-3])((void*)item[-6]); // item[-3] is function ptr, item[-6] is object ptr
        }
        item[-6] = 0; // clear object ptr
        item[-4] = 0;
        item[-5] = 0;
        FUN_004d3d90(*itemNames[i]); // likely a string release / deallocate

        // Release second group (offsets -8, +4, 0, -1)
        if (item[-2] != 0) {
            reinterpret_cast<void (*)(void*)>(item[1])((void*)item[-2]);
        }
        item[-2] = 0;
        item[0] = 0;
        item[-1] = 0;

        // Release third group (offsets +8, +20, +16, +12)
        if (item[2] != 0) {
            reinterpret_cast<void (*)(void*)>(item[5])((void*)item[2]);
        }
        item[2] = 0;
        item[4] = 0;
        item[3] = 0;

        // Release fourth group (offsets +24, +36, +32, +28)
        if (item[6] != 0) {
            reinterpret_cast<void (*)(void*)>(item[9])((void*)item[6]);
        }
        item[6] = 0;
        item[8] = 0;
        item[7] = 0;

        // Initialize state for reused item
        item[0x0F] = 0; // offset 0x3C (60)
        item[0x10] = DAT_00e2b04c; // global default
        item[0x0E] = 0; // offset 0x38
        item[0x11] = DAT_00e2b050; // global default
        *reinterpret_cast<uint8_t*>(item + 0x14) = 1; // byte at offset 0x50 set to 1
        item[0x12] = 0;
        item[0x13] = 0;
    }

    // Zero out the vtable pointer (first DWORD) to mark object as invalid
    *reinterpret_cast<int**>(this) = nullptr;
}