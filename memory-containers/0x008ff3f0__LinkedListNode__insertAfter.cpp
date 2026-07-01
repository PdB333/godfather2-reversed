// FUNC_NAME: LinkedListNode::insertAfter
void __thiscall LinkedListNode::insertAfter(int this, int newNode) // 0x008ff3f0
{
    int *nextPtr; // pointer to 'next' field at this+0x1c
    int iVar2;
    int sentinel; // maybe 0x48? sentinel value or null (0)

    nextPtr = (int *)(this + 0x1c); // +0x1c: 'next' pointer

    // If the current next is non-null and not some sentinel (0x48?),
    // and some condition from FUN_008fdfd0 (maybe isInList?) returns nonzero
    if (((*nextPtr != 0) && (*nextPtr != 0x48)) &&
       (iVar2 = FUN_008fdfd0(), iVar2 != 0)) {
        FUN_008fdfd0(0); // maybe setIsInList(false)?
        FUN_00791a70(0); // maybe notifyListChanged?
    }

    // If the current next is non-null and not sentinel, do something
    if ((*nextPtr != 0) && (*nextPtr != 0x48)) {
        FUN_008febe0(0); // maybe detachFromNext? with arg 0
    }

    // Convert newNode: if zero, keep zero; else add offset 0x48 
    // (could be offsetof(listNode, prev) or something)
    if (newNode == 0) {
        newNode = 0;
    } else {
        newNode = newNode + 0x48; // adjust newNode pointer by 0x48
    }

    // If the new next is different from current next
    if (*nextPtr != newNode) {
        // If there's a current next, unlink it
        if (*nextPtr != 0) {
            FUN_004daf90(nextPtr); // probably unlink from the list
        }
        *nextPtr = newNode; // set new next pointer
        if (newNode != 0) {
            *(int *)(this + 0x20) = *(int *)(newNode + 4); // copy prev? or some back pointer
            *(int **)(newNode + 4) = nextPtr; // set back pointer to this's next field
        }
    }

    // If the next is non-null and not sentinel, do something else
    if ((*nextPtr != 0) && (*nextPtr != 0x48)) {
        FUN_008febe0(1); // maybe attachNext? with arg 1
        iVar2 = FUN_008fdfd0(); // re-check condition
        if (iVar2 != 0) {
            if (*nextPtr != 0) {
                FUN_008fdfd0(); // another call with no argument
                FUN_00791a70();
                return;
            }
            FUN_008fdfd0();
            FUN_00791a70();
            return;
        }
    }
    return;
}