// FUNC_NAME: DataManager::LookupPair

#include <cstdint>

// 0x006ccde0
// Attempts to retrieve a value associated with two keys (key1, key2).
// Returns 1 on success (true) with the value stored via outValue.
// Returns 0 on failure and sets outValue to 0.
// Calls internal function FUN_004480d0 for the actual lookup.
uint32_t DataManager::LookupPair(uint32_t key1, uint32_t key2, uint32_t* outValue)
{
    uint32_t tempValue = 0;
    bool found = FUN_004480d0(key1, key2, &tempValue); // 0x004480d0: internal two-key lookup
    if (found) {
        *outValue = tempValue;
        return 1;
    }
    *outValue = 0;
    return 0;
}