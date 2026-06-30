// FUNC_NAME: ThreadLocalAllocator::finalize
void ThreadLocalAllocator::finalize() {
    // Call internal initialization cleanup (FUN_00561950)
    FUN_00561950();

    int blockCount = *(int*)(this + 0x14c); // +0x14c: number of allocated blocks
    if (blockCount >= 0) {
        // Retrieve thread-local storage slot
        TlsGetValue((DWORD)DAT_01139810);
        // Clear block metadata at +0x144: size blockCount*4, fill with 0x17 (23)
        FUN_00aa26e0(*(void**)(this + 0x144), blockCount * 4, 0x17);
    }

    // Release two resource handles
    FUN_00aad100();
    FUN_00aad100();

    // Deallocate 6 fixed-size blocks (e.g., pool pages)
    int i = 5;
    do {
        thunk_FUN_00aa6490();
        i--;
    } while (i >= 0);
}