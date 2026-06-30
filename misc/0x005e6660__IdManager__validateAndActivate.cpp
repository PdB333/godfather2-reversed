// FUNC_NAME: IdManager::validateAndActivate
// Address: 0x005e6660
// Validates a 32-bit ID by extracting the low 16-bit slot index, checking bounds, 
// verifying the stored ID matches, and activating the slot if valid.

// Assumes a global table of entries, each 0x30 bytes, with ID stored at offset 0x2c.
// The table base is at g_pEntryTable (DAT_012234bc). Max 512 slots (0x200).

// Called by various subsystems (networking, object management) to confirm ID validity.

#include <cstdint>

// Forward declaration of activation helper (FUN_005e5e60)
bool activateEntry(uint16_t slotIndex, uint32_t unknownFlag);

// Global table base pointer (from DAT_012234bc)
extern uint8_t* g_pEntryTable;  // Actually a pointer to array of Entry structures

// Structure representing each entry in the table (0x30 bytes)
#pragma pack(push, 1)
struct IdEntry {
    uint8_t pad0[0x10];        // +0x00: unknown
    uint8_t pad10[0x1C];       // +0x10: unknown (size guess)
    uint32_t storedId;         // +0x2C: full 32-bit ID that must match
};
#pragma pack(pop)

// Validates and optionally activates an entry by its full ID.
// Returns true if the ID is recognized and activation succeeded.
bool validateAndActivate(uint32_t fullId) {
    uint16_t slotIndex = static_cast<uint16_t>(fullId & 0xFFFF);
    
    // Bounds check: only 512 slots (0x200)
    if (slotIndex < 0x200) {
        // Calculate pointer to entry's storedId field (offset 0x2C from entry start)
        // The entry start is at g_pEntryTable + slotIndex * sizeof(IdEntry)
        uint8_t* entryPtr = g_pEntryTable + slotIndex * sizeof(IdEntry);
        IdEntry* entry = reinterpret_cast<IdEntry*>(entryPtr);
        
        // Ensure the default stored ID matches the given full ID
        if (entryPtr != nullptr && entry->storedId == fullId) {
            // Activate the entry (FUN_005e5e60) with unknown flag = 0
            if (activateEntry(slotIndex, 0)) {
                return true;
            }
        }
    }
    return false;
}