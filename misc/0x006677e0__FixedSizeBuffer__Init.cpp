// FUNC_NAME: FixedSizeBuffer::Init
// Function address: 0x006677e0
// Role: Initialize a fixed-size buffer (capacity 64) with dynamic allocation.
// Structure layout (offsets from 'this'):
//   +0x00: count (uint32)
//   +0x04: capacity (uint32, initially 0x40)
//   +0x08: flags/index (uint32, zeroed)
//   +0x0C: buffer pointer (uint32*)

int FixedSizeBuffer::Init() {
    uint32* buf = (uint32*)calloc(4, 0x40);  // allocate 64 ints
    this->buffer = buf;
    if (buf != nullptr) {
        this->count = 0;
        this->capacity = 0x40;
        this->field_08 = 0;
        return FUN_00665ce0();  // secondary initialization, returns 0 on success
    }
    return -2;  // allocation failure
}