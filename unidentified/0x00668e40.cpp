// FUN_NAME: BitArray28::shiftLeftBits
// Function address: 0x00668e40
// Shifts the entire 28-bit packed array left by (bitIndex % 28) bits,
// removing the bits at the bottom and compacting the array.
// Returns 0 on success, or a non-zero error code from helper functions.

struct BitArray28 {
    int count;        // +0x00: number of 28-bit elements
    int capacity;     // +0x04: allocated capacity (in elements)
    int writePosition; // +0x08: cursor used after shift (set to 0 if count becomes 0)
    uint32* data;     // +0x0c: pointer to array of 32-bit words storing 28-bit values
};

// Forward declarations of helper functions (defined elsewhere)
int ensureCapacity(BitArray28* self);    // FUN_00665ce0
int growCapacity(BitArray28* self);     // FUN_00667740
int shiftWordAligned(BitArray28* self, int wordIndex); // FUN_006687e0

int __thiscall BitArray28::shiftLeftBits(BitArray28* this, int bitIndex) {
    int ret;
    
    // Guard: if this pointer has been invalidated, reinitialize
    if ((this != reinterpret_cast<BitArray28*>(EAX)) && (ret = ensureCapacity(this), ret != 0)) {
        return ret;
    }
    
    // Check if we need to allocate space for a new word due to the shift
    if ((this->capacity < (bitIndex / 28) + 1 + this->count) && 
        (ret = growCapacity(this), ret != 0)) {
        return ret;
    }
    
    // If the bit index spans beyond the first word, handle word alignment shift
    if ((27 < bitIndex) && (ret = shiftWordAligned(this, bitIndex / 28), ret != 0)) {
        return ret;
    }
    
    if (bitIndex % 28 == 0) {
        // Exact word boundary: just trim trailing zero elements
        goto trimTrailingZeros;
    } else {
        // Shift left by (bitIndex % 28) bits across all words
        int shiftAmount = static_cast<uint8_t>(bitIndex % 28);
        int i = 0;
        uint32 carry = 0;
        uint32* wordPtr = this->data;
        int origCount = this->count;
        
        if (0 < origCount) {
            do {
                // Extract the high shiftAmount bits from the current word
                uint32 highBits = *wordPtr >> (28 - shiftAmount) & ((1 << shiftAmount) - 1);
                // Shift the word left and merge the previous carry
                *wordPtr = (*wordPtr << shiftAmount) | carry;
                // Keep the high bits as carry for next word
                carry = highBits;
                wordPtr++;
                i++;
            } while (i < origCount);
            
            // If there is a leftover carry, append a new word
            if (highBits != 0) {
                *(uint32*)(this->data + this->count) = highBits;
                this->count++;
            }
        }
        
        // Remove any trailing zero elements
        trimTrailingZeros:
        int newCount = this->count;
        if (0 < newCount) {
            do {
                if (*(uint32*)(this->data + (newCount - 1)) != 0) break;
                newCount--;
                this->count = newCount;
            } while (0 < newCount);
        }
    }
    
    // If count became zero, reset write cursor
    if (this->count == 0) {
        this->writePosition = 0;
    }
    
    return 0;
}