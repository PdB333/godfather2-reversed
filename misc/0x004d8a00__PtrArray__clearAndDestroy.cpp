// FUNC_NAME: PtrArray::clearAndDestroy

// Reconstructed from 0x004d8a00: Clears all entries in a pointer array with destructor callbacks.
// The array stores 0x10-byte entries: [object pointer (0x00), unknown (0x04-0x0B), destructor function pointer (0x0C)].
// Class layout: entries* (+0x00), count (+0x04), capacity (+0x08).

void __fastcall PtrArray::clearAndDestroy(int* thisPtr)
{
    int count = thisPtr[1]; // +0x04: number of entries
    int idx = count - 1;
    if (idx >= 0) {
        int offset = idx * 0x10; // each entry is 16 bytes
        do {
            void* obj = *(void**)(thisPtr[0] + offset); // +0x00: object pointer
            if (obj != nullptr) {
                // +0x0C: destructor function pointer
                void (*destructor)(void*) = *(void (**)(void*))(thisPtr[0] + offset + 0xC);
                destructor(obj);
            }
            idx--;
            offset -= 0x10;
        } while (idx >= 0);
    }
    thisPtr[1] = 0; // reset count
    deallocateArray((void*)thisPtr[0]); // free the entries array (FUN_009c8f10)
    thisPtr[0] = 0; // entries = nullptr
    thisPtr[2] = 0; // +0x08: capacity = 0
}