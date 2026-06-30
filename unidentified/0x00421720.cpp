// FUN_NAME: UInt32Array::initialize
// Address: 0x00421720
// Role: This function initializes a dynamic array object with a fixed count of 67 elements (0x43). 
// The object holds a pointer to a block of 268 bytes allocated via the engine's allocator, then zeroed.
// Struct layout (offsets from this):
//   +0x00: uint32_t* mData      (pointer to allocated buffer)
//   +0x04: uint32_t mCount       (number of elements, = 67)
//   +0x08: uint32_t mFlags       (set to 0)
//   +0x0C: uint8_t  mByteFlag    (set to 0)
void UInt32Array::initialize()
{
    // Set count to 67 (0x43) – this determines the size of the dynamically allocated buffer.
    this->mCount = 0x43;
    // Initialize pointer to null – will be overwritten below.
    this->mData = 0;
    // Clear flags.
    this->mFlags = 0;
    // Clear the byte flag at offset 0x0C.
    this->mByteFlag = 0;
    // Allocate buffer: 0x10C bytes = 0x43 * 4 = 67 * sizeof(uint32_t).
    this->mData = (uint32_t*)FUN_009c8e80(0x10c);
    // Zero-fill the allocated buffer.
    memset(this->mData, 0, this->mCount * 4);
}