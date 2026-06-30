// FUNC_NAME: DynamicArray::pushBack
void DynamicArray::pushBack(int32_t* element)
{
    // If the array is full, grow the capacity
    if (m_size == m_capacity)
    {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reallocate(newCapacity);
    }

    // Write the element at the end and increment size
    int32_t* dest = &m_data[m_size];
    m_size++;
    if (dest != nullptr)
    {
        *dest = *element;
    }
}