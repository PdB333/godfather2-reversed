// FUNC_NAME: ObjectHandle::release
// Address: 0x004b1ca0
// __thiscall member function of an object handle class.
// The handle stores a 32-bit ID (low 16 bits = pool index, high bits = generation).
// Global pointer g_pObjectPool (0x012234bc) points to a PoolManager structure.
// Pool entries start at offset +0x10 from that pointer, each entry is 0x30 bytes.
// Entry fields: +0x24, +0x28 are cleared on release; +0x2c stores the full handle ID for validation.

struct PoolEntry {
    uint8_t pad_0x00[0x24];        // 0x00 - 0x23
    uint32_t field_0x24;           // +0x24 (cleared on release)
    uint32_t field_0x28;           // +0x28 (cleared on release)
    uint32_t handleID;             // +0x2c – full handle ID used to verify slot ownership
};

struct PoolManager {
    uint8_t header[0x10];          // +0x00 – unknown header
    PoolEntry entries[0x200];      // +0x10 – up to 0x200 entries (0x30 bytes each)
};

// Global pointer to the object pool manager
PoolManager* g_pObjectPool = (PoolManager*)0x012234bc;

// Forward declaration: called to free a pool slot by index
void freePoolSlot(uint32_t index, int param);

void ObjectHandle::release() {
    uint32_t handleID = *(uint32_t*)this;  // full handle ID from the handle object
    if (handleID != 0) {
        uint32_t index = handleID & 0xFFFF;  // low 16 bits are the pool index
        // First pass: clear selected fields in the pool entry if handle matches
        if ((index < 0x200) &&
            (g_pObjectPool != 0)) {
            PoolEntry* entry = &g_pObjectPool->entries[index];
            if (entry->handleID == handleID) {
                entry->field_0x24 = 0;
                entry->field_0x28 = 0;
            }
        }
        // Second pass: free the pool slot and invalidate handle
        if ((index < 0x200) &&
            (g_pObjectPool != 0)) {
            PoolEntry* entry2 = &g_pObjectPool->entries[index];
            if (entry2->handleID == handleID) {
                freePoolSlot(index, 0);
            }
        }
        *(uint32_t*)this = 0;  // clear the handle itself
    }
}