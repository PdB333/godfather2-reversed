// FUNC_NAME: SomeManager::updateActiveItems
void __thiscall SomeManager::updateActiveItems(void *thisPtr, int count)
{
    int idx = 0;
    if (count > 0) {
        do {
            // Check if the flag at global offset (g_activeFlagsBase + g_stride * 0x1b + idx) is non-zero
            if (g_activeFlagsBase[g_stride * 0x1b + idx] != 0) {
                // Process the active item
                handleActiveItem();
            }
            idx++;
        } while (idx < count);
    }
}