// FUNC_NAME: ObjectHandleManager::insert

#include <cstdint>

// Global data: array of 32 object entries (12 bytes each) at 0x1222328, count at 0x12224a8
static ObjectEntry g_objects[32];   // +0x00: 8 bytes key, +0x08: 4 bytes value (or similar)
static uint32_t g_objectCount;      // number of valid entries

struct ObjectEntry {
    uint64_t field0; // +0x00
    uint32_t field1; // +0x08
};

// __fastcall: ECX = this (unused), EDX = index, ESI = pointer to source entry
// Returns a handle: ((address of inserted slot) >> 8) | 1
uint32_t __fastcall ObjectHandleManager::insert(void* /*this*/, uint32_t index, const ObjectEntry* srcEntry) {
    if (g_objectCount > 31) {
        // Array full, return error code (count with low byte zeroed)
        return g_objectCount & 0xFFFFFF00;
    }

    if (index != g_objectCount) {
        // Inserting at a position before the end: shift elements to make room.
        // First preserve the last element by copying it to the end (g_objectCount is currently the next free slot)
        g_objects[g_objectCount] = g_objects[g_objectCount - 1];

        // Shift elements from g_objectCount-1 down to index+1 to the right
        for (int i = g_objectCount - 1; i > (int)index; i--) {
            g_objects[i] = g_objects[i - 1];
        }
    }

    // Place new element at the index
    g_objects[index] = *srcEntry;
    g_objectCount++;

    // Build handle from address of the inserted slot
    uintptr_t slotAddr = reinterpret_cast<uintptr_t>(&g_objects[index]);
    return (static_cast<uint32_t>(slotAddr >> 8) | 1);
}