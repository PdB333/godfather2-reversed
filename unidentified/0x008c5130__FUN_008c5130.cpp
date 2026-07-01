// FUNC_NAME: SomeManager::shutdown
void __thiscall SomeManager::shutdown(int this, int managerData)
{
    int someId = *(int *)(managerData + 8); // +0x8: some identifier or parameter
    FUN_006b2ff0(0, 0); // likely debug/logging call

    int count = *(int *)(managerData + 0x14); // +0x14: number of items
    int *itemArray = *(int **)(managerData + 0x10); // +0x10: pointer to array of item IDs/pointers

    // Iterate backwards over items and destroy each
    for (int i = count - 1; i >= 0; i--)
    {
        FUN_008c2e50(itemArray[i], someId); // destroy/release item with given ID
    }

    *(int *)(this + 0x154) = 0; // +0x154: some state flag or pointer

    int activeIndex = FUN_008bdd00(managerData); // get current active index
    if (activeIndex >= 0)
    {
        FUN_008c2160(activeIndex); // remove or deactivate at that index
    }
}