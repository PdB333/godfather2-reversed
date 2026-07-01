// FUNC_NAME: SomeContainer::findMatchingElement (index search)
// Address: 0x00815c30
// Role: Searches a container for an element matching the given parameters.
// The container has a count stored at offset +0x04.
// For each index, it calls a compare function (FUN_00815560) which takes the search params.
// Returns the index of the first match, or -1 (0xFFFFFFFF) if not found.

#include <cstdint>

// Forward declaration of the comparison function used by this method.
// It is declared as __cdecl (default) because the calling convention is unknown from this snippet.
extern "C" char __cdecl compareElement(uint32_t param2, uint32_t param3);

class SomeContainer {
public:
    // Searches for an element matching param2 and param3.
    // Returns index if found, or 0xFFFFFFFF if not.
    uint32_t __thiscall findMatchingElement(uint32_t param2, uint32_t param3) {
        uint32_t count = *(uint32_t*)((uint8_t*)this + 0x04);
        uint32_t currentIndex = 0;
        uint32_t savedIndex = 0xFFFFFFFF; // default return value if not found

        if (count != 0) {
            do {
                savedIndex = currentIndex;
                // Compare function returns non-zero on match, zero on no match? 
                // Actually loop continues while compare returns 0 (false), 
                // so non-zero means match found.
                if (compareElement(param2, param3) != 0) {
                    // Match found at savedIndex
                    return savedIndex;
                }
                currentIndex = savedIndex + 1;
            } while (currentIndex < count);
        }
        return 0xFFFFFFFF; // not found
    }
};