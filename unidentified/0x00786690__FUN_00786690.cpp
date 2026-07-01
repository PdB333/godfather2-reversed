// FUNC_NAME: SomeManager::findObjectByID
int __thiscall SomeManager::findObjectByID(int this, int objectID)
{
    int objectPtr;
    int *ptrArray;
    uint index;

    index = 0;
    objectPtr = 0;
    if (*(uint *)(this + 0x2c80) != 0) {
        ptrArray = *(int **)(this + 0x2c7c);
        while (objectPtr = *ptrArray, *(int *)(objectPtr + 0x84) != objectID) {
            index = index + 1;
            ptrArray = ptrArray + 1;
            if (*(uint *)(this + 0x2c80) <= index) {
                return 0;
            }
        }
    }
    return objectPtr;
}