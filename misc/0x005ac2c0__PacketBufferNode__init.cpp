// FUNC_NAME: PacketBufferNode::init
// Address: 0x005ac2c0
// Role: Initializes a fixed-size packet buffer node, likely part of a free list allocator.
// Offsets: +0x00: flags (uint32), +0x02: unused? (uint16), +0x04: packet size/type? (uint16, set to 4),
//          +0x06: unused? (uint16), +0x08: pointer to next free node (uint32), +0x0C: data payload (64 bytes)
void __thiscall PacketBufferNode::init(void *this) {
    uint32_t *flags = (uint32_t *)this;
    // Clear bits 5-14, preserve bits 0-4, then force bits 1-4 (0x1E = 11110 binary)
    *flags = (*flags & 0xffff801e) | 0x1e;
    // Zero out field at offset 2
    *(uint16_t *)((char *)this + 2) = 0;
    // Set bit 15 (probably marks node as allocated or valid)
    *flags |= 0x8000;
    // Set field at offset 4 to 4 (likely header size or buffer type)
    *(uint16_t *)((char *)this + 4) = 4;
    // Zero out field at offset 6
    *(uint16_t *)((char *)this + 6) = 0;
    // Make the 'next' pointer at offset 8 point to the data area (offset 12)
    *(uint32_t *)((char *)this + 8) = (uint32_t)((char *)this + 12);
    // Clear the 64-byte data payload
    memset((char *)this + 12, 0, 0x40);
}