// FUNC_NAME: cContainer::getElementByTwoIndices
// Address: 0x00625950
// Role: Retrieves an element from a container using two indices.
// If either index is less than 1, it substitutes a random index.
// The container stores 8-byte elements between a start and end pointer.
// This function likely belongs to a custom EA EARS container.

// Member offsets:
// +0x08 = m_pStart  (pointer to first element)
// +0x0C = m_pEnd    (pointer to one past the last element)

unsigned int __thiscall cContainer::getElementByTwoIndices(int index1, int index2)
{
    unsigned int addr1;
    unsigned int addr2;

    // Compute address for index1
    if (index1 < 1)
    {
        // Generate random index
        addr1 = getRandomNumber(); // FUN_00625430
    }
    else
    {
        // Calculate: m_pEnd - 8 + index1 * 8
        addr1 = (unsigned int)(m_pEnd - 8 + index1 * 8);
        // Clamp to zero if below the start pointer (invalid)
        if (addr1 < (unsigned int)m_pStart)
            addr1 = 0;
    }

    // Compute address for index2
    if (index2 < 1)
    {
        addr2 = getRandomNumber(); // FUN_00625430
    }
    else
    {
        addr2 = (unsigned int)(m_pEnd - 8 + index2 * 8);
        if (addr2 < (unsigned int)m_pStart)
            addr2 = 0;
    }

    // Only return valid data if both addresses are non-zero
    if ((addr1 != 0) && (addr2 != 0))
    {
        return getSlotValue(addr2); // FUN_00634150 - retrieves value at address
    }

    return 0;
}