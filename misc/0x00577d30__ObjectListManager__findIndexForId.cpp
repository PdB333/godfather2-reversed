// FUNC_NAME: ObjectListManager::findIndexForId
int ObjectListManager::findIndexForId(void)
{
    int id = FUN_004dafd0(); // get target id (unknown source)
    int arrayTable = *(int *)(this + 0x70); // +0x70: pointer to array table (e.g., mArrayTable)
    int arrayBase = *(int *)(arrayTable + 0x40); // +0x40: start of array pointers array
    short arrayIndex = *(short *)(this + 0x74); // +0x74: which sub-array to search (index)

    // Each sub-array descriptor is 8 bytes: count (int) + pointer to actual array (int)
    int count = *(int *)(arrayBase + arrayIndex * 8); // number of elements in sub-array
    int* elementArray = *(int **)(arrayBase + arrayIndex * 8 + 4); // pointer to array of 12-byte structures

    if (count != 0 && elementArray != 0) {
        for (int i = 0; i < count; i++) {
            if (elementArray[0] == id) { // first field of 12-byte structure is the id
                return i;
            }
            elementArray += 3; // each element is 3 ints (12 bytes)
        }
    }
    return -1;
}