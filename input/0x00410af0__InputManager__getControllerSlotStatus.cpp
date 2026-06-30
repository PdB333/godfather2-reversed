// FUNC_NAME: InputManager::getControllerSlotStatus

class InputManager {
public:
    struct ControllerSlot {
        char active; // +0x00 of slot – first byte indicates active/occupied
        // ... remaining 0x43 bytes
    };

    // Array of 16 slots at offset 0x6a from 'this'
    // Each slot is 0x44 bytes
    ControllerSlot* getSlots() const {
        return reinterpret_cast<ControllerSlot*>(reinterpret_cast<char*>(this) + 0x6a);
    }

    // Returns:
    //   if input byte <= 15: 1 if slot is occupied, 0 if free
    //   if input byte == 0x11: finds first free slot (0-15), or 1 if none free
    //   other high bytes: returns input with low byte cleared (unlikely path)
    uint __thiscall getControllerSlotStatus(uint slotIndex) {
        uint lowByte = slotIndex & 0xFF;

        if (lowByte > 15) {
            // Scan for first free slot only if byte == 0x11
            if (lowByte == 0x11) {
                uint freeSlot = 0;
                ControllerSlot* slot = getSlots();
                while (slot->active != '\0') {
                    freeSlot++;
                    slot++;
                    if (freeSlot > 15) {
                        // No free slot found – return 1 (ambiguous, but caller knows context)
                        return 1;
                    }
                }
                return freeSlot;
            }
            // Any other high bytes: return original value with low byte zeroed
            return slotIndex & 0xFFFFFF00;
        }

        // Check if specific slot (0-15) is occupied
        if (lowByte < 16) {
            if (getSlots()[lowByte].active != '\0') {
                return 1;
            }
        }
        return 0;
    }
};