// FUNC_NAME: SlotPool::initializePool
void SlotPool::initializePool(void)
{
    // this is a pointer to the object (in_EAX)
    // Offset +0x04: size of buffer in 4-byte words (0x280 = 640 words = 2560 bytes)
    // Offset +0x00: pointer to allocated buffer
    // Offset +0x08: unknown field set to 0
    // Offset +0x0C: unknown field set to 0
    // Offset +0x10: unknown field set to 0
    // Offset +0x14: byte field set to 0

    this->m_wordCount = 0x280;               // +0x04
    this->m_buffer = nullptr;                // +0x00
    this->m_field_08 = 0;                    // +0x08
    this->m_field_0C = 0;                    // +0x0C
    this->m_field_10 = 0;                    // +0x10
    *(byte *)((int)this + 0x14) = 0;         // +0x14

    // Allocate 0xA00 (2560) bytes for the pool buffer
    void *buffer = (void *)heapAlloc(0xA00); // FUN_009c8e80
    this->m_buffer = buffer;                 // +0x00

    // Clear the buffer: 0x280 * 4 = 2560 bytes
    memset(buffer, 0, this->m_wordCount * 4);

    // Initialize each of the 64 slots (each slot is 0x28 = 40 bytes)
    for (int slotIndex = 0; slotIndex < 64; slotIndex++)
    {
        // Assume FUN_00573a00 is a constructor/initializer for a slot
        // It likely takes the slot address based on internal state, but here it's called with no args.
        // For reconstruction, we assume it uses the buffer pointer stored in this->m_buffer.
        constructSlot(); // FUN_00573a00
    }
    return;
}