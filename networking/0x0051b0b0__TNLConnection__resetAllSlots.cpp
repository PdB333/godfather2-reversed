// FUNC_NAME: TNLConnection::resetAllSlots
class TNLConnection {
public:
    // offsets:
    // +0x0c: connection flags (uint32)
    // +0x7c: unknown (cleared to 0)
    // +0x80: slotCount (int16)
    // +0x82: lastAck? (int16, cleared to 0)
    // +0xf0: array of Slot (20 bytes each)

    struct Slot {
        uint32_t flags;    // +0x00
        uint32_t objectPtr; // +0x04 (non-null if active)
        // +0x08-0x13: reserved (12 bytes)
    };

    void resetAllSlots() {
        // Clear specific flags in connection flags
        uint32_t connFlags = *(uint32_t*)(this + 0x0c);
        connFlags &= 0xfff6ffff;  // clear bit16 and bit19
        *(uint32_t*)(this + 0x0c) = connFlags;

        // Reset counters
        *(uint32_t*)(this + 0x7c) = 0;
        *(int16_t*)(this + 0x82) = 0;

        int16_t count = *(int16_t*)(this + 0x80);
        if (count > 0) {
            Slot* slot = (Slot*)(this + 0xf0);
            for (int i = 0; i < count; i++, slot++) {
                if (slot->objectPtr != 0) {
                    slot->flags |= 0x4000000;  // set bit26 (active flag)
                    releaseSlotObject();       // release the slot's object
                    slot->objectPtr = 0;
                }
                slot->flags &= 0xe7ffffff;    // clear bits27 and bit28
            }
        }
    }

private:
    void releaseSlotObject(); // defined elsewhere
};