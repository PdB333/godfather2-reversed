// FUNC_NAME: validateItemFlagSet
void __fastcall validateItemFlagSet(void* unusedThis, int itemId)
{
    uint index = 0;
    
    // Check if the global item table has entries
    if (g_itemCount != 0) {
        // Search for the item ID in the table (each entry is two ints)
        while (g_itemTable[index * 2] != itemId) {
            index++;
            if (g_itemCount <= index) {
                // Item not found -> assertion failure
                assertionFailure();
                return;
            }
        }
        // If the flag at offset 4 is already set, success
        if (g_itemTable[index * 2 + 1] != 0) {
            return;
        }
    }
    // Either no items, or found item with flag cleared -> assertion failure
    assertionFailure();
    return;
}