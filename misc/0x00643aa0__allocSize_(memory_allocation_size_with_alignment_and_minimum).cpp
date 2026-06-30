// FUNC_NAME: allocSize (memory allocation size with alignment and minimum)
// Function address: 0x00643aa0
// Role: Computes a padded size for memory allocation.
// For input sizes <= 5, returns minimum 16.
// For larger sizes, adds 11 bytes of overhead and rounds down to multiple of 8.

unsigned int allocSize(unsigned int inputSize)
{
    if (0x10 < inputSize + 0xb) {
        return (inputSize + 0xb) & 0xfffffff8; // align to 8 (clear lower 3 bits)
    }
    return 0x10;
}