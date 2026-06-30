// FUN_004c7580: RenderVisibilityManager::collectVisibleAndSort
void __thiscall RenderVisibilityManager::collectVisibleAndSort(void* thisPtr) {
    uint32 count = *(uint32*)((uintptr_t)thisPtr + 0x34); // +0x34: number of object slots
    if (count == 0) {
        return;
    }

    // Temporary global sort buffer (8-byte entries: pointer + sort key)
    static void* sortBuffer[256][2]; // DAT_01163ee0 (buffer start)
    static int32 sortBufferCount;    // DAT_01163edc

    sortBufferCount = 0;

    // Pointer to array of 0xB0-byte elements
    uint8* elementBase = *(uint8**)((uintptr_t)thisPtr + 0x50); // +0x50: pointer to object array

    for (uint32 i = 0; i < count; i++) {
        uint8* element = elementBase + i * 0xB0; // each element is 0xB0 bytes
        // Check flag at offset +8: bit 0x20 (visible/active)
        if (*(uint8*)(element + 8) & 0x20) {
            // Store pointer (first 4 bytes) and sort key (second 4 bytes)
            // Sort key assumed to be at offset +4 (e.g., depth, priority)
            sortBuffer[sortBufferCount][0] = (void*)element;
            sortBuffer[sortBufferCount][1] = *(void**)(element + 4); // key field
            sortBufferCount++;
        }
    }

    // Sort the collected entries using the comparator at 0x004c7560
    qsort(sortBuffer, sortBufferCount, 8, (__cdecl*)(const void*, const void*))0x004c7560);
}