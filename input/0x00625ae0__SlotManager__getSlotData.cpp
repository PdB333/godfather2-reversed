// FUNC_NAME: SlotManager::getSlotData
// Address: 0x00625ae0
// This function retrieves a value from a slot in an array of 8-byte entries.
// Each entry consists of a type field (int) and a pointer to a data structure.
// If type == 4, it returns the data at offset 0xc in the pointed structure.
// Otherwise, it checks a secondary validation (isValidEntry) before returning.
// Special case: if slotIndex < 1, it uses a default/null entry.

class SlotManager {
private:
    struct SlotEntry {
        int type;                // +0x00: entry type (4 = active)
        void* pData;            // +0x04: pointer to data object
    };

    SlotEntry* m_pArrayStart;   // +0x0c: pointer to first element in slot array
    SlotEntry* m_pArrayEnd;     // +0x08: pointer past the last element

    // Returns a pointer to a default/null entry when slotIndex is invalid.
    static SlotEntry* getNullEntry() {
        // Implemented elsewhere (FUN_00625430)
        return nullptr;
    }

    // Returns non-zero if the entry is considered valid (type check fallback).
    static int isValidEntry() {
        // Implemented elsewhere (FUN_00633990)
        return 0;
    }

public:
    // __thiscall: 'this' in ECX (decompiler shows EDI, but we treat as this)
    int __thiscall getSlotData(int slotIndex) {
        SlotEntry* entry;

        if (slotIndex < 1) {
            entry = getNullEntry();
        } else {
            // Compute pointer to slot entry: base + (slotIndex - 1) * sizeof(SlotEntry)
            entry = reinterpret_cast<SlotEntry*>(
                reinterpret_cast<int*>(m_pArrayStart) - 8 + slotIndex * 8
            );
            // Bounds check: entry must be less than m_pArrayEnd
            if (entry >= m_pArrayEnd) {
                return 0;
            }
        }

        if (entry != nullptr) {
            if (entry->type == 4) {
                // Direct access: return value at offset 0xc in data struct
                return *reinterpret_cast<int*>(
                    reinterpret_cast<char*>(entry->pData) + 0xc
                );
            }
            if (isValidEntry()) {
                return *reinterpret_cast<int*>(
                    reinterpret_cast<char*>(entry->pData) + 0xc
                );
            }
        }
        return 0;
    }
};