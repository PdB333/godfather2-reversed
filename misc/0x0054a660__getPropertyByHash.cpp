// FUNC_NAME: getPropertyByHash
// Function address: 0x0054a660
// Role: Retrieves a property value (at offset +0x14) from an object identified by a 32-bit hash.
// Calls FUN_004b9ca0 which is likely a hash-based property lookup function.

#include <cstdint>

// Forward declaration: FUN_004b9ca0 - looks up a property by hash on an object, returns pointer to a struct or null.
void* FUN_004b9ca0(void* object, uint32_t propertyHash);

// Returns a 32-bit value from the property structure. Returns 0 if not found.
uint32_t getPropertyByHash(void* object) {
    void* propertyData = FUN_004b9ca0(object, 0x33a16735);  // hash for some property (e.g., "maxHealth")
    if (propertyData != nullptr) {
        // +0x14: field containing the property value (float or int)
        return *reinterpret_cast<uint32_t*>(static_cast<char*>(propertyData) + 0x14);
    }
    return 0;
}