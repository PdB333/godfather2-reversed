// FUNC_NAME: ObjectManager::destroyAllObjects
void ObjectManager::destroyAllObjects(void)
{
    uint i;
    int *objectPtr;

    i = 0;
    if (g_objectCount != 0) {
        do {
            objectPtr = *(int **)(g_objectArray + i * 4);
            if (objectPtr != (int *)0x0) {
                if (*objectPtr != 0) {
                    // Call cleanup function at offset +0x0C (objectPtr[3])
                    (*(code *)objectPtr[3])(*objectPtr);
                }
                // Free the object memory
                operatorDelete(objectPtr);
            }
            i = i + 1;
        } while (i < g_objectCount);
    }
    g_objectCount = 0;
    operatorDeleteArray(g_objectArray);
    g_objectArray = 0;
    g_someFlag = 0;
    return;
}