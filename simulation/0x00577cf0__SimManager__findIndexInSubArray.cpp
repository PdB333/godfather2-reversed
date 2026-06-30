// FUNC_NAME: SimManager::findIndexInSubArray
int SimManager::findIndexInSubArray(int searchValue)
{
    // this+0x70: pointer to a structure containing an array of 8-byte elements
    int* baseStruct = *(int**)((char*)this + 0x70);
    // baseStruct+0x40: pointer to the start of the 8-byte element array
    int* arrayBase = *(int**)((char*)baseStruct + 0x40);
    // this+0x74: short index into the array (selects a specific 8-byte element)
    short subIndex = *(short*)((char*)this + 0x74);
    // Each 8-byte element: first int = count, second int = pointer to sub-array of 0xc-byte structures
    int* element = (int*)((char*)arrayBase + subIndex * 8);
    int count = element[0];
    int* subArray = (int*)element[1]; // pointer to array of 0xc-byte structures
    for (int i = 0; i < count; i++)
    {
        // Each sub-array element: first int is the value to compare
        if (subArray[i * 3] == searchValue)
        {
            return i;
        }
    }
    return -1;
}