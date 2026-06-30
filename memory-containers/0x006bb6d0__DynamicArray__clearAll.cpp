// FUNC_NAME: DynamicArray::clearAll
// Address: 0x006bb6d0 – Clears all items in a dynamic array (each item 0x18 bytes) and frees the array memory.
// The first 4 bytes of each item is a pointer; if non‑null the item is considered allocated and is destroyed via destroyItem().

class DynamicArray {
public:
    struct Item {
        void* m_pData;   // +0x00: non‑null indicates a valid item
        // (remaining 0x14 bytes, not detailed here, total size 0x18)
    };

    // Clears all items and deallocates the array buffer
    void clearAll() {
        int count = m_count;
        // Iterate backward from the last element
        if (count > 0) {
            int index = count - 1;
            do {
                Item* pItem = &m_pItems[index];
                if (pItem->m_pData != nullptr) {
                    destroyItem(pItem);   // defined at 0x004daf90
                }
                --index;
            } while (index >= 0);
        }
        m_count = 0;
        // Free the array buffer and reset capacity/pointer
        if (m_pItems != nullptr) {
            freeArrayBuffer(m_pItems);    // defined at 0x009c8f10
        }
        m_pItems = nullptr;
        m_capacity = 0;
    }

private:
    Item* m_pItems;    // +0x00: dynamic array of Items
    int m_count;       // +0x04: number of currently stored items
    int m_capacity;    // +0x08: allocated capacity (number of items that fit)
};

// Helper function declarations (actual implementations elsewhere)
void destroyItem(DynamicArray::Item* pItem);
void freeArrayBuffer(void* pBuffer);