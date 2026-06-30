// FUNC_NAME: ListNode::initialize (or possibly Node::init)
// Address: 0x005ac070
// Role: Initializes a linked list node structure (likely a sentinel or standalone node) in the EARS engine.
// This appears to be a __thiscall member function where 'this' is passed in EAX.

void __thiscall Node::initialize(void) {
    uint* const ptr = reinterpret_cast<uint*>(this);
    uint* selfPtr = ptr; // in_EAX

    // Clear and set specific bits in the first 32-bit field (flags at offset 0)
    // Bits 2 and 4 are set (0x14), bit 15 is set later (0x8000).
    // Mask 0xffff8014 preserves bits 2, 4, 15 and clears others.
    *selfPtr = (*selfPtr & 0xffff8014) | 0x14;

    // Set the second 16-bit word (offset 2) to 0 (part of the first dword)
    *reinterpret_cast<uint16*>(reinterpret_cast<uint8*>(selfPtr) + 2) = 0;

    // Set bit 15 (0x8000) in the first dword
    *selfPtr |= 0x8000;

    // Set the 16-bit value at offset 6 to 0
    *reinterpret_cast<uint16*>(reinterpret_cast<uint8*>(selfPtr) + 6) = 0;

    // Compute pointer to offset 12 (self + 0x0C)
    uint* const innerPtr = selfPtr + 3; // offset 12

    // Set a short at offset 4 to 2 (likely a type or size field)
    *reinterpret_cast<uint16*>(selfPtr + 1) = 2;  // +0x04

    // Set the pointer at offset 8 to point to offset 12 (self-reference)
    selfPtr[2] = reinterpret_cast<uint>(innerPtr); // +0x08

    // Zero out 8 bytes at offset 12-19 (potential child node or data area)
    innerPtr[0] = 0; // +0x0C
    innerPtr[1] = 0; // +0x10

    // Zero out fields at offset 20 and 24 (likely additional data)
    selfPtr[5] = 0; // +0x14
    selfPtr[6] = 0; // +0x18
}