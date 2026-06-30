// FUNC_NAME: SimManager::updateEntityCategories
void SimManager::updateEntityCategories(undefined4 context) // param_1 likely float deltaTime or some update context
{
    int index;
    uint idx;
    int dataTable;
    int entryValue;
    int numItems;
    int i;

    // First category: offset 0x58 count, indices at 0x59
    i = 0;
    if (*(char*)(this + 0x58) != '\0') {
        do {
            idx = (uint)*(byte*)(this + 0x59 + i);
            dataTable = *(int*)(this + 0x1bc);
            // Check if the entry at the offset 0x18 array is not -2 (sentinel for invalid)
            entryValue = *(int*)(*(int*)(dataTable + 0x18) + idx * 4);
            if (entryValue != -2) {
                // Global callback: possibly debug output or pre-update hook
                (**(code**)(*DAT_01205590 + 4))();
            }
            // Call the update function for this category
            updateCategoryItem1(context);
            i = i + 1;
        } while (i < (int)(uint)*(byte*)(this + 0x58));
    }

    // Second category: offset 0x79 count, indices at 0x7a
    i = 0;
    if (*(char*)(this + 0x79) != '\0') {
        do {
            idx = (uint)*(byte*)(this + 0x7a + i);
            dataTable = *(int*)(this + 0x1bc);
            // Check entry at offset 0x24 array
            entryValue = *(int*)(*(int*)(dataTable + 0x24) + idx * 4);
            if (entryValue != -2) {
                (**(code**)(*DAT_01205590 + 4))();
            }
            // Call a different update function, passing the entity pointer from another array
            updateCategoryItem2(*(undefined4*)(*(int*)(dataTable + 0x20) + idx * 4), context);
            i = i + 1;
        } while (i < (int)(uint)*(byte*)(this + 0x79));
    }

    // Third category: offset 0x9a count, indices at 0x9c
    i = 0;
    if (*(char*)(this + 0x9a) != '\0') {
        do {
            idx = (uint)*(byte*)(this + 0x9c + i);
            dataTable = *(int*)(this + 0x1bc);
            // Check entry at offset 0x30 array
            entryValue = *(int*)(*(int*)(dataTable + 0x30) + idx * 4);
            if (entryValue != -2) {
                (**(code**)(*DAT_01205590 + 4))();
            }
            // Call a virtual function from the entity's vtable at offset +0x0C
            (**(code**)(**(int**)(*(int*)(dataTable + 0x2c) + idx * 4) + 0xC))(context);
            i = i + 1;
        } while (i < (int)(uint)*(byte*)(this + 0x9a));
    }

    // Optional post-update: if pointer at 0x1c0 is non-null, call another update function
    if (*(int*)(this + 0x1c0) != 0) {
        postUpdateCategory(context);
    }
}