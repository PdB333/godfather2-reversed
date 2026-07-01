// FUNC_NAME: BitfieldManager::clearAllSlots
// Address: 0x007f7e40
// Clears bit flags for up to 10 slots (bits 0-9) in two bitfields at +0x604 and +0x608.
// Resets two counters at +0x60c and +0x1b90 to zero.
// Calls an external function when clearing slot 9 (possibly a special finalization).
void __thiscall BitfieldManager::clearAllSlots(uint8_t *this)
{
  uint8_t slotIdx = 0;
  do {
    // Clear bit 'slotIdx' in both bitfields
    uint32_t mask = ~(1 << (slotIdx & 0x1f));
    *(uint32_t *)(this + 0x604) &= mask; // m_activeFlags
    *(uint32_t *)(this + 0x608) &= mask; // m_dirtyFlags
    *(uint32_t *)(this + 0x60c) = 0;     // m_count
    *(uint32_t *)(this + 0x1b90) = 0;    // m_anotherCounter
    if (slotIdx == 9) {
      // Slot 9 has special handling; call function with argument 0
      FUN_00549cf0(0); // e.g., OnClearLastSlot()
    }
    slotIdx++;
  } while ((int8_t)slotIdx < 10);
  return;
}