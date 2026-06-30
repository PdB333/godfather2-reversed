// 0x004fff00 - DirtyPageTracker::markPageDirty
// Marks a memory page as dirty in the current thread's page table.
// param_1: pointer to a context structure with:
//   +0x10: int pageOffset - offset from page table base
//   +0x24: some object that must be initialized via sub_0043e500 (likely a mutex)
// Returns the address of the dirtied dword.

int __fastcall DirtyPageTracker::markPageDirty(void* context)
{
    // Get per-thread page table base from TLS (FS:0x2C).
    // The TLS structure at that offset contains a pointer; offset +8 holds the page table base.
    int* tlsPointer = *reinterpret_cast<int**>(__readfsdword(0x2C));
    int pageTableBase = tlsPointer[2]; // tlsPointer + 8 bytes -> tlsPointer[2] (assuming 4-byte int)

    // Read the page offset from the context object.
    int pageOffset = *reinterpret_cast<int*>(reinterpret_cast<char*>(context) + 0x10);

    // Initialize sub-object at offset 0x24 (e.g., a critical section or mutex).
    sub_0043e500(reinterpret_cast<char*>(context) + 0x24);

    // Compute address of the dirty flag word.
    int* dirtyWord = reinterpret_cast<int*>(pageTableBase + pageOffset);
    *dirtyWord |= 1;     // Mark page as dirty (set bit 0).

    // Return the dirty word address (used for further tracking).
    return reinterpret_cast<int>(dirtyWord);
}