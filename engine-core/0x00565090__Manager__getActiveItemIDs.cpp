// FUNC_NAME: Manager::getActiveItemIDs
#include <cstdint>

// SubItem structure assumed:
// +0x00: ???
// +0x129: char m_isActive; // Active flag (non-zero if active)
struct SubItem {
    char data[0x129]; // placeholder for fields up to 0x129
    char m_isActive;
};

// Item structure assumed:
// +0x00: SubItem* m_subItems[4]; // Array of up to 4 sub-item pointers
// +0x10: uint32_t m_subItemCount; // Number of valid sub-items (0-4)
// +0x3c: uint32_t m_id; // Unique identifier for this item
struct Item {
    SubItem* m_subItems[4]; // +0x00
    uint32_t m_subItemCount; // +0x10
    // other fields...
    uint32_t m_id; // +0x3c
};

// Manager class (unknown name):
// +0x24: Item* m_items[]; // Fixed-size array of item pointers (size unknown, count gives valid)
// +0x124: uint32_t m_itemCount; // Number of items in the array
class Manager {
public:
    // Offset +0x24: pointer to items? Actually used as array start.
    Item* m_items; // not a pointer; the address itself is the array start
    uint32_t m_itemCount; // +0x124

    void __thiscall getActiveItemIDs(uint32_t* outBuffer);
};

void __thiscall Manager::getActiveItemIDs(uint32_t* outBuffer)
{
    Item* collectedItems[64]; // Local buffer for temporary storage
    uint32_t collectedCount = 0;

    if (this->m_itemCount != 0) {
        // Iterate through all items
        for (uint32_t i = 0; i < this->m_itemCount; ++i) {
            Item* item = &this->m_items[i]; // Note: m_items is used as array base (not pointer to array)
            // Check if item has any sub-items
            if (item->m_subItemCount != 0) {
                // Check each sub-item for active flag
                for (uint32_t j = 0; j < item->m_subItemCount; ++j) {
                    SubItem* sub = item->m_subItems[j];
                    // Offset +0x129: active flag (char, non-zero means active)
                    if (sub->m_isActive != 0) {
                        if (collectedCount < 64) {
                            collectedItems[collectedCount] = item;
                            collectedCount++;
                        }
                        break; // Only need one active sub-item to collect this item
                    }
                }
            }
        }
    }

    // Write count to output buffer
    *outBuffer = collectedCount;
    outBuffer++;

    // Write IDs of all collected items
    for (uint32_t i = 0; i < collectedCount; ++i) {
        // Offset +0x3c: item ID (uint32)
        outBuffer[i] = collectedItems[i]->m_id;
    }
}