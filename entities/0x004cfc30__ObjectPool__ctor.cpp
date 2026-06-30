// FUNC_NAME: ObjectPool::ctor
undefined4 * __thiscall ObjectPool::ctor(undefined4 *this, int count, int numChunks)
{
    // count is passed in EAX register; for clarity we treat as parameter
    uint uVar1;
    void *buffer;
    
    this[1] = (undefined4)count;       // +0x04: store count (number of elements)
    *this = 0;                          // +0x00: clear buffer pointer initially
    this[2] = 0;                        // +0x08
    this[3] = 0;                        // +0x0C
    this[4] = 0;                        // +0x10
    *(undefined1 *)(this + 5) = 0;      // +0x14: zero flag byte (part of field at +0x14)
    
    // Allocate buffer: count * 4 bytes (size of each element assumed 4)
    buffer = (void *)FUN_009c8e50(count * 4);  // essentially operator new or malloc
    *this = (undefined4 *)buffer;       // store allocated buffer
    
    // Zero the entire buffer
    _memset(buffer, 0, count * 4);
    
    // Initialize in chunks: total chunks = (numChunks + 1023) / 1024
    for (uVar1 = (numChunks + 0x3ffU) >> 10; uVar1 != 0; uVar1--) {
        FUN_004cfd30(); // likely initializes per-element or per-chunk metadata
    }
    
    return this;
}