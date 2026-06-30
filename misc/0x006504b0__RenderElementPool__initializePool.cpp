// FUNC_NAME: RenderElementPool::initializePool
void RenderElementPool::initializePool(void)
{
    // Check if the pool array pointer is initialized
    if (m_pSlotArray != 0) {
        // Increment the number of pools (or slots) being initialized
        m_nSlotCount = m_nSlotCount + 1;

        int currentSlot = 0;                 // Index into m_pSlotArray (0, 4, 8, 12 per block)
        int dataOffset = 0;                  // Byte offset within m_pDataBuffer (0, 0xC0, ...)
        int baseElementId = 2;               // Starting ID for the first block (becomes 0,1,2,3 after subtraction)

        do {
            // Each block of 4 elements is spaced 0x30 bytes apart within m_pDataBuffer
            // Write the addresses of these 4 elements into the slot array
            *(int**)(currentSlot + m_pSlotArray) = (int*)(m_pDataBuffer + dataOffset);            // First element
            *(*(int**)(currentSlot + m_pSlotArray) + 0x0b) = baseElementId - 2;                   // Set ID: 0, 4, 8, ...

            *(int**)(currentSlot + 4 + m_pSlotArray) = (int*)(m_pDataBuffer + dataOffset + 0x30); // Second element
            *(*(int**)(currentSlot + 4 + m_pSlotArray) + 0x0b) = baseElementId - 1;               // ID: 1, 5, 9, ...

            *(int**)(currentSlot + 8 + m_pSlotArray) = (int*)(m_pDataBuffer + dataOffset + 0x60); // Third element
            *(*(int**)(currentSlot + 8 + m_pSlotArray) + 0x0b) = baseElementId;                   // ID: 2, 6, 10, ...

            *(int**)(currentSlot + 0xc + m_pSlotArray) = (int*)(m_pDataBuffer + dataOffset + 0x90); // Fourth element
            *(*(int**)(currentSlot + 0xc + m_pSlotArray) + 0x0b) = baseElementId + 1;             // ID: 3, 7, 11, ...

            // Advance to the next block (each block is 0xC0 bytes and contains 4 elements)
            dataOffset += 0xC0;          // 4 elements * 0x30 size = 0xC0
            currentSlot += 0x10;         // 4 pointers in m_pSlotArray (4 * 4 = 0x10)
            baseElementId += 4;          // Each block adds 4 to the ID base
        } while (baseElementId < 0x3FE); // Loop until we've set IDs 0..1023 (i.e., 256 blocks)

        // Mark the pool as initialized
        m_bInitialized = 1;

        // Notify internal system about the newly allocated slots
        updateSlotArray(this, m_nSlotCount);
    }
}