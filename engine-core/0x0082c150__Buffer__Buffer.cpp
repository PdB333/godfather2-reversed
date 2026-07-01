// FUNC_NAME: Buffer::Buffer

// Constructor for a buffer class used in EA EARS engine
// Initializes vtable, allocates an internal 64-byte buffer, sets capacity to 16
__fastcall void Buffer::Buffer(Buffer* this)
{
    // vtable pointer at offset +0x00
    this->vtable = &Buffer_vtable;  // PTR_FUN_00d73788

    // +0x04: unknown flag/state, initialized to 0
    this->field_0x04 = 0;

    // +0x08: pointer to allocated buffer (size 0x40 = 64 bytes)
    this->m_pBuffer = (unsigned char*)FUN_009c8e80(0x40);  // operator new or heap alloc

    // +0x0C: unknown index/offset, initialized to 0
    this->field_0x0C = 0;

    // +0x10: capacity (likely number of items), set to 0x10 = 16
    this->m_nCapacity = 0x10;

    // Note: buffer size (64) / item size (4?) = capacity (16) suggests 4-byte elements
}