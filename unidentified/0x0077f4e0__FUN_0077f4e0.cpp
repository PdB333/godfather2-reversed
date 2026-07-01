// FUNC_NAME: SomeClass::setNextNode
void __thiscall SomeClass::setNextNode(int thisPtr, int* newNext)
{
    int** nextPtr = (int**)(thisPtr + 0x64); // offset 0x64: pointer to next node
    int* adjustedNewNext;

    if (newNext == 0) {
        adjustedNewNext = 0;
    } else {
        adjustedNewNext = (int*)((char*)newNext + 0x48); // offset 0x48: node's next pointer within the object
    }

    if (*nextPtr != adjustedNewNext) {
        if (*nextPtr != 0) {
            FUN_004daf90(nextPtr); // remove old next from list
        }
        *nextPtr = adjustedNewNext;
        if (adjustedNewNext != 0) {
            *(int**)(thisPtr + 0x68) = *(int**)((char*)adjustedNewNext + 4); // offset 0x68: prev pointer? Actually stores the back pointer
            *(int**)((char*)adjustedNewNext + 4) = nextPtr; // update the new node's back pointer to point to this node's next pointer
        }
    }
}