// FUNC_NAME: Container::FindByID

#include <cstdint>

// Helper struct for items in the container (0x34 bytes each)
struct ContainerItem {
    uint32_t padding1[2];  // +0x00
    int32_t  id;           // +0x08 – the field compared against search value
    // … remaining 0x2C bytes
};

// Container structure (object at param_1)
struct Container {
    ContainerItem* items;  // +0x04 – pointer to array of entries
    uint32_t       count;  // +0x08 – number of entries
};

// __fastcall: ECX = this (Container*), EDX = id to find?
// EAX is used as output index pointer (uint16_t* outIndex)
// Returns true if found, false otherwise.
bool __fastcall Container::FindByID(Container* this, int32_t id, uint16_t* outIndex) {
    uint32_t numEntries = this->count;
    *outIndex = 0;                            // start index at 0

    if (numEntries != 0) {
        ContainerItem* itemArray = this->items;
        do {
            if (itemArray[*outIndex].id == id) {
                return true;                  // found
            }
            (*outIndex)++;                     // advance to next index
        } while (*outIndex < numEntries);     // loop while index valid
    }
    return false;
}