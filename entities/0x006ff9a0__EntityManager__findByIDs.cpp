// FUNC_NAME: EntityManager::findByIDs
int __thiscall EntityManager::findByIDs(int thisPtr, int id1, int id2)
{
    // thisPtr+0x10 is pointer to head of linked list node
    int* nodePtr = *(int**)(thisPtr + 0x10);
    int* foundObj = 0;

    if (nodePtr != 0) {
        while (true) {
            foundObj = (int*)*nodePtr; // dereference first field: pointer to object
            if (foundObj != 0 &&
                *(int*)((int)foundObj + 0x50) == id1 &&
                *(int*)((int)foundObj + 0x54) == id2) {
                break; // match found
            }
            nodePtr = (int*)nodePtr[1]; // advance to next node (offset 4)
            if (nodePtr == 0) {
                return 0; // not found
            }
        }
    }
    return (int)foundObj; // return pointer to object (or 0 if list empty)
}