// FUNC_NAME: BufferManager::allocateSubBuffer

// Function at 0x00841ef0: Allocates a sub-buffer of size 0xC0 bytes, constructs an internal object inside it,
// stores a handle at this+0x3C (likely a smart pointer/ref count), and returns a pointer to the object +0xC offset.

int __fastcall BufferManager::allocateSubBuffer(BufferManager* this) // param_1 = this
{
    uint32_t allocationHint;
    int bufferPtr;
    int internalObjectPtr;

    // Get a memory pool/arena (possibly a static heap)
    allocationHint = getMemoryPool(); // FUN_00840250

    // Allocate 0xC0 bytes from the pool with the hint
    bufferPtr = allocateRawMemory(0xC0, allocationHint); // FUN_008401e0
    if (bufferPtr == 0) {
        // Allocation failed
        internalObjectPtr = 0;
    } else {
        // Call constructor for internal object inside the allocated buffer
        internalObjectPtr = constructInternalObject(bufferPtr); // FUN_00841820
    }

    // Update the smart pointer/handle at this+0x3C with the new buffer reference
    // FUN_00848c30 likely takes the old handle and returns a new one (reference increment/decrement?)
    uint32_t newHandle = updateHandle(*(uint32_t*)(this + 0x3C)); // +0x3C: m_pSubBufferHandle
    *(uint32_t*)(this + 0x3C) = newHandle;

    if (internalObjectPtr != 0) {
        // Return pointer to the sub-object inside the buffer (skip header of 0xC bytes)
        return internalObjectPtr + 0xC;
    }
    return 0;
}