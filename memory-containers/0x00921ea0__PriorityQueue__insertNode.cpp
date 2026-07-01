// FUNC_NAME: PriorityQueue::insertNode
// Function address: 0x00921ea0
// Role: Inserts a node into a sorted priority queue (ascending order by priority at +0x54)
// The queue is stored as a dynamic array of 8-byte slots (data pointer + next pointer) at this+0x68, count at this+0x6c.
// Each element (param_2) has an embedded node at offset 0x48, with a next pointer at node+0x04.
// Priority at element+0x54 determines insertion order.

void __thiscall PriorityQueue::insertNode(PriorityQueue *this, void *element) {
    uint index;
    Slot *slotPtr;
    int iVar3;
    Node *node;         // local_8
    Node *savedNext;    // local_4

    // Compute node address from element (embedded at +0x48)
    if (element == 0) {
        node = 0;
    } else {
        node = (Node *)((char *)element + 0x48);
    }

    // Save old next pointer and initialize node's next to a dummy (later released)
    savedNext = 0;
    if (node != 0) {
        savedNext = (Node *)*(int *)((char *)node + 4);  // node->next
        *(int *)((char *)node + 4) = (int)&node;          // temporary self-reference (hack or profiler)
    }

    index = 0;
    // Check for duplicate node in queue
    if (*(uint *)(this + 0x6c) != 0) {
        slotPtr = *(Slot **)(this + 0x68);
        do {
            if (slotPtr->data == node) {
                if (index < 0xFFFFFFFF) goto exit;  // duplicate found, skip insertion
                break;
            }
            index++;
            slotPtr++;
        } while (index < *(uint *)(this + 0x6c));
    }

    index = 0;
    // Find insertion index based on priority (sort ascending)
    if (*(uint *)(this + 0x6c) != 0) {
        slotPtr = *(Slot **)(this + 0x68);
        do {
            Node *existingNode;
            if (slotPtr->data == 0) {
                existingNode = 0;
            } else {
                existingNode = (Node *)((char *)slotPtr->data - 0x48);  // adjust back to element
            }
            // Compare priority at element+0x54
            if (*(int *)((char *)element + 0x54) < *(int *)((char *)existingNode + 0x54))
                break;
            index++;
            slotPtr++;
        } while (index < *(uint *)(this + 0x6c));
    }

    // Allocate a slot at the determined index
    slotPtr = (Slot *)allocateSlot(index);  // FUN_00921560
    iVar3 = (int)node;
    if (slotPtr != (Slot *)&node && slotPtr->data != node) {
        // Release any previous data in slot (if any)
        if (slotPtr->data != 0) {
            releaseSlot(slotPtr);  // FUN_004daf90
        }
        // Insert node into slot
        slotPtr->data = (Node *)iVar3;
        if (iVar3 != 0) {
            slotPtr->next = (Node *)*(int *)(iVar3 + 4);  // node's old next becomes slot's next
            *(int *)(iVar3 + 4) = (int)slotPtr;           // node->next points back to slot (intrusive)
        }
    }

exit:
    // Clean up temporary self-reference
    if (node != 0) {
        releaseNode(&node);  // FUN_004daf90(&local_8)  - probably just clears dummy
    }
    return;
}