// FUNC_NAME: SimpleMap::set
// Function address: 0x00442ee0
// This function inserts or updates a key-value pair in a dynamically growing array.
// The container layout (relative to this):
//   +0x18: pointer to base of pair array (each pair: int key, int value = 8 bytes)
//   +0x1c: current number of pairs stored
//   +0x20: allocated capacity (max number of pairs before reallocation)

void __thiscall SimpleMap::set(int this, int key, int value)
{
    uint index = 0;
    if (*(uint *)(this + 0x1c) != 0) {
        int *pairPtr = *(int **)(this + 0x18);
        do {
            if (*pairPtr == key) {
                // Key exists: update value at same index
                (*(int **)(this + 0x18))[index * 2 + 1] = value;
                return;
            }
            index = index + 1;
            pairPtr = pairPtr + 2;
        } while (index < *(uint *)(this + 0x1c));
    }
    // Key not found: insert new pair
    int capacity = *(int *)(this + 0x20);
    if (*(int *)(this + 0x1c) == capacity) {
        // Grow capacity: double (or set to 1 if zero)
        if (capacity == 0) {
            capacity = 1;
        } else {
            capacity = capacity * 2;
        }
        FUN_00443e50(capacity);  // Reallocate array to new capacity
    }
    // Append new pair at the end
    int *newPair = (int *)(*(int *)(this + 0x18) + *(int *)(this + 0x1c) * 8);
    *(int *)(this + 0x1c) = *(int *)(this + 0x1c) + 1;
    *newPair = key;
    newPair[1] = value;
    return;
}