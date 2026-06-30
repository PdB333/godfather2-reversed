// FUNC_NAME: SelectionList::setSelection
void __thiscall SelectionList::setSelection(int thisPtr, int newSelectionPtr)
{
    // Offsets:
    // +0xa4: pointer to current selection node (ListNode*)
    // +0xa8: next pointer for the head node? (ListNode*)
    // +0xb8: pointer to parent selection list (SelectionList*)
    // +0xc0: another pointer, maybe to sibling list (SelectionList*)
    // +0x48: size of ListNode (or offset to node from container)
    // +0x50: size of SelectionList container? (used for parent offset)

    int* curSelPtr = (int*)(thisPtr + 0xa4);
    int newSel;

    // newSelectionPtr is either a pointer to a ListNode container or null.
    // The actual ListNode is at container + 0x48.
    if (newSelectionPtr == 0) {
        newSel = 0;
    } else {
        newSel = newSelectionPtr + 0x48;
    }

    // Remove old selection if different
    if (*curSelPtr != newSel) {
        if (*curSelPtr != 0) {
            removeNode(curSelPtr); // unlink the old node
        }
        *curSelPtr = newSel;
        if (newSel != 0) {
            // Update the linked list: store previous back pointer and set new back pointer
            *(int*)(thisPtr + 0xa8) = *(int*)(newSel + 4); // old next
            *(int**)(newSel + 4) = curSelPtr;              // new node points back to curSelPtr
        }
    }

    // Propagate selection to parent list (at thisPtr+0xc0)
    int parent1 = *(int*)(thisPtr + 0xc0);
    if (parent1 != 0 && parent1 != 0x50) {
        int thisContainer = (*curSelPtr == 0) ? 0 : *curSelPtr - 0x48;
        int parentContainer = (parent1 == 0) ? 0 : parent1 - 0x50;
        if (parentContainer != 0) {
            int* parentSelPtr = (int*)(parentContainer + 0xc0);
            int selToSet = (thisContainer == 0) ? 0 : thisContainer + 0x48;
            if (*parentSelPtr != selToSet) {
                if (*parentSelPtr != 0) {
                    removeNode(parentSelPtr);
                }
                *parentSelPtr = selToSet;
                if (selToSet != 0) {
                    *(int*)(parentContainer + 0xc4) = *(int*)(selToSet + 4);
                    *(int**)(selToSet + 4) = parentSelPtr;
                }
            }
        }
    }

    // Propagate selection to sibling list (at thisPtr+0xb8)
    int parent2 = *(int*)(thisPtr + 0xb8);
    if (parent2 != 0 && parent2 != 0x50) {
        int thisContainer = (*curSelPtr == 0) ? 0 : *curSelPtr - 0x48;
        int parentContainer = (parent2 == 0) ? 0 : parent2 - 0x50;
        if (parentContainer != 0) {
            int* parentSelPtr = (int*)(parentContainer + 0xc0);
            int selToSet = (thisContainer == 0) ? 0 : thisContainer + 0x48;
            if (*parentSelPtr != selToSet) {
                if (*parentSelPtr != 0) {
                    removeNode(parentSelPtr);
                }
                *parentSelPtr = selToSet;
                if (selToSet != 0) {
                    *(int*)(parentContainer + 0xc4) = *(int*)(selToSet + 4);
                    *(int**)(selToSet + 4) = parentSelPtr;
                }
            }
        }
    }
}