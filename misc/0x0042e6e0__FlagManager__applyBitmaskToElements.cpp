// FUNC_NAME: FlagManager::applyBitmaskToElements

// Reconstructed from address 0x0042e6e0
// This function iterates over an array of elements (0xB0 bytes each) in the manager (this).
// For each element whose state byte (at +0x29) is 0 or 2, it uses a short index (at +0x2A)
// to set or clear a bit (from global g_bitmask) in a ushort array owned by a target object.
// The target object is identified by the element's type (0 or 2) and the caller-supplied objectId.
// Target objects are stored in a global array of size 0x6A0 per type, starting at offset 0x1230.

class FlagManager {
public:
    // Assumed structure offsets:
    // +0x34: elementCount (uint32)
    // +0x50: pElements (Element*) - pointer to array of Element (each 0xB0 bytes)

    // Element structure (0xB0 bytes):
    // +0x29: state (uint8) - expected values 0 or 2 to be processed
    // +0x2A: index (int16) - index into target's bit array

    // Global bitmask used for the operation (from _DAT_012053d8)
    static uint16 g_bitmask; // Actually read as undefined4 but used as ushort16

    void applyBitmaskToElements(int objectId, bool setBit) {
        uint32 elementCount = *(uint32*)((uint32)this + 0x34);
        if (elementCount == 0) return;

        uint16 bitmask = (uint16)g_bitmask; // Only low 16 bits matter
        Element* pElementBase = *(Element**)((uint32)this + 0x50);

        for (uint32 i = 0; i < elementCount; i++) {
            Element* pElement = &pElementBase[i];
            uint8 state = *(uint8*)((uint32)pElement + 0x29);

            if (state < 5 && (state == 0 || state == 2)) {
                // State type determines which global target array to use
                // Target array base = 0x1230 + state * 0x6A0 + objectId
                uint32 targetBase = 0x1230 + state * 0x6A0 + objectId;

                int16 index = *(int16*)((uint32)pElement + 0x2A);
                uint32 arrayLength = *(uint32*)(targetBase + 0x38);

                if (index >= 0 && index < (int32)arrayLength) {
                    uint16* pBitArray = *(uint16**)(targetBase + 0x0C);
                    if (setBit) {
                        pBitArray[index] |= bitmask;
                    } else {
                        pBitArray[index] &= ~bitmask;
                    }
                }
            }
        }
    }

private:
    // Dummy structure for clarity (actual layout doesn't need to be defined here)
    struct Element {
        // ... other fields up to offset 0x29, 0x2A
    };
};

// Global bitmask value (defined elsewhere, likely at 0x012053D8)
uint16 FlagManager::g_bitmask;