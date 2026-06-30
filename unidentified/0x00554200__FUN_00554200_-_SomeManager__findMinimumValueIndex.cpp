// FUNC_NAME: FUN_00554200 - SomeManager::findMinimumValueIndex
// Address: 0x00554200
// This function iterates over an array of items (count at offset 0x68 from this),
// calls FUN_005540a0 to get a float value for each item, and returns the index
// of the item with the smallest value. Returns -1 if no items.

int __thiscall SomeManager::findMinimumScoreIndex(void)
{
    int count = *(int *)((int)this + 0x68); // +0x68: number of items in array
    int bestIdx = -1;
    float bestValue = DAT_00e2b334; // global float constant (likely FLT_MAX)
    float currentValue;

    for (int i = 0; i < count; i++)
    {
        // Get value for this item; the function likely uses i or some internal state
        currentValue = FUN_005540a0(); // returns float score for current item
        if (currentValue < bestValue)
        {
            bestValue = currentValue;
            bestIdx = i;
        }
    }
    return bestIdx;
}