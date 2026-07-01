// FUNC_NAME: ActionValidator::validate
// Reconstructed C++ for function at 0x0083be80
// This function validates an action against a chain of filters and two hash-based block checks.
// The chain is stored as an array of (vtable pointer+0x14 function, data) pairs at this+0x100 (count at this+0x128).

#include <cstdint>

// Forward declaration of the hash lookup function (defined elsewhere)
bool lookUpHashEntry(uint16_t key, uint32_t hash, void** outData, uint32_t* outValue);

bool ActionValidator::validate(uint32_t context, ActionDescriptor* action) {
    // Check if the action's flags are blocked by a bitmask stored at this+0xFC
    if (*(uint32_t*)(this + 0xFC) != 0) {
        uint16_t actionFlags = *(uint16_t*)(action + 0x0A);
        if ((*(uint32_t*)(this + 0xFC) & actionFlags) != 0) {
            return false;
        }
    }

    void* resultData = nullptr;
    uint32_t resultValue = 0;

    // First hash lookup: check if action ID (at action+0x08) is blocked with hash 0x5b25c73b
    if (lookUpHashEntry(*(uint16_t*)(action + 0x08), 0x5b25c73b, &resultData, &resultValue)) {
        if (resultData != nullptr && resultValue != 0) {
            uint8_t typeField = *(uint8_t*)(resultValue + 0x06);
            if (typeField == 0x02 && (resultValue & 1) != 0) {
                return false;
            }
        }
    }

    // Second hash lookup with different hash 0xd1fbb69b
    if (lookUpHashEntry(*(uint16_t*)(action + 0x08), 0xd1fbb69b, &resultData, &resultValue)) {
        if (resultData != nullptr && resultValue != 0) {
            uint8_t typeField = *(uint8_t*)(resultValue + 0x06);
            if (typeField == 0x02 && (resultValue & 1) != 0) {
                return false;
            }
        }
    }

    // Run through filter chain at this+0x100
    FilterPair* filterArray = (FilterPair*)(this + 0x100);
    int32_t filterCount = *(int32_t*)(this + 0x128);

    // Assume action is allowed by default
    bool allowed = true;

    for (int32_t i = 0; i < filterCount; i++) {
        FilterPair* currentFilter = &filterArray[i];
        // Each filter pair: first is pointer to an object with a vtable; offset 0x14 is the validation function.
        // The validation function is called with (this+0xf8, context, action).
        bool (*filterFunc)(uint32_t, uint32_t, ActionDescriptor*) = 
            (bool (*)(uint32_t, uint32_t, ActionDescriptor*))(currentFilter->vtablePtr + 0x14);
        
        if (!filterFunc(*(uint32_t*)(this + 0xF8), context, action)) {
            allowed = false;
            break;
        }
    }

    return allowed;
}