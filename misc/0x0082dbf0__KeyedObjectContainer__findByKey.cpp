// FUNC_NAME: KeyedObjectContainer::findByKey
// Address: 0x0082dbf0
// Searches a linear array of object pointers for an object whose 4-int key matches the given key.
// Returns pointer to the object if found, or nullptr if not found.

int __thiscall KeyedObjectContainer::findByKey(int *key) {
    uint count = *(uint *)(this + 0xc); // number of elements in the array
    if (count != 0) {
        int **array = *(int ***)(this + 0x8); // pointer to array of object pointers
        for (uint i = 0; i < count; i++) {
            int *obj = array[i];
            // Compare the 4-int key at offsets 0x1c, 0x20, 0x24, 0x28
            if (obj[0x1c/4] == key[0] &&
                obj[0x20/4] == key[1] &&
                obj[0x24/4] == key[2] &&
                obj[0x28/4] == key[3]) {
                return (int)obj;
            }
        }
    }
    return 0;
}