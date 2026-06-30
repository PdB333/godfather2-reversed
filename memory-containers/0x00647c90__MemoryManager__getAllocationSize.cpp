// FUNC_NAME: MemoryManager::getAllocationSize
// Address: 0x00647c90
// Retrieves the size of a memory allocation, thread-safe via embedded critical section.
// Reads a 4-byte header at ptr-4: bit0 and bit1 are flags, remaining 29 bits are allocation size.
// Returns size or 0 if the pointer is invalid or the allocation is not in use.

int __fastcall MemoryManager::getAllocationSize(void* ptr)
{
    // this +0x4e8: pointer to a CRITICAL_SECTION protecting the heap
    CRITICAL_SECTION* critSect = *(CRITICAL_SECTION**)((char*)this + 0x4e8);
    if (critSect) {
        EnterCriticalSection(critSect);
    }

    int result = 0;
    if (ptr != nullptr) {
        // Read the allocation header (size + flags) stored at ptr - 4
        uint header = *(uint*)((char*)ptr - 4);
        uint sizeWithFlags = header & 0x7ffffff8; // clear low 3 bits to get the raw size

        if ((header & 2) == 0) {
            // Bit1 not set: check byte at ptr + (sizeWithFlags - 4) for a validity flag (bit0)
            if ((*((char*)ptr + sizeWithFlags - 4) & 1) == 0) {
                // Allocation not in use; return 0
                goto leave;
            }
            // Valid single-header allocation: subtract 4-byte overhead
            result = sizeWithFlags - 4;
        } else {
            // Bit1 set: larger overhead (8 bytes) – possibly double-tagged allocation
            result = sizeWithFlags - 8;
        }
    }

leave:
    if (critSect) {
        LeaveCriticalSection(critSect);
    }
    return result;
}