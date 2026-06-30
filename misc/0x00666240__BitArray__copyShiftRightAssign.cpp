// FUNC_NAME: BitArray::copyShiftRightAssign
// Address: 0x00666240
// Role: Copies a source BitArray into this, applying a 1-bit right shift across all bits (with carry between words). Allows resizing if capacity insufficient.

struct BitArray {
    uint32_t  size;        // +0x00 number of 32-bit words used
    uint32_t  capacity;    // +0x04 maximum number of words allocated
    uint32_t  flags;       // +0x08 e.g., sign or status flags
    uint32_t* data;        // +0x0C pointer to word array
};

// __thiscall in EAX
int BitArray::copyShiftRightAssign(BitArray* src) {
    int iVar1;

    // If source size fits in our capacity, or we can successfully resize, proceed
    if (src->size <= this->capacity || (iVar1 = resizeCapacity(), iVar1 == 0)) {
        int newSize = src->size;               // copy source size
        int oldSize = this->size;              // save old size for zeroing later
        this->size = newSize;

        // Pointers to last words of source and destination (since we iterate backwards)
        uint32_t* srcPtr = (uint32_t*)(src->data + newSize - 1);
        uint32_t* dstPtr = (uint32_t*)(this->data + newSize - 1);

        uint32_t carry = 0;
        // Process all words from high to low, shifting right by 1 and propagating carry
        while (newSize-- > 0) {
            uint32_t newCarry = *srcPtr & 1;           // LSB of current source word
            *dstPtr = (*srcPtr >> 1) | (carry << 27); // shift right and insert previous carry into bit 27
            carry = newCarry;
            dstPtr--;
            srcPtr--;
        }

        // Zero out any additional words if new size is smaller than old size
        if (newSize < oldSize) {
            uint32_t* clearPtr = (uint32_t*)(this->data + newSize);
            int wordsToClear = oldSize - newSize;
            while (wordsToClear-- > 0) {
                *clearPtr++ = 0;
            }
        }

        // Copy the flags field
        this->flags = src->flags;

        // Trim trailing zeros: decrease size while the last word is zero
        int currentSize = this->size;
        if (currentSize > 0) {
            do {
                if (this->data[currentSize - 1] != 0) break;
                currentSize--;
                this->size = currentSize;
            } while (currentSize > 0);
        }

        // If size became zero, clear flags
        if (this->size == 0) {
            this->flags = 0;
        }

        iVar1 = 0; // success
    }
    // iVar1 is non-zero only if resize failed (value from resizeCapacity)
    return iVar1;
}