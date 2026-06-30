// FUNC_NAME: ConnectionManager::addConnection
void ConnectionManager::addConnection(int connection)
{
    // Check for duplicates in the connection array
    uint count = m_count; // +0x90
    if (count != 0)
    {
        int* array = m_array; // +0x8c
        uint index = 0;
        do
        {
            if (array[index] == connection)
            {
                // Already present, do nothing
                return;
            }
            index++;
        } while (index < count);
    }

    // Get associated data from the connection object
    int* connectionData = *(int**)(connection + 0xa0);

    // Call first-time initialization hook
    FUN_0049cf80();

    // Check flags: if this manager has a special flag (0x02) and the connection has a flag (0x01 at +0xb2)
    if ((m_flags & 0x02) != 0 && (*(byte*)(connection + 0xb2) & 0x01) != 0)
    {
        FUN_0049feb0();
        FUN_0049ef30(extraout_ECX);
    }

    // Ensure connectionData's ID matches ours, otherwise update
    if (*(int*)(connectionData + 0x38) != m_expectedId) // +0x84 ?
    {
        FUN_0049f5e0(*(int*)(connectionData + 0x38));
    }

    // Grow the array if needed
    int capacity = m_capacity; // +0x94
    if (m_count == capacity)
    {
        if (capacity == 0)
            capacity = 1;
        else
            capacity *= 2;
        FUN_004a0210(capacity);
    }

    // Add the new connection pointer to the array and increment count
    int* destSlot = m_array + m_count * 4;
    m_count++; // +0x90
    if (destSlot != nullptr)
    {
        *destSlot = connection;
    }

    // Check if the connection data indicates a special flag (0x04 at +0x24)
    if ((*(byte*)(connectionData + 0x24) & 0x04) != 0)
    {
        // If not already created, allocate and initialize a callback object
        if (m_callbackObj == 0) // +0x18
        {
            int alloc = FUN_0049e8b0(0xb0);
            int obj;
            if (alloc == 0)
                obj = 0;
            else
                obj = FUN_0044daa0(0);
            m_callbackObj = obj; // +0x18
            FUN_00450340();

            // If manager has the 0x02 flag, insert into a global linked list (DAT_012233a4)
            if ((m_flags & 0x02) != 0)
            {
                int* listHead = (int*)(DAT_012233a4 + 0x10);
                if (*(int*)(DAT_012233a4 + 0x10) != 0)
                {
                    *(int*)(*(int*)(DAT_012233a4 + 0x10) + 0x9c) = m_callbackObj;
                }
                *(int*)(m_callbackObj + 0xa0) = *listHead;
                *listHead = m_callbackObj;
            }
        }
        FUN_0049d0c0(&LAB_0049eab0, m_callbackObj);
    }

    // Update a float value if different from a global constant
    if (m_thresholdFloat != DAT_00e2b05c) // +0xa0
    {
        FUN_0049eb50();
        *(int*)(connectionData + 0x74) = m_someValue; // +0x80
    }
}