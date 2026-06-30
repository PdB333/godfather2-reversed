// FUNC_NAME: HandleManager::RemapIndices

// Reconstructed from 0x005207a0
// This function remaps or resets integer handles stored in an array of 0x20-byte structures.
// The class (assumed to be HandleManager) contains:
//   - m_items (pointer to array of ItemStruct) at +0x04
//   - m_count (number of items) at +0x08
//   - m_resetFlag (boolean flag) at +0x0C
//   - m_remapTable (array of ints) at +0x18
// Each item structure has a handle at offset 0x1C (the last dword of the 0x20-byte struct).

struct ItemStruct {
    char pad_0x00[0x1C]; // 0x00 - 0x1B
    int m_handle;        // +0x1C: index/handle to be remapped or cleared
}; // size = 0x20

class HandleManager {
public:
    ItemStruct* m_items;      // +0x04
    int m_count;              // +0x08
    char m_resetFlag;         // +0x0C: 0 = remap, non-zero = clear handles
    int m_remapTable[];       // +0x18: variable-length array of ints

    // __thiscall
    void RemapIndices(void);
};

void HandleManager::RemapIndices(void) {
    if (m_resetFlag == '\0') {
        // Remap handles: each item's handle is used as an index into m_remapTable,
        // and the table value replaces the handle.
        for (int i = 0; i < m_count; i++) {
            m_items[i].m_handle = m_remapTable[m_items[i].m_handle];
        }
    } else {
        // Clear handles to zero.
        for (int i = 0; i < m_count; i++) {
            m_items[i].m_handle = 0;
        }
    }
}