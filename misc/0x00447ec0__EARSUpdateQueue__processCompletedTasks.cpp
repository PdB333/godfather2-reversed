// FUNC_NAME: EARSUpdateQueue::processCompletedTasks
void EARSUpdateQueue::processCompletedTasks(void *this_ptr)
{
    Node *currentNode;
    SubItem *subItem;
    Node *nodeIter;
    int *subObject;
    int *subClass;
    int nodePrev;
    int nodeNext;
    byte local_4;
    int local_c;
    int *local_8;

    nodeIter = *(Node **)((int)this_ptr + 0x60); // +0x60: head of active node list
    do {
        do {
            currentNode = nodeIter;
            if (currentNode == (Node *)nullptr) {
                return;
            }
            subItem = (SubItem *)currentNode->subListHead; // +0xC (offset 3)
            nodeIter = currentNode->next; // +0x0
            while (subItem != (SubItem *)nullptr) {
                // Check bit 30 of flags: if set, skip this item? (maybe marked for removal)
                if (((uint)subItem->flags >> 0x1e & 1) == 0) {
                    // Bit 27 indicates a special sub-object
                    if ((subItem->flags & 0x8000000) == 0) {
                        // Normal callback: call first vtable function with arg 1
                        (subItem->vtable->function0)(1);
                        // Reset subItem to head of list (list may have changed)
                        subItem = (SubItem *)currentNode->subListHead;
                    }
                    else {
                        // Item has a nested sub-object (offset +0x3C = subObject)
                        subObject = (int *)(subItem + 0xf); // +0x3C
                        // Check byte at offset +0x40 for bit 2
                        if ((*(byte *)(subItem + 0x10) & 2) != 0) { // +0x40
                            local_4 = 0;
                            local_c = DAT_012067dc;         // global timer or context
                            local_8 = subObject;
                            // Call second function on subObject with struct
                            (*(code **)(*subObject + 4))(&local_c);
                        }
                        // Call first function on subObject with arg 1
                        (*(code **)*subObject)(1);
                        // Reset to head
                        subItem = (SubItem *)currentNode->subListHead;
                    }
                }
                else {
                    // Bit 30 set: advance to next subitem (skip)
                    subItem = subItem->nextSibling; // +0x8 (offset 2)
                }
            }
        } while ((currentNode->subListHead != 0) || (currentNode->subListTail != 0)); // +0xC, +0x10
        // Node's sublists empty: remove node from doubly linked list
        if ((int *)currentNode->prev == (int *)nullptr) {
            nodeNext = currentNode->next;
            *(int *)((int)this_ptr + 0x60) = nodeNext;
            if (nodeNext != 0) {
                *(int *)(nodeNext + 4) = 0;
                goto LAB_00447f76;
            }
LAB_00447f84:
            nodePrev = currentNode->prev;
            *(int *)((int)this_ptr + 100) = nodePrev; // +0x64? actually 0x64 = 100
            if (nodePrev != 0) {
                *(int *)nodePrev = 0;
            }
        }
        else {
            *(int *)currentNode->prev = currentNode->next;
LAB_00447f76:
            if (currentNode->next == 0) goto LAB_00447f84;
            *(int *)(currentNode->next + 4) = currentNode->prev;
        }
        currentNode->prev = 0;
        currentNode->next = 0;
        FUN_00448630(); // free or return node to pool
    } while (true);
}