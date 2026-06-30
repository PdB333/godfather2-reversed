// FUNC_NAME: DynamicArray::initialize

undefined4* __thiscall DynamicArray::initialize(undefined4* this, uint elementCount, byte flag) {
    void* buffer;

    // +0x14: flag (byte, likely ownsMemory or some bit)
    *(byte*)(this + 5) = flag;  // offset 20 = 0x14
    // +0x04: allocated element count (capacity)
    this[1] = elementCount;     // offset 4
    // +0x00: pointer to allocated buffer
    this[0] = 0;                // offset 0
    // +0x08, +0x0C, +0x10: counters/indices initialized to zero
    this[2] = 0;                // offset 8
    this[3] = 0;                // offset 12
    this[4] = 0;                // offset 16

    // Allocate buffer: elementCount * 4 bytes (each element is 4 bytes)
    buffer = (void*)FUN_009c8e80(-(uint)(int32)((uint64)elementCount * 4 >> 32) | ((uint64)elementCount * 4));
    this[0] = buffer;           // store pointer
    memset(buffer, 0, elementCount * 4);

    // Call parent/base class initialization
    FUN_006e73f0();

    return this;
}