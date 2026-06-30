// FUNC_NAME: DynamicBuffer::initialize
int DynamicBuffer::initialize(void)
{
    // Allocate buffer for capacity elements (capacity = 0x40 = 64 elements, each 4 bytes)
    // calloc(4, 0x40) allocates 4 * 64 = 256 bytes; interpreted as 64 elements of 4 bytes.
    this->data = (unsigned char*)_calloc(4, 0x40);
    if (this->data == 0) {
        return 0xfffffffe; // Allocation failure
    }
    this->currentSize = 0;    // +0x00: number of elements used
    this->capacity = 0x40;    // +0x04: maximum element count (64)
    this->flags = 0;          // +0x08: reserved/unused
    return 0;
}