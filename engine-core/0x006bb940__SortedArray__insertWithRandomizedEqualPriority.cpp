// FUNC_NAME: SortedArray::insertWithRandomizedEqualPriority
void __thiscall SortedArray::insertWithRandomizedEqualPriority(int this, int item)
{
    uint count = *(uint *)(this + 0x60); // +0x60: number of elements
    uint i = 0;
    
    // First pass: check if item is already present by pointer equality
    if (count != 0) {
        int **items = *(int ***)(this + 0x5c); // +0x5c: pointer to array of pointers
        do {
            if (items[i] == (int *)item) {
                if ((int)i >= 0) {
                    return; // item already in list, do nothing
                }
                break;
            }
            i++;
        } while (i < count);
    }
    
    uint firstEqualIndex = 0xffffffff; // sentinel for no equal found
    uint j = 0;
    uint insertIndex = count; // default insert at end
    if (count != 0) {
        int **items = *(int ***)(this + 0x5c);
        do {
            // Compare keys at +0x5c of items and new item
            if (*(uint *)(item + 0x5c) == *(uint *)(items[j] + 0x5c)) {
                if (firstEqualIndex == 0xffffffff) {
                    firstEqualIndex = j;
                }
            } else {
                insertIndex = j;
                if (*(uint *)(item + 0x5c) < *(uint *)(items[j] + 0x5c)) break;
            }
            j++;
        } while (j < count);
        // If equal group found, randomize insertion among that group
        if (firstEqualIndex != 0xffffffff) {
            // Compute random offset within equal group range [firstEqualIndex, insertIndex-1]
            int rangeSize = (insertIndex - firstEqualIndex) + 1;
            uint randBits = *(uint *)0x010c2678 & *(uint *)0x012054b4; // global random state
            *(uint *)0x012054b4 = *(uint *)0x012054b4 + 1; // advance RNG
            float randFloat = *(float *)(&DAT_010c2680 + randBits * 4); // global random float array
            int randomOffset = (int)ROUND(randFloat * (float)rangeSize);
            int finalIndex = firstEqualIndex + randomOffset;
            *(int **)FUN_006bb370(finalIndex) = (int *)item;
            return;
        }
    }
    // No equal found: insert at sorted position
    *(int **)FUN_006bb370(insertIndex) = (int *)item;
}