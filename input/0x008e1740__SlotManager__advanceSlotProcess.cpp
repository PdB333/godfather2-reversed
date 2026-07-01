// FUNC_NAME: SlotManager::advanceSlotProcess
// Address: 0x008e1740
// Iterates through an array of 8 data slots (each 0x10 bytes) at +0x17C.
// Tracks current slot index at +0x178. When an empty slot (first dword == 0) is found,
// calls handleEmptySlot() and resets index to -1. Otherwise either advances to next slot
// or resets to -1 when all slots have been checked.
class SlotManager {
public:
    int32_t m_currentSlotIndex; // +0x178
    // Slot array of size 8, each 0x10 bytes, starting at +0x17C
    // Slot data: first 4 bytes indicate occupancy (0 = empty)
};

void __fastcall SlotManager::advanceSlotProcess() {
    if (m_currentSlotIndex == -1) {
        // Start from the beginning
        m_currentSlotIndex = 0;
        return;
    }

    int32_t newIndex = m_currentSlotIndex + 1;
    m_currentSlotIndex = newIndex;

    if (newIndex < 8) {
        // Check if this slot is empty
        if (*(int32_t*)(reinterpret_cast<uint8_t*>(this) + 0x17C + newIndex * 0x10) == 0) {
            // Empty slot found – process it and restart scan
            m_currentSlotIndex = -1;
            FUN_008e1480(); // handleEmptySlot
            return;
        }
        // Slot occupied – nothing to do, next call will advance further
    } else {
        // Scanned all slots with no empty slot – restart
        m_currentSlotIndex = -1;
    }
}