// FUN_004837e0: DynamicArray::insert
void* DynamicArray::insert(int index)
{
    // Ensure capacity before insertion
    if (m_nCount == m_nCapacity)
    {
        int newCapacity = (m_nCapacity == 0) ? 1 : (m_nCapacity * 2);
        reallocate(newCapacity); // FUN_00483960 – increases capacity and reallocates data
    }

    int count = m_nCount;
    if (index == count)
    {
        // Inserting at the end: just increment count and return address of new slot
        m_nCount = count + 1;
        return (void*)((uint8_t*)m_pData + index * 16);
    }

    // Element size = 16 bytes (two uint64_t halves)
    // Save the last element to the newly allocated slot at the end
    uint8_t* lastSlot = (uint8_t*)m_pData + count * 16;
    *(uint64_t*)lastSlot = *(uint64_t*)(lastSlot - 16);          // first 8 bytes from element count-1
    *(uint64_t*)(lastSlot + 8) = *(uint64_t*)(lastSlot - 8);    // second 8 bytes

    // Shift elements from [index .. count-2] one position to the right
    int lastIndex = count - 1;
    if (index < lastIndex)
    {
        int numToShift = lastIndex - index;
        int offset = lastIndex * 16;
        do
        {
            uint8_t* current = (uint8_t*)m_pData + offset;
            *(uint64_t*)current = *(uint64_t*)(current - 16);       // copy first half from left neighbour
            *(uint64_t*)(current + 8) = *(uint64_t*)(current - 8); // copy second half
            offset -= 16;
            numToShift--;
        } while (numToShift != 0);
    }

    m_nCount++;
    return (void*)((uint8_t*)m_pData + index * 16);
}