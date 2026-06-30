// FUNC_NAME: getEnumMappingValue
// Address: 0x0066cf40
// Role: Looks up a static mapping table of 3 entries (key-value pairs). Returns the value for a given key, or 1 if not found.

typedef int KeyType;
typedef int ValueType;

struct KeyValuePair {
    KeyType key;
    ValueType value;
};

// Static global table at 0x00e2747c (three pairs)
static const KeyValuePair s_enumMappingTable[3] = {
    // Entries as defined in the binary
    // Values are unknown, but the table is used to map integer keys to integer values
};

ValueType __fastcall getEnumMappingValue(KeyType key)
{
    for (int i = 0; i < 3; ++i) {
        if (key == s_enumMappingTable[i].key) {
            return s_enumMappingTable[i].value;
        }
    }
    return 1; // default value when key not found
}