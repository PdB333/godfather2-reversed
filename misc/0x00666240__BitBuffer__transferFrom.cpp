// FUNC_NAME: BitBuffer::transferFrom
// Address: 0x00666240
// Role: Copies bit array data from source to destination with bit rotation and trailing zero trimming

int BitBuffer::transferFrom(BitBuffer *src) {
    // Fields of BitBuffer (offsets from this):
    // +0x00: int count;          // number of elements currently
    // +0x04: int capacity;       // max elements
    // +0x08: int flags;          // e.g., 0 = empty, non-zero = has data
    // +0x0C: int* data;          // pointer to array of 32-bit words

    // Check if operation is allowed:
    // Proceed if src->count <= this->capacity OR if some internal check (e.g., realloc possible) succeeds
    if (src->count <= this->capacity || isReallocPossible()) { // isReallocPossible is FUN_00667740
        int newCount = src->count;
        int oldCount = this->count;
        this->count = newCount;

        // Pointers to the end of each array (last element)
        uint *srcPtr = (uint *)(src->data + (newCount - 1));
        uint *dstPtr = (uint *)(this->data + (newCount - 1));
        uint carry = 0;

        // Process each word from last to first, rotating each right by 1 bit
        for (int i = newCount; i > 0; i--) {
            uint temp = carry << 0x1b;      // previous LSB becomes MSB
            carry = *srcPtr & 1;             // save LSB of source for next iteration
            *dstPtr = (*srcPtr >> 1) | temp; // rotate right by 1
            srcPtr--;
            dstPtr--;
        }

        // If new count is smaller than old count, zero out the extra elements at the end
        if (newCount < oldCount) {
            int *zeroPtr = this->data + newCount;
            int numToZero = oldCount - newCount;
            for (; numToZero > 0; numToZero--) {
                *zeroPtr = 0;
                zeroPtr++;
            }
        }

        // Copy flags from source
        this->flags = src->flags;

        // Trim trailing zeros from the array
        if (this->count > 0) {
            while (this->count > 0 && this->data[this->count - 1] == 0) {
                this->count--;
            }
            if (this->count == 0) {
                this->flags = 0; // fully empty
            }
        }

        return 0; // success
    }

    // If condition failed, return non-zero (failure) - but iVar1 might be garbage, assume failure
    return -1;
}