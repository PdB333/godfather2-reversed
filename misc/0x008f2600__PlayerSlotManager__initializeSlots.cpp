// FUNC_NAME: PlayerSlotManager::initializeSlots
// Function at 0x008f2600: Initializes an array of 6 player slots (each 0x156 bytes) and global name/description buffers.

int __fastcall PlayerSlotManager::initializeSlots(void* this) {
    // +0x000: char m_name[64] (global)
    // +0x040: char m_description[256] (global)
    // +0x130: char m_terminator (null byte)
    // +0x140: int m_prevSlot (link for first slot)
    // +0x144: start of slot array (6 slots, each 0x156 bytes)
    // Slot structure (relative to slotBase):
    //   -0x4: int m_prev (link to previous slot)
    //   +0x0: int m_next (link to next slot)
    //   +0x4..+0x150: other fields (strings, etc.) – initialized via helper calls
    // +0x2010: int m_slotCount (set to 0)

    int slotIndex = 5;  // loop from 5 down to 0
    uint8_t* slotBase = (uint8_t*)this + 0x144;  // start of slot array

    do {
        // Initialize linked-list pointers
        *(uint32_t*)(slotBase - 4) = 0;  // m_prev = 0
        *(uint32_t*)(slotBase) = 0;       // m_next = 0

        // Call slot-specific initialization (probably sets default values)
        FUN_00acc780();   // likely slot::initDefaults1()
        FUN_00accc70();   // likely slot::initDefaults2()

        // Initialize two string buffers (global) – these are written repeatedly,
        // but only the last iteration matters (all set to empty).
        _strncpy((char*)(slotBase - 0x144), "", 0x3f);   // m_name (at +0x000)
        *(uint8_t*)(slotBase - 0x14) = 0;                 // null terminator at +0x130

        _strncpy((char*)(slotBase - 0x104), "", 0xff);    // m_description (at +0x040)
        *(uint8_t*)(slotBase - 5) = 0;                    // null terminator for description

        // Move to next slot (size 0x156 = 342 bytes)
        slotBase += 0x156;
        slotIndex--;
    } while (slotIndex >= 0);

    *(uint32_t*)((uint8_t*)this + 0x2010) = 0;  // m_slotCount = 0
    return (int)this;
}