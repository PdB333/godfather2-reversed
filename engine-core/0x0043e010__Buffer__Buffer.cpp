// FUNC_NAME: Buffer::Buffer
// Address: 0x0043e010
// Role: Constructor for a fixed-capacity buffer class (16 elements max). 
// Clears old data if capacity exceeded, then sets new capacity and zeroes count.
// param_2 bit0 controls whether to deallocate this object after initialization.

class Buffer {
public:
    // +0x00: vtable pointer (changed during construction)
    // +0x0C: m_pData - pointer to allocated data (low byte used as flags)
    // +0x1C: m_nCount - current number of elements
    // +0x20: m_nCapacity - max number of elements (default 15)

    Buffer(byte allocFlag) {
        // Set initial vtable (base class)
        this->vtable = &g_vtableInitial;

        if (this->m_nCapacity > 15) {
            // Capacity exceeds maximum, free old data
            operator delete(this->m_pData);
        }

        // Set to fixed capacity of 16 (0xF = 15 max index)
        this->m_nCapacity = 15;
        this->m_nCount = 0;

        // Clear low byte of m_pData (resets internal flags/tag)
        *(uint8_t*)&this->m_pData = 0;

        // Switch to final vtable (derived class or actual class)
        this->vtable = &g_vtableFinal;

        if (allocFlag & 1) {
            // If flag bit0 set, deallocate this object
            operator delete(this);
        }
    }
};