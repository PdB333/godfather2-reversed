// FUNC_NAME: SomeManager::removeByKey
// Address: 0x00569650
// Removes an element from an internal array by matching a key value from another object.
// The array is stored at this+0x20, count at this+0x120.
// The key to match is at param_1+0x110.
// Uses a global critical section (DAT_00e2cbe8) for thread safety.

void __thiscall SomeManager::removeByKey(int param_1)
{
    uint count;
    uint index;
    int *array; // this+0x20
    int key;    // param_1+0x110

    // Lock global mutex
    FUN_00ab4db0(&DAT_00e2cbe8);

    count = *(uint *)(this + 0x120); // number of elements in array
    if (count != 0) {
        index = 0;
        // Search for element matching key from param_1
        while (*(int *)(this + 0x20 + index * 4) != *(int *)(param_1 + 0x110)) {
            index++;
            if (count <= index) {
                // Not found, unlock and return
                FUN_00ab4e70();
                return;
            }
        }
        // Found at index, remove it
        if ((int)index >= 0 && index < count) {
            // If not the last element, move last element to the removed slot
            if (index < count - 1) {
                *(int *)(this + 0x20 + index * 4) = *(int *)(this + 0x1c + count * 4);
            }
            // Decrement count
            *(int *)(this + 0x120) = count - 1;
        }
    }
    // Unlock mutex
    FUN_00ab4e70();
}