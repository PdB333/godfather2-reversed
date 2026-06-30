// FUNC_NAME: FlagManager::modifyFlag
// Address: 0x004c5340
// This function sets or clears a global bitmask on the flag associated with a given item ID.
// It iterates over an array of items, finds the one with matching ID, and updates the corresponding ushort flag.

extern unsigned short g_flagMask; // DAT_012053d8

class FlagManager {
public:
    // param_1 = item ID to match, param_2 = enable (1 to set, 0 to clear)
    void modifyFlag(int id, bool enable) __thiscall;
private:
    int m_count;           // +0x38 : number of items
    void* m_pItems;        // +0x10 : pointer to array of ItemStruct (0x20 bytes each)
    unsigned short* m_pFlags; // +0x0c : pointer to array of ushort flags, one per item
};

struct ItemStruct {
    char padding[0x1c]; // +0x00 - +0x1b
    int id;             // +0x1c : item ID
};

void FlagManager::modifyFlag(int id, bool enable) {
    if (m_count <= 0)
        return;

    unsigned short mask = g_flagMask;
    int index = 0;
    int offset = 0; // byte offset into m_pItems array (each item is 0x20 bytes)

    if (!enable) {
        // Clear the mask bits for the matching item
        while (index < m_count) {
            ItemStruct* item = (ItemStruct*)((char*)m_pItems + offset);
            if (item->id == id) {
                m_pFlags[index] &= ~mask;
            }
            ++index;
            offset += 0x20;
        }
    } else {
        // Set the mask bits for the matching item
        while (index < m_count) {
            ItemStruct* item = (ItemStruct*)((char*)m_pItems + offset);
            if (item->id == id) {
                m_pFlags[index] |= mask;
            }
            ++index;
            offset += 0x20;
        }
    }
}