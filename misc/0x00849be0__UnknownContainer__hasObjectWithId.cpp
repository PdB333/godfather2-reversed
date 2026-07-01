// FUNC_NAME: UnknownContainer::hasObjectWithId
bool __thiscall UnknownContainer::hasObjectWithId(int param_1, int param_2) {
    uint index = 0;
    uint foundIndex = 0xffffffff;

    if (*(uint *)(param_1 + 0x14) != 0) { // count of objects
        int **pArray = *(int ***)(param_1 + 0x10); // pointer to array of object pointers
        while (foundIndex = index, *(int *)(*pArray + 0x50) != param_2) { // compare object->id at +0x50
            index++;
            pArray++;
            if (*(uint *)(param_1 + 0x14) <= index) {
                return false;
            }
        }
    }
    return (int)foundIndex >= 0;
}