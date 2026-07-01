// FUNC_NAME: DynArray::DynArray
// Function address: 0x0094f2c0
// Constructor for DynArray (dynamic array of elements of size 0x14)
// Object layout (4 dwords):
//   +0x00: data pointer (to array of elements)
//   +0x04: count (number of elements)
//   +0x08: capacity (initialized to 0)
//   +0x0C: unknown (initialized to 0)

__thiscall DynArray::DynArray(uint count) {
    uint *header;
    uint *data;

    // Multiply count by element size (0x14) with overflow detection
    uint64_t product = (uint64_t)count * 0x14;
    uint allocationSize = (uint)product;
    if (product >> 32 != 0) {
        allocationSize = 0xFFFFFFFF; // overflow -> signal error
    }

    // Compute final allocation size: 4 bytes for header + elements
    // If allocationSize > 0xFFFFFFFB, set to 0xFFFFFFFF (error)
    uint finalSize = 0xFFFFFFFF;
    if (allocationSize <= 0xFFFFFFFB) {
        finalSize = allocationSize + 4;
    }

    // Allocate memory (header + elements)
    header = (uint*)FUN_009c8e80(finalSize); // likely operator new or custom allocator
    if (header == nullptr) {
        data = nullptr;
    } else {
        // Store count in header
        *header = count;
        // Data pointer follows header
        data = header + 1;
        // Construct each element using the element constructor at 0x0094f250
        _vector_constructor_iterator_(data, 0x14, count, (void (*)(void*))0x0094f250);
    }

    // Initialize object fields
    this->data = data;   // +0x00
    this->count = count; // +0x04
    this->capacity = 0;  // +0x08
    this->field_C = 0;   // +0x0C

    return this;
}