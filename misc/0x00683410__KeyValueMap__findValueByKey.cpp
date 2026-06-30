// FUNC_NAME: KeyValueMap::findValueByKey
// Function address: 0x00683410
// Role: Linear search through a key-value pair array to find the value associated with a given key.
// Returns the value if found, or 0 if not found.

// Structure layout for KeyValueMap (offsets from this):
// +0x00: (vtable pointer? / unknown)
// +0x0C: pointer to array of KeyValuePair (each 8 bytes: key (int), value (int/pointer))
// +0x88: number of entries in the array (uint)
// The array is contiguous; entries are stored as pairs.

struct KeyValuePair {
    int key;      // +0x00
    int value;    // +0x04
};

class KeyValueMap {
public:
    int findValueByKey(int key);  // returns 0 if not found
};

// __thiscall: this is passed in ECX
int KeyValueMap::findValueByKey(int key) {
    int result = 0;                           // default return value (not found)
    uint count = *(uint *)((char *)this + 0x88);  // number of entries

    if (count != 0) {
        // Start of the array: pointer at offset 0x0C
        KeyValuePair *pairs = *(KeyValuePair **)((char *)this + 0x0C);
        for (uint i = 0; i < count; ++i) {
            if (pairs[i].key == key) {
                result = pairs[i].value;
                break;
            }
        }
    }
    return result;
}