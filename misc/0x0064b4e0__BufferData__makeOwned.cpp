// FUNC_NAME: BufferData::makeOwned

// Reconstructed C++ for function at 0x0064b4e0
// Makes the buffer own its data by allocating a new copy if not already owned.
// Offsets: +0x0c = data pointer, +0x10 = data size, +0x14 = owned flag (bool)

void BufferData::makeOwned()
{
    // Check if this buffer already owns its data
    if (!m_bOwned) // +0x14
    {
        // Allocate new memory of the same size
        void* pNewData = malloc(m_nSize); // +0x10

        // Copy the existing data into the new buffer
        memcpy(pNewData, m_pData, m_nSize); // +0x0c = source pointer

        // Update the pointer to the newly owned buffer
        m_pData = pNewData; // +0x0c

        // Mark as owned
        m_bOwned = true; // +0x14
    }
}