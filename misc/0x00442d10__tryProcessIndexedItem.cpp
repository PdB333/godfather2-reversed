// FUNC_NAME: tryProcessIndexedItem

// Function address: 0x00442d10
// Attempts to validate an indexed item and process it if valid.
// Calls internal validation and processing helpers.

void __cdecl tryProcessIndexedItem(int itemIndex)
{
    int result;

    // Validate the item index; returns -1 if invalid, otherwise the validated index.
    result = FUN_00443880(&itemIndex);

    // If validation succeeded (non-negative), process the item.
    if (result >= 0) {
        FUN_00443820();
    }
}