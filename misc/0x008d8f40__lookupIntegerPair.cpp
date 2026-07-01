// FUNC_NAME: lookupIntegerPair
// Address: 0x008d8f40
// Role: Wrapper that retrieves an integer value using two keys. Calls internal lookup function.
// Returns 1 on success, 0 on failure. Output value stored in outValue.

bool lookupIntegerPair(int key1, int key2, int* outValue)
{
    int value = 0;
    if (getIntFromTable(key1, key2, &value)) {
        *outValue = value;
        return true;
    }
    *outValue = 0;
    return false;
}