// FUNC_NAME: SecureBufferManager::allocateBuffer
// Address: 0x0066b960
// Role: Allocates a fixed-size buffer (64 ints), XORs it with a key from the object, and returns a packed handle.
// The handle is two 64-bit values: first is a magic constant (0x4000000000), second is the buffer pointer shifted left by 32.
// The number of XOR iterations is the minimum of the object's stored size and the requested size.

int SecureBufferManager::allocateBuffer(int* pRequestSize, uint64_t* pOutHandle)
{
    uint* pDest;
    uint64_t uVar2;
    int numElements;
    int i;
    void* pBuffer;
    int oldSize;
    void* oldBuffer;

    // Determine number of elements to XOR: min of this->size and *pRequestSize
    if (this->size < *pRequestSize) {
        pBuffer = _calloc(4, 0x40); // Allocate 0x100 bytes (64 ints)
        if (pBuffer == (void*)0x0) {
            return -2;
        }
        int lockResult = acquireLock(); // FUN_00665ce0 - likely a mutex lock
        if (lockResult != 0) {
            return lockResult;
        }
        numElements = this->size;
    } else {
        pBuffer = _calloc(4, 0x40);
        if (pBuffer == (void*)0x0) {
            return -2;
        }
        int lockResult = acquireLock();
        if (lockResult != 0) {
            return lockResult;
        }
        numElements = *pRequestSize;
        // Note: this pointer is reassigned to pRequestSize? Actually in_EAX = param_1, but that's not used later.
        // The decompiler shows in_EAX = param_1, but the loop uses in_EAX[3] which is the key pointer from the original this.
        // This is likely a decompilation artifact; the key pointer should come from the original this.
        // We'll assume the key is always from this->keyArray.
    }

    // XOR the first numElements ints of the buffer with the key array
    i = 0;
    if (0 < numElements) {
        do {
            pDest = (uint*)((int)pBuffer + i * 4);
            *pDest = *pDest ^ *(uint*)(this->keyArray + i * 4); // this->keyArray is at offset +0x0C
            i = i + 1;
        } while (i < numElements);
    }

    // Pack the handle
    uVar2 = *pOutHandle; // Save old handle low part
    oldBuffer = (void*)((ulonglong)pOutHandle[1] >> 0x20); // Extract old buffer pointer from high 32 bits of second qword
    *pOutHandle = 0x4000000000; // Magic constant (type tag?)
    pOutHandle[1] = ZEXT48(pBuffer) << 0x20; // Store buffer pointer in high 32 bits

    // If there was an old buffer, free it
    if (oldBuffer != (void*)0x0) {
        oldSize = (int)uVar2; // Old size stored in low part of first qword? Actually uVar2 is the old first qword, but we treat it as size.
        _memset(oldBuffer, 0, oldSize * 4); // Clear old buffer before freeing
        _free(oldBuffer);
    }

    return 0;
}