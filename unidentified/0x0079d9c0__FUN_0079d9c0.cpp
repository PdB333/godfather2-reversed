// FUNC_NAME: SomeManager::setNode
void __thiscall SomeManager::setNode(int thisPtr, int objPtr)
{
    int **headPtr = (int **)(thisPtr + 0x24ac); // pointer to head of linked list
    int nodePtr;

    if (objPtr == 0) {
        nodePtr = 0;
    } else {
        nodePtr = objPtr + 0x48; // node is at offset 0x48 within the object
    }

    if (*headPtr != nodePtr) {
        if (*headPtr != 0) {
            // Remove previous node from list (likely unlink)
            FUN_004daf90(headPtr);
        }
        *headPtr = nodePtr;
        if (nodePtr != 0) {
            // Save old back pointer (maybe previous node or list head)
            *(int *)(thisPtr + 0x24b0) = *(int *)(nodePtr + 4);
            // Set node's back pointer to point to the head pointer location
            *(int **)(nodePtr + 4) = headPtr;
        }
    }
}