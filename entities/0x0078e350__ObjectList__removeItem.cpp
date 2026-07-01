// FUNC_NAME: ObjectList::removeItem
void __thiscall ObjectList::removeItem(int thisPtr, int item)
{
    // Check if item matches current item pointer at +0x1c
    if (item == *(int *)(thisPtr + 0x1c)) {
        *(int *)(thisPtr + 0x1c) = 0; // Clear current item
    }

    uint count = *(uint *)(thisPtr + 0x14);
    if (count != 0) {
        int *items = *(int **)(thisPtr + 0x10); // +0x10 array of int pointers
        for (uint i = 0; i < count; i++) {
            if (items[i] == item) {
                // Remove item at index i (helper function at 0x78e190)
                removeItemAtIndex(i);
                return;
            }
        }
    }
    // Item not found – nothing to remove
}