// FUNC_NAME: SlotManager::clearSlotFlag

// 0x006f0d60: SlotManager::clearSlotFlag - Clears a flag in a slot array (struct size 0x2c).
// Slot structure:
//   size 0x2c (44 bytes)
//   offset 0x29: BYTE m_flag (1 byte)
// m_pSlotArray stored at offset 0x64 (100 decimal) of this.

void __thiscall SlotManager::clearSlotFlag(int slotIndex) {
    if (m_pSlotArray != 0) {
        clearSlotCallback(); // call to FUN_006f0b90, likely a cleanup/notification
        m_pSlotArray[slotIndex].m_flag = 0; // clear the flag byte at +0x29
    }
}