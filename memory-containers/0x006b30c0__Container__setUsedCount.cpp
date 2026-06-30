// FUNC_NAME: Container::setUsedCount
void __thiscall Container::setUsedCount(unsigned int newCount)
{
    // +0x64 = m_used (current number of used elements)
    // +0x58 = m_capacity (maximum capacity)
    // +0x40 = m_data (pointer to element data)
    // +0x38 = m_allocator (allocator or deallocation function object)
    if (m_used != newCount) {
        if (newCount < m_capacity) {
            // Free/destroy elements from newCount to capacity
            FUN_008c74d0(m_data);                         // Probably begin deallocation
            FUN_008be590(m_allocator, m_capacity - newCount); // Deallocate count elements
        }
        m_used = newCount;
    }
}