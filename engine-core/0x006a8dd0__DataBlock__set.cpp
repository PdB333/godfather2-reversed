// FUNC_NAME: DataBlock::set
// Function address: 0x006a8dd0
// Role: Sets the internal buffer of a DataBlock object by allocating aligned memory and copying data.
// Thread-safe via global critical section (DAT_00d5d8e0).
// Class DataBlock has fields: buffer pointer at +0x40, size at +0x44.

void __thiscall DataBlock::set(void *src, size_t size)
{
    // Enter critical section (global lock)
    enterCriticalSection(&g_criticalSection); // FUN_00ab4db0

    // If an existing buffer is present, free it
    if (this->buffer != 0) { // *(int *)(param_1 + 0x40)
        alignedFree(this->buffer); // FUN_005e3c00
        this->buffer = 0; // *(undefined4 *)(param_1 + 0x40) = 0
        this->size = 0;   // *(undefined4 *)(param_1 + 0x44) = 0
    }

    // Allocate new aligned buffer (align 0x10, flags 0)
    void *newBuffer = alignedAlloc(size, 0x10, 0); // FUN_005e3bb0
    if (newBuffer != 0) {
        this->buffer = newBuffer;
        this->size = size;
        memcpy(newBuffer, src, size); // _memcpy
    }

    // Leave critical section
    leaveCriticalSection(&g_criticalSection); // FUN_00ab4e70
}