// FUN_004a2f10: ActionSlotManager::processActiveSlots

class ActionSlotManager {
public:
    // Each entry in the array at offset +0x12C (300) is 8 bytes:
    //   +0x00: void* objectPtr
    //   +0x04: unknown/padding (not used in this function)
    struct SlotEntry {
        void* objectPtr;
        char _pad[4];
    };

    // Assumed array: m_slots[4];  // +0x12C
    // Method at 0x004a1f50 (process single slot)
    void handleSlot(uint32_t slotIndex);

    // Function at 0x004a2f10
    void processActiveSlots();
};

void ActionSlotManager::processActiveSlots() {
    uint32_t index = 0;
    SlotEntry* entries = reinterpret_cast<SlotEntry*>(
        reinterpret_cast<uintptr_t>(this) + 0x12C
    );

    do {
        void* obj = entries[index].objectPtr;
        if (obj == nullptr) {
            // Null pointer – array not fully initialized; abort.
            return;
        }

        // Check byte at offset +8 of the pointed object.
        // A non‑zero value indicates this slot requires processing.
        char* objBase = static_cast<char*>(obj);
        if (objBase[8] == '\0') {
            // Slot is inactive; advance to the next one.
            index++;
        } else {
            // Active slot – delegate processing.
            // handleSlot() is expected to clear the flag, so on the next
            // iteration the same slot will be skipped and index will advance.
            this->handleSlot(index);
            // Note: index is NOT incremented – we re‑check this slot until
            // the flag is cleared by handleSlot().
        }
    } while (index < 4);
}