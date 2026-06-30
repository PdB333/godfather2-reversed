// FUNC_NAME: ThreadLocalAllocator::freeByIndex
void __fastcall ThreadLocalAllocator::freeByIndex(void* thisObject) {
    int resourceIndex = *(int*)((char*)thisObject + 8); // +0x08: resource index
    if (resourceIndex >= 0) {
        TlsGetValue(gTlsKey);                    // retrieve thread-local storage
        FUN_00aa26e0(
            *(int*)thisObject,                   // +0x00: resource ID
            resourceIndex << 4,                  // convert index to byte offset
            0x17                                 // allocation tag (0x17)
        );
    }
}