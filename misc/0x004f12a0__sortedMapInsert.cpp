// FUNC_NAME: sortedMapInsert
void sortedMapInsert(uint key, uint value)
{
    uint currentCount = g_sortedMapCount;
    uint index = 0;

    if (g_sortedMapCount != 0) {
        // Traverse to find insertion point (sorted order, no duplicates)
        do {
            uint existingKey = *(uint *)(g_sortedMapArray + index * 8);
            if (existingKey == key) {
                break; // Duplicate key; do nothing
            }
            if (key <= existingKey) { // key is smaller (and not equal)
                uint* newSlot = (uint*)allocAndShift(); // Allocate and shift array to insert, returns pointer to new slot
                *newSlot = key;
                newSlot[1] = value;
                break;
            }
            index = index + 1;
        } while (index < g_sortedMapCount);
    }

    // If we traversed all existing entries without inserting (key is largest), append at end
    if (index == currentCount) {
        if (g_sortedMapCount == g_sortedMapCapacity) {
            growSortedMapArray(); // Resize the global array
        }
        uint* newSlot = (uint *)(g_sortedMapArray + g_sortedMapCount * 8);
        g_sortedMapCount = g_sortedMapCount + 1;
        if (newSlot != (uint *)0x0) {
            *newSlot = key;
            newSlot[1] = value;
        }
    }
    return;
}