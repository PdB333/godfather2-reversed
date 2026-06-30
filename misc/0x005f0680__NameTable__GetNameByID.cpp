// FUNC_NAME: NameTable::GetNameByID
// Function address: 0x005f0680
// Role: Resolves a numeric hash/ID to a name string from an internal name table.
// Accesses a container obtained via GetNameTableContainer, then iterates over name table entries.
// Each entry is 0x30 bytes; the first 4 bytes are a hash (ID), the remaining bytes are the name string.

#include <cstdint>

// Forward declarations of helper functions
extern int GetNameTableContainer(uint32_t context, uint32_t* id, void** outContainer);
extern uint32_t HashString(const char* str); // Computes the hash/ID for a name string

char* __cdecl NameTable::GetNameByID(uint32_t context, uint32_t targetID) {
    void* container = nullptr;
    int containerValid = 0;
    int containerPtr = GetNameTableContainer(context, &targetID, &container);
    
    if ((container != nullptr) && (containerPtr != 0)) {
        int* nameTableBase = *(int**)((uint8_t*)container + 0x0C); // +0x0C: pointer to name table data
        if (nameTableBase != nullptr) {
            if (*(int*)((uint8_t*)nameTableBase + 0x40) == 0) { // +0x40: flag indicating no tables
                return "<no nametables found>";
            }
            uint32_t entryCount = *(uint32_t*)((uint8_t*)nameTableBase + 0x38); // +0x38: number of entries
            char* entryPtr = (char*)(*(int*)((uint8_t*)nameTableBase + 0x40) + (uint8_t*)nameTableBase); // +0x40: offset to first entry
            
            for (uint32_t i = 0; i < entryCount; i++) {
                if (HashString(entryPtr) == targetID) {
                    return entryPtr; // Return pointer to the name string
                }
                entryPtr += 0x30; // Each entry is 0x30 bytes
            }
        }
    }
    return "<name not found>";
}