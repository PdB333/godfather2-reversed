// FUNC_NAME: EventQueue::dequeue
// Address: 0x0049c9e0
// This function pops an item from the queue. Returns combined success flag and data in upper bits.
// Fields:
//   +0x10: m_data (uint32_t) - the stored data value
//   +0x14: m_next (int) - the next item index or pointer
//   +0x1c: m_counter (int) - some counter, cleared on dequeue
uint32_t __thiscall EventQueue::dequeue(int &outId, uint32_t &outData) {
    if (m_next != 0) {
        outId = m_next;
        outData = m_data;
        m_next = 0;
        m_data = 0;
        m_counter = 0;
        // Return a 32-bit value: high byte = 1 (success), lower 24 bits = (outData >> 8)
        return (0x01000000) | (outData >> 8);
    }
    return 0;
}