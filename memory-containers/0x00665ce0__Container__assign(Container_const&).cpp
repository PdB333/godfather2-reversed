// FUNC_NAME: Container::assign(Container const&)
int Container::assign(Container const& other)
{
    // Check for self-assignment
    if (this == &other) {
        return 0;
    }

    // If the other container's size exceeds our capacity, attempt to grow
    if (m_capacity < other.m_size) {
        int growResult = growTo(other.m_size);
        if (growResult != 0) {
            return growResult;
        }
    }

    // Copy elements from other's data array to ours
    uint32_t* destData = reinterpret_cast<uint32_t*>(m_data);
    uint32_t* srcData  = reinterpret_cast<uint32_t*>(other.m_data);
    int i = 0;
    if (0 < other.m_size) {
        do {
            *destData = *srcData;
            i++;
            destData++;
            srcData++;
        } while (i < other.m_size);
    }

    // Zero out any remaining elements in our capacity
    if (i < m_capacity) {
        do {
            *destData = 0;
            i++;
            destData++;
        } while (i < m_capacity);
    }

    // Copy size and flags fields
    m_size = other.m_size;
    m_flags = other.m_flags;

    return 0;
}