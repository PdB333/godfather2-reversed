// FUNC_NAME: SomeCollection::removeByKey

void __thiscall SomeCollection::removeByKey(int this, int key)
{
    uint index;
    int *items;

    index = 0;
    // +0x34: count of items in collection
    if (*(uint *)(this + 0x34) != 0) {
        // +0x30: pointer to array of items (int*)
        items = *(int **)(this + 0x30);
        do {
            if (*items == key) {
                // If index is negative, return early (shouldn't happen as index is unsigned)
                if ((int)index < 0) {
                    return;
                }
                // Call the removal helper at 0x006ea530
                FUN_006ea530();
                return;
            }
            index = index + 1;
            items = items + 1;
        } while (index < *(uint *)(this + 0x34));
    }
    return;
}