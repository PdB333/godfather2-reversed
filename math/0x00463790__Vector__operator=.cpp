// FUNC_NAME: Vector::operator=
void Vector::operator=(const Vector& other)
{
    // self-assignment check
    if (this == &other) return;

    if (m_nCapacity < other.m_nSize)
    {
        // free old buffer
        MemFree(m_pData);  // FUN_009c8f10
        m_nCapacity = other.m_nSize;
        // allocate new buffer (4 bytes per element)
        m_pData = static_cast<int*>(MemAlloc(m_nCapacity * 4));  // FUN_009c8e80
    }

    // copy elements
    for (uint32 i = 0; i < other.m_nSize; i++)
    {
        m_pData[i] = other.m_pData[i];
    }

    m_nSize = other.m_nSize;
}
// Structure offsets: m_pData +0x0, m_nSize +0x4, m_nCapacity +0x8