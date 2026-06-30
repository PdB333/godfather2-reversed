// FUNC_NAME: UInt32Array::UInt32Array
// Address: 0x0043fe80
// Role: Constructor for a dynamic array of unsigned 32-bit integers.
//        Allocates and zero-initializes a buffer of size count*4 bytes.
//        Stores a global singleton pointer to the instance.
// Assumed class layout:
//   +0x00: vtable pointer (to VTABLE_UInt32Array)
//   +0x04: m_pData (uint32*)
//   +0x08: m_count (uint32)
//   +0x0C: m_current (uint32, initially 0)

UInt32Array* __thiscall UInt32Array::UInt32Array(UInt32Array* this, unsigned int count)
{
    void* newBuffer;

    // Global singleton reference
    g_pSingleton = this;

    // Store the count
    this->m_count = count;

    // Set vtable
    this->vtable = &VTABLE_UInt32Array;

    // Initialize the current index to 0
    this->m_current = 0;

    // Allocate memory for the array: count * 4 bytes
    newBuffer = MemoryAllocator::allocate(count * 4);
    this->m_pData = (uint32*)newBuffer;

    // Zero-initialize the buffer
    memset(this->m_pData, 0, this->m_count * 4);

    return this;
}