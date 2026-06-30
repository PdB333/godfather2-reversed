// FUNC_NAME: lookupUint32Pair
bool lookupUint32Pair(uint32_t key1, uint32_t key2, uint32_t* outValue) {
    uint32_t value = 0;
    // Call internal store lookup; returns non-zero on success
    if (dataStoreLookup(key1, key2, &value)) {
        *outValue = value;
        return true;
    }
    *outValue = 0;
    return false;
}