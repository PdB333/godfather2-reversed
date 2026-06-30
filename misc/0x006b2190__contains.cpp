// FUNC_NAME: contains
bool __thiscall EntityManager::contains(int thisPtr, int item)
{
    uint index = 0;
    uint foundIndex = 0xffffffff;

    // Check if the array has any elements (count at +0xac)
    if (*(uint *)(thisPtr + 0xac) != 0)
    {
        // Pointer to the array of items at +0xa8
        int *array = *(int **)(thisPtr + 0xa8);
        while (foundIndex = index, *array != item)
        {
            index++;
            array++;
            // If we've reached the end without finding, return false
            if (*(uint *)(thisPtr + 0xac) <= index)
            {
                return false;
            }
        }
    }
    // Return true if foundIndex is not -1 (i.e., item was found)
    return (int)foundIndex >= 0;
}