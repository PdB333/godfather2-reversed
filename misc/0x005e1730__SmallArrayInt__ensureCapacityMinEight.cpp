// FUNC_NAME: SmallArrayInt::ensureCapacityMinEight
void SmallArrayInt::ensureCapacityMinEight() {
    if (m_nCapacity >= 8) {
        return;
    }

    // Allocate new buffer of 32 bytes (capacity 8 ints)
    int* pNewData = (int*)allocateMemory(0x20);

    if (m_pData != nullptr) {
        // Copy existing elements
        for (uint i = 0; i < m_nCount; i++) {
            pNewData[i] = m_pData[i];
        }
        // Free old buffer
        freeMemory(m_pData);
    }

    m_pData = pNewData;
    m_nCapacity = 8;
}