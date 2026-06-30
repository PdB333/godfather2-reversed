// FUNC_NAME: MessageQueue::push

bool MessageQueue::push(int value)
{
    // Critical section for thread safety (offset +0x10 in struct, decompiler showed +0x04 erroneously)
    EnterCriticalSection(&m_cs);

    bool success = false;

    if (m_count < m_capacity)                             // compare count (offset +0x0C) with capacity (offset +0x04)
    {
        // Compute write position as (head + count) % capacity
        int writeIndex = m_head + m_count;                // m_head at +0x08
        ++m_count;                                        // increment count

        if (m_capacity <= writeIndex)                     // wrap around
        {
            writeIndex -= m_capacity;                     // modulo operation
        }

        m_data[writeIndex] = value;                       // m_data at +0x00
        success = true;
    }

    LeaveCriticalSection(&m_cs);
    return success;
}