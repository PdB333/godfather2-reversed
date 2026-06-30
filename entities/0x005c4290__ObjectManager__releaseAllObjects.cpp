// FUNC_NAME: ObjectManager::releaseAllObjects
void ObjectManager::releaseAllObjects(void)
{
    int objectCount;
    int objectIndex;
    int *objectArray;
    int *currentObject;
    int nextObject;
    
    objectIndex = 0;
    if (0 < DAT_01222068) { // g_objectCount
        objectArray = (int *)DAT_0122206c; // g_objectArray (array of ObjectManagerEntry, 0x20 bytes each)
        do {
            currentObject = (int *)((int)objectArray + objectIndex * 0x20); // +0x00: object pointer
            nextObject = *(int *)((int)objectArray + objectIndex * 0x20 + 0x1c); // +0x1c: first child object
            while (nextObject != 0) {
                nextObject = currentObject[7]; // +0x1c: next child in linked list
                currentObject[7] = *(int *)(nextObject + 4); // +0x04: next pointer in child list
                (**(code **)(*currentObject + 8))(nextObject); // vtable+8: release/destructor
                nextObject = currentObject[7];
            }
            objectIndex = objectIndex + 1;
            currentObject[3] = 0; // +0x0c: some flag
            currentObject[4] = 0; // +0x10: some flag
            currentObject[6] = 0; // +0x18: some flag
        } while (objectIndex < DAT_01222068);
    }
    DAT_01222068 = 0; // g_objectCount = 0
    return;
}