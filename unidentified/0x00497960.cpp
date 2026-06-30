// FUN_NAME: KeyValueVector::add
void KeyValueVector::add(int key, int value)
{
    // Prepare insertion (e.g., ensure uniqueness or adjust internal buffer)
    // This function may modify the 'this' pointer (param_2) and takes a reference to key (param_1)
    FUN_00498950(&m_pData, &key);  // param_2 = &this, param_1 = &key

    // Grow buffer if full
    if (m_nSize == m_nCapacity)
    {
        int newCapacity = (m_nCapacity == 0) ? 1 : m_nCapacity * 2;
        FUN_00499230(newCapacity); // reallocate to new capacity
    }

    int index = m_nSize;
    int* entry = &m_pData[index * 2]; // each pair is 8 bytes (two ints)

    entry[0] = key;
    entry[1] = value;
    m_nSize++;
}