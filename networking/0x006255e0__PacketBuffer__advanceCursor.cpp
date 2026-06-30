// FUNC_NAME: PacketBuffer::advanceCursor
// Address: 0x006255e0
// Role: Adjusts the buffer's current pointer forward or backward by a number of 8-byte elements.
// When moving forward (delta >= 0), zeroes elements between the old current and new position.
// When moving backward (delta < 0), moves the current pointer back by (|delta|-1) elements.
// Structure offsets:
//   +0x08 : m_current (uint8_t*) - current read/write position in the buffer
//   +0x0C : m_start  (uint8_t*) - base address of the allocated buffer

void __fastcall PacketBuffer::advanceCursor(int delta)
{
    // delta is signed; negative means move backward, positive means move forward
    if (delta < 0) {
        // Move current pointer backward: new_pos = old_pos + delta*8 + 8
        // For delta = -1, this results in no change ( -8 + 8 = 0 )
        // For delta = -2, moves back 8 bytes (one element)
        m_current = m_current + delta * 8 + 8;
        return;
    }

    // Forward move: compute target position based on m_start
    int elementOffset = delta * 8;
    uint8_t* target = m_start + elementOffset;

    // Zero out elements from current position to target (exclusive)
    while ((uintptr_t)m_current < (uintptr_t)target) {
        // Zero the first 4 bytes of the 8-byte element (clears a pointer or sequence number)
        *(uint32_t*)m_current = 0;
        m_current += 8;
    }

    // Set the current pointer to the new target position
    m_current = target;
}