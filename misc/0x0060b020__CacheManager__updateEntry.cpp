// FUNC_NAME: CacheManager::updateEntry
// Address: 0x0060b020
// Compares a block of data (16-byte aligned chunks) against a cached entry in one of two tables
// (regular or pending) selected by the top bit of packedIndexCount. If different, copies the new
// data and notifies the global CacheManager via a virtual callback (vtable offset 0x1b4 for regular,
// 0x178 for pending). The first parameter (this/param_1) is unused—the method functions as a static
// helper on behalf of the global CacheManager singleton at 0x01205750.

// Global tables: regular table at 0x011d97f0, pending table at 0x011ea8f0.
// Each table entry is 16 bytes. Index = packedIndexCount & 0xFF,
// blockCount = (packedIndexCount >> 8) & 0xFF (number of 16-byte blocks to compare/copy).
// The total data size is blockCount * 16 bytes.

#include <cstring>

// Forward declaration of the CacheManager class (vtable layout unknown, but we assume two methods)
class CacheManager {
public:
    // vtable+0x1b4 (regular update)
    void __thiscall onRegularEntryUpdated(int index, const byte* data, int blockCount);
    // vtable+0x178 (pending update)
    void __thiscall onPendingEntryUpdated(int index, const byte* data, int blockCount);
};

// The global pointer to the CacheManager singleton (stored at address 0x01205750)
#define GET_CACHE_MANAGER() (*(CacheManager**)(0x01205750))

// The static tables (global arrays)
static constexpr uint kEntrySize = 16; // bytes per slot
static byte* s_regularTable = reinterpret_cast<byte*>(0x011d97f0);
static byte* s_pendingTable = reinterpret_cast<byte*>(0x011ea8f0);

void CacheManager::updateEntry(uint packedIndexCount, const byte* sourceData) {
    if (packedIndexCount == 0) {
        return;
    }

    uint index      = packedIndexCount & 0xFF;
    uint blockCount = (packedIndexCount >> 8) & 0xFF;
    bool usePending = (packedIndexCount & 0x80000000) != 0;

    // Select destination entry
    byte* destEntry;
    if (!usePending) {
        destEntry = s_regularTable + index * kEntrySize;
    } else {
        destEntry = s_pendingTable + index * kEntrySize;
    }

    // Compare source with cached entry (total size = blockCount * 16)
    if (std::memcmp(destEntry, sourceData, blockCount * kEntrySize) == 0) {
        return; // No change
    }

    // Copy new data over the existing entry
    std::memcpy(destEntry, sourceData, blockCount * kEntrySize);

    // Notify the global CacheManager via the appropriate virtual callback
    CacheManager* mgr = GET_CACHE_MANAGER();
    if (usePending) {
        mgr->onPendingEntryUpdated(index, destEntry, blockCount);
    } else {
        mgr->onRegularEntryUpdated(index, destEntry, blockCount);
    }
}