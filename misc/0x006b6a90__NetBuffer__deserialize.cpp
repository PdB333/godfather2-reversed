// FUNC_NAME: NetBuffer::deserialize
int __thiscall NetBuffer::deserialize(void *this, int srcBuffer, void *srcStream) {
    int *refCountPtr;
    uint originalRefCount;
    uint currentRefCount;
    int i;
    int bytesRead1;
    int bytesRead2;
    int totalBytes;

    // +0x78: reference count (refCount)
    originalRefCount = *(uint *)((int)this + 0x78);
    currentRefCount = originalRefCount;

    // Decrement refcount; if it hits zero, release sub-objects
    while (currentRefCount != 0) {
        refCountPtr = (int *)((int)this + 0x78);
        *refCountPtr = *refCountPtr - 1;
        if (*refCountPtr == 0) {
            // +0xac: number of sub-objects to release
            int subObjectCount = *(int *)((int)this + 0xac);
            while (subObjectCount-- > 0) {
                FUN_006b56a0(subObjectCount); // release or delete sub-object
            }
        }
        currentRefCount = *(uint *)((int)this + 0x78);
    }

    // Clear pointers and free previous data
    *(int *)((int)this + 0x88) = 0;               // +0x88: some data1 pointer
    FUN_009c8f10(*(int *)((int)this + 0x84));      // free old buffer1
    *(int *)((int)this + 0x84) = 0;                // +0x84: buffer1 pointer
    *(int *)((int)this + 0x8c) = 0;                // +0x8c: data2 pointer?
    *(int *)((int)this + 0xa0) = 0;                // +0xa0: some pointer
    FUN_009c8f10(*(int *)((int)this + 0x9c));      // free old buffer2
    *(int *)((int)this + 0x9c) = 0;                // +0x9c: buffer2 pointer
    *(int *)((int)this + 0xa4) = 0;                // +0xa4: some other pointer

    // Read data from srcStream into this object
    // FUN_006b6990 likely returns number of bytes consumed from srcBuffer
    int bytesFromBuffer = FUN_006b6990(srcBuffer, &srcStream, srcStream); // note: pass by reference?
    // Position after reading from srcBuffer
    int posInBuffer = bytesFromBuffer + srcBuffer;

    // Read first section: size at srcStream+0x38, output to this+0x84
    bytesRead1 = FUN_006b47b0(posInBuffer, *(int *)((int)srcStream + 0x38), (int *)((int)this + 0x84));
    int posAfterRead1 = posInBuffer + bytesRead1;

    // Read second section: size at srcStream+0x3c, output to this+0x9c
    bytesRead2 = FUN_006b47b0(posAfterRead1, *(int *)((int)srcStream + 0x3c), (int *)((int)this + 0x9c));
    int posAfterRead2 = posAfterRead1 + bytesRead2;

    // Restore reference count to original and trigger processing if needed
    currentRefCount = *(uint *)((int)this + 0x78);
    while (currentRefCount < originalRefCount) {
        *(int *)((int)this + 0x78) = *(int *)((int)this + 0x78) + 1;
        if (*(int *)((int)this + 0x78) == 1) {
            // +0x68: total capacity? +0xac: used count?
            int remaining = *(int *)((int)this + 0x68) - *(int *)((int)this + 0xac);
            if (remaining > 0) {
                do {
                    FUN_006b4b50();  // process or fill next slot
                    remaining--;
                } while (remaining != 0);
            }
        }
        currentRefCount = *(uint *)((int)this + 0x78);
    }

    // Finalize: +0x16c some callback list or object
    FUN_006b4e30(*(int *)((int)this + 0x16c), 0);
    FUN_006b2f70(); // static update

    // Return total bytes read (excluding initial srcBuffer offset)
    return (posAfterRead2) - srcBuffer;
}