// FUNC_NAME: ObjectManager::removeFlaggedItems
void ObjectManager::removeFlaggedItems() { // this = param_1
    int count = *(int*)(this + 0x14); // array size
    int** itemsArray = *(int***)(this + 0x10); // pointer to array of pointers

    // Iterate from last to first (for safe removal by swapping with last)
    for (int idx = count - 1; idx >= 0; --idx) {
        int* item = itemsArray[idx];
        // Check if the flag at offset 0x5f bit 0 is set
        if ((*(unsigned char*)(item + 0x5f) & 1) != 0) {
            // Call cleanup/destructor for the item
            FUN_006b3c40(item);
            // Call deletion with flags (param2=1, param3=0, param4=0)
            FUN_008bf280(item, 1, 0, 0);

            // If not the last element, move the last element to this position
            if (idx != count - 1) {
                itemsArray[idx] = itemsArray[count - 1];
            }
            // Decrement the count
            count--;
            // Note: The array pointer remains the same, but count is adjusted.
            // The caller may later reallocate if needed.
        }
    }
    // Update the count in the object
    *(int*)(this + 0x14) = count;
}