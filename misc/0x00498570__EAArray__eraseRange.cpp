// FUNC_NAME: EAArray::eraseRange
void __thiscall EAArray::eraseRange(void ** begin, void ** end)
{
    // +0x00: m_pData (pointer to element array)
    // +0x04: m_size (number of elements)
    int *data = m_pData;
    int size = m_size;
    uint32_t *current = (uint32_t *)begin;
    uint32_t *stop = (uint32_t *)end;

    if ((current != 0) && (current < stop)) {
        do {
            uint32_t *last = (uint32_t *)(data - 1 + size * 4);
            if (current < last) {
                int count = ((int)last + (-1 - (int)current) >> 2) + 1;
                // Shift elements left to overwrite the current element
                for (uint32_t *src = current + 1; count != 0; count--) {
                    *current = *src;
                    current++;
                    src++;
                }
            }
            m_size--;
            current++;
        } while (current != stop);
    }
}