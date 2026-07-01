// FUNC_NAME: ObjectManager::findByID
// Address: 0x008c1250
// Searches an array of pointers (at this+0x1a4) of length (this+0x1a8) for an object whose internal ID field (at offset +0x8) matches param_2.
// Returns the pointer to the matching object, or NULL if not found.
int __thiscall ObjectManager::findByID(int this, int id)
{
    uint index = 0;
    // +0x1a8: count of elements in the array
    if (*(uint *)(this + 0x1a8) != 0) {
        // +0x1a4: pointer to array of object pointers
        int *array = *(int **)(this + 0x1a4);
        do {
            // Each object pointer -> object; compare field at offset +0x8 (likely a type/ID field)
            if (*(int *)(*array + 8) == id) {
                // Guard against potential overflow (though index is unsigned, so this check is likely a leftover)
                if ((int)index < 0) {
                    return 0;
                }
                // Return the pointer at the found index from the original array
                return (*(int **)(this + 0x1a4))[index];
            }
            index = index + 1;
            array = array + 1; // advance to next pointer in the array
        } while (index < *(uint *)(this + 0x1a8));
    }
    return 0;
}