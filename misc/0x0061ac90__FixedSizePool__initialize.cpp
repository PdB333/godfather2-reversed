// FUNC_NAME: FixedSizePool::initialize
void FixedSizePool::initialize() {
    // Zero the base header (0x800 bytes), likely base class data
    memset(this, 0, 0x800);

    // +0x800: Some flag (set to 0, already zeroed)
    *(int*)((char*)this + 0x800) = 0;

    // +0x808: Capacity of the pool (0x1000 = 4096 elements)
    *(int*)((char*)this + 0x808) = 0x1000;

    // +0x804: Callback function pointer (e.g., cleanup or deallocation)
    *(void**)((char*)this + 0x804) = (void*)0x0061b1a0;

    // +0x80c: Allocate buffer for 0x1000 * 4 bytes (each element 4 bytes)
    void* pool = memoryAlloc(0x4000);  // FUN_009c8e80 is custom allocator
    *(void**)((char*)this + 0x80c) = pool;

    // +0x810, +0x814, +0x818: Counters or indices (set to 0)
    *(int*)((char*)this + 0x810) = 0;
    *(int*)((char*)this + 0x814) = 0;
    *(int*)((char*)this + 0x818) = 0;

    // Zero the entire pool buffer
    memset(pool, 0, *(int*)((char*)this + 0x808) * 4);
}