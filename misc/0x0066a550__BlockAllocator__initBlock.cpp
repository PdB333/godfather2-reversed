// FUNC_NAME: BlockAllocator::initBlock

// Structure for a simple block allocator/range manager
// Offsets:
// +0x00 : hasValue (boolean flag)
// +0x04 : numDwords (number of DWORDs in buffer)
// +0x08 : counter (some internal counter)
// +0x0C : buffer (pointer to DWORD array)
struct BlockAllocator {
    uint32_t hasValue;      // +0x00
    uint32_t numDwords;     // +0x04
    uint32_t counter;       // +0x08
    uint32_t* buffer;       // +0x0C
};

// Initializes the block allocator with a given value
// value is passed in EAX, this pointer in ESI
void __thiscall BlockAllocator::initBlock(uint32_t value) {
    this->counter = 0;
    this->hasValue = 0;
    // Clear the entire buffer (size = numDwords * 4 bytes)
    _memset(this->buffer, 0, this->numDwords * 4);
    // Store the masked value (lower 28 bits) at the start of the buffer
    *this->buffer = value & 0x0FFFFFFF;
    // Set hasValue flag if the stored value is non-zero
    this->hasValue = (*this->buffer != 0) ? 1 : 0;
}