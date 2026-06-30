// FUNC_NAME: LinearMap::findPair
// Function at 0x005e9d90: Linear search in a key-value map with two value arrays.
// This appears to be a generic lookup utility likely from a container class.
// The "this" pointer offsets:
//   +0x08: pointer to array of int keys
//   +0x0c: count of entries (uint32)
//   +0x04: pointer to array of primary values (uint32 each)
//   +0x14: pointer to array of secondary structs (12 bytes each), taking field at +0x04
int __thiscall LinearMap::findPair(int this, int key, int* outSecondary)
{
    int result = 0;
    uint32_t index = 0;
    if (*(uint32_t*)(this + 0xc) != 0) {
        int* keyArray = *(int**)(this + 0x8);
        while (*keyArray != key) {
            index++;
            keyArray++;
            if (*(uint32_t*)(this + 0xc) <= index) {
                return result;
            }
        }
        // Found: retrieve primary value from array at +0x04
        result = *(int*)(*(int*)(this + 0x4) + index * 4);
        // Retrieve secondary value from struct array at +0x14, field at +0x04
        *outSecondary = *(int*)(*(int*)(this + 0x14) + 4 + index * 0xc);
    }
    return result;
}