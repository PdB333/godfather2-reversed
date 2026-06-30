// FUNC_NAME: DataBuffer::reserveElements
bool __thiscall DataBuffer::reserveElements(uint32_t elementCount) {
    // Check if total elements would exceed max (0x4000 = 16384)
    if (0x4000 < ((m_writeOffset - m_readOffset) >> 3) + elementCount) {
        return false;
    }

    // If not enough remaining capacity for requested elements (each 8 bytes), grow buffer
    if (m_capacity - m_writeOffset <= elementCount * 8) {
        growBuffer(); // FUN_00635c70
    }

    uint32_t newWriteOffset = m_writeOffset + elementCount * 8;
    // Update max used offset for statistics
    if (m_pUsageInfo->maxUsedOffset < newWriteOffset) {
        m_pUsageInfo->maxUsedOffset = newWriteOffset;
    }

    return true;
}