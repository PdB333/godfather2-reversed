// FUNC_NAME: IntPairMap::add
// Function address: 0x00895000
// Role: Add a key-value pair (where key is stored at offset 0x04 in each 8-byte entry) if the key is not already present.
// Fields:
//   +0x48 m_pData    (int*) – pointer to array of pairs (each pair: [value, key])
//   +0x4c m_count    (uint) – current number of pairs
//   +0x50 m_capacity (int)  – allocated capacity (number of pairs)

void __thiscall IntPairMap::add(int key, int value)
{
    uint index = 0;

    // Search for existing key
    if (m_count != 0) {
        int* keyPtr = m_pData + 1;       // start at first pair's key (second 4 bytes)
        do {
            if (*keyPtr == key) {
                if (index != 0xffffffff) {
                    return;              // key already present – no duplicate
                }
                break;
            }
            index++;
            keyPtr += 2;                 // advance to next pair's key (skip 8 bytes)
        } while (index < m_count);
    }

    // Key not found – add new pair
    if (m_count == m_capacity) {
        int newCapacity = (m_capacity == 0) ? 1 : m_capacity * 2;
        reserve(newCapacity);            // grow the dynamic array (FUN_00893840)
    }

    // Write new pair at end of array
    int* newPair = m_pData + m_count * 2;
    newPair[0] = value;   // first 4 bytes: value
    newPair[1] = key;     // next 4 bytes: key

    m_count++;
}