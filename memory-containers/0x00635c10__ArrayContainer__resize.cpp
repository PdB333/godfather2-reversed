// FUNC_NAME: ArrayContainer::resize

void ArrayContainer::resize(short newCount) // newCount passed in EDI
{
    int elementSize = 0x18; // 24 bytes per element

    // Get old data pointer
    char* oldData = m_pData; // +0x28

    // Reallocate: call with old size (oldCount * elementSize) and new size (newCount * elementSize)
    char* newData = (char*)FUN_006279a0((uint)m_count * elementSize, (uint)newCount * elementSize);

    // Adjust cursor pointer (m_pCursor, +0x14) relative to new base, aligned to element boundary
    m_pCursor = newData + ((m_pCursor - oldData) / elementSize) * elementSize;

    // Update data pointer and count
    m_pData = newData; // +0x28
    m_count = newCount; // +0x2c
    m_pEnd = newData + (newCount & 0xFFFF) * elementSize; // +0x24
}