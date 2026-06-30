// FUNC_NAME: MemoryManager::AllocateAligned

// Global pointer to the memory manager singleton (DAT_0112a9c0)
extern class MemoryManager* g_pMemoryManager;

/**
 * Function: 0x006eaba0
 * Role: Memory allocation with 256-byte alignment.
 * If a global memory manager exists, it delegates to the manager's Allocate method.
 * Otherwise, it forces the input size to a 256-byte boundary by masking off the low 8 bits.
 * Note: The decompiled output uses an implicit `in_EAX` register; here it is modeled
 * as the `size` parameter for clarity, assuming the caller passes the desired allocation
 * size in EAX (fastcall convention). The actual assembly may have stored the original
 * size in EAX and then passed `param_1` as an additional flag or context.
 */
uint AllocateAligned(uint size) {
    // If no global manager exists, align the size to 256 bytes (0xFFFFFF00 mask)
    uint alignedSize = size & 0xFFFFFF00;

    // Use the global memory manager if available
    if (g_pMemoryManager != nullptr) {
        alignedSize = g_pMemoryManager->Allocate(size);  // +0x00: MemoryManager::Allocate (func_006f6ed0)
    }

    return alignedSize;
}