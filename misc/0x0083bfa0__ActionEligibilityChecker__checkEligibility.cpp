// FUNC_NAME: ActionEligibilityChecker::checkEligibility
// Address: 0x0083bfa0
// Role: Checks whether an action can be performed by evaluating internal flags,
// property states, and a chain of handler objects. Returns 1 if allowed, 0 if denied.

#include <cstdint>

// Forward declare the handler interface (assumed pure virtual)
class ActionEligibilityHandler {
public:
    virtual __thiscall bool canPerformAction(uint32_t contextValue, uint32_t param2, int32_t actionParams) = 0; // vtable+0x10
    virtual ~ActionEligibilityHandler() {}
};

class ActionEligibilityChecker {
public:
    // Offsets (relative to this)
    uint32_t m_flags;           // +0xfc – bitmask of active constraints
    uint32_t m_contextValue;    // +0xf8 – passed to handlers as first argument
    // Array of handler structs: each 8 bytes, first 4 bytes = pointer to handler object
    struct HandlerEntry {
        ActionEligibilityHandler* handler; // +0x00
        uint32_t padding;                  // +0x04 (unused?)
    } *m_handlerArray;          // +0x100
    int32_t m_handlerCount;     // +0x128 – number of entries in m_handlerArray

    // Helper: external function to fetch a uint32 property by hash from a short index
    // Returns boolean success, and stores result in outValue if found.
    // (Likely reads from a database or config)
    static bool __fastcall getPropertyByHash(uint16_t index, uint32_t hash, int32_t& outValue);

    // Main method
    uint8_t __thiscall checkEligibility(uint32_t param2, int32_t actionParams);
};

// External function definition (address 0x005fd340)
bool __fastcall ActionEligibilityChecker::getPropertyByHash(uint16_t index, uint32_t hash, int32_t& outValue) {
    // Implementation not provided
    // Returns true if property exists, false otherwise.
    // On success, outValue contains the property data.
    return false;
}

uint8_t ActionEligibilityChecker::checkEligibility(uint32_t param2, int32_t actionParams) {
    // +0x10 in actionParams? Interpretation: actionParams points to a structure; offset 10 is a uint16
    uint16_t actionFlags = *(uint16_t*)(actionParams + 10);

    // Check if a global flag overlaps with action flags
    if (m_flags != 0 && (m_flags & actionFlags) != 0) {
        return 0;
    }

    int32_t propertyValue = 0;
    // Check first named property (hash: 0x5b25c73b) – possibly "isDisabled" or similar
    if (getPropertyByHash(*(uint16_t*)(actionParams + 8), 0x5b25c73b, propertyValue)) {
        // Interpret the property (only first byte matters? The decompiler shows a check for byte at +6)
        uint32_t propBit = 0;
        // The decompiler had a local_4 pointer that never gets set – likely a decompilation artifact.
        // We assume that if property is valid (byte at offset 6 indicates type 0x02?), then the value is read.
        // We simplify: treat propertyValue bit 0 as deny flag.
        if ((propertyValue & 1) != 0) {
            return 0;
        }
    }

    // Check second named property (hash: 0xd1fbb69b)
    if (getPropertyByHash(*(uint16_t*)(actionParams + 8), 0xd1fbb69b, propertyValue)) {
        if ((propertyValue & 1) != 0) {
            return 0;
        }
    }

    // Mark action as allowed initially
    *(uint8_t*)&actionParams = 1;  // set first byte of actionParams to 1

    // Iterate over all handlers in the array
    HandlerEntry* entry = m_handlerArray;
    HandlerEntry* end = entry + m_handlerCount;  // each entry is 8 bytes
    while (entry < end) {
        ActionEligibilityHandler* handler = entry->handler;
        if (!handler->canPerformAction(m_contextValue, param2, actionParams)) {
            // Handler denied the action
            *(uint8_t*)&actionParams = 0;
            break;
        }
        entry++;
    }

    return *(uint8_t*)&actionParams; // returns 1 if all handlers returned true, 0 otherwise
}