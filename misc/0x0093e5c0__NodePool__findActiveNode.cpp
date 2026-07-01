// FUNC_NAME: NodePool::findActiveNode
// Reconstructed from 0x0093e5c0 - NodePool iterator that finds the next active node, 
// reaping dead nodes (type 0 with unreferenced objects) into the free list.

int* __fastcall NodePool::findActiveNode(NodePool* this) // param_1 = this
{
    int* pNode = *(int**)(this + 0x48); // +0x48: head of active list (linked list of Node)
    int* pNext;
    int  nodeType;
    int  objectPtr;
    uint temp;

    do {
        while (true) {
            if (pNode == nullptr) {
                return nullptr; // No active nodes
            }
            nodeType = pNode[2]; // Node field at offset +8 (type: 0..6)
            if (nodeType == 0) break; // Handle type 0 specially (needs ref count check)
            if (nodeType == 1) return pNode;
            if (nodeType == 2) return pNode;
            if (nodeType == 3) return pNode;
            if (nodeType == 4) return pNode;
            if (nodeType == 5) return pNode;
            if (nodeType == 6) return pNode;
            pNode = (int*)*pNode; // Move to next node (linked list forward)
        }
        // Node type is 0 – check if its object is still alive
        objectPtr = FUN_006b0ee0(pNode[8]); // pNode[8] is some handle/ID -> returns object pointer or 0
        if (objectPtr != 0 && *(int*)(objectPtr + 0xfc) != 0) {
            return pNode; // Object still alive, keep node
        }

        // Node is dead (type 0 with no valid object) – remove from active list
        pNext = (int*)*pNode; // next pointer (offset +0)

        if (pNode == *(int**)(this + 0x78)) { // +0x78: head of another list? (maybe "expired" list)
            // Update timestamp and clear fields
            temp = DAT_01205224 + 0x9c4; // Global timestamp value
            if (*(uint*)(this + 0x7c) < temp) {
                temp = *(uint*)(this + 0x7c);
            }
            *(uint*)(this + 0x7c) = temp;
            pNode[7] = 0; // Node field at +0x1c (maybe flags?)
            *(uint*)(*(int*)(this + 0x78) + 0xc) = *(uint*)(this + 0x7c); // Copy timestamp to head node
            *(short*)(this + 0x60) = 0;
            *(short*)(this + 0x62) = 0;
            *(int*)(this + 0x74) = 0;
            *(int*)(this + 0x70) = 0;
            *(int*)(this + 0x6c) = 0;
            *(int*)(this + 0x68) = 0;
            *(int*)(this + 0x64) = 0;
        } else {
            // Standard unlink from doubly linked list
            if (pNode[1] == 0) { // prev pointer null? means head of list?
                // Update head to next
                *(int*)(this + 0x48) = *pNode;
                if (*pNode != 0) {
                    *(int*)(*pNode + 4) = 0; // next->prev = null
                    goto doneUnlink;
                }
            } else {
                // prev->next = next
                *(int*)pNode[1] = *pNode;
                if (*pNode != 0) {
                    *(int*)(*pNode + 4) = pNode[1];
                }
            }
            // Relink to free list
            pNode[1] = 0; // prev = null
            *pNode = 0; // next = null
            // Free object if type 1,2,5,6 and object pointer valid
            if ((((nodeType == 1 || nodeType == 2) && (objectPtr = pNode[8], objectPtr != 0)) ||
                ((nodeType == 5 && (objectPtr = pNode[8], objectPtr != 0))) ||
                ((nodeType == 6 && (objectPtr = pNode[8], objectPtr != 0)))) {
                FUN_009c8f10(objectPtr); // Some destructor or release call
            }
            // Insert into free list at +0x44
            *pNode = *(int*)(this + 0x44); // next = free list head
            (*(int*)(this + 0x1c))++; // +0x1c: free count? (increment)
            (*(int*)(this + 0x20))--; // +0x20: some count (decrement)
            *(int**)(this + 0x44) = pNode; // free list head = pNode
            (*(int*)(this + 0x50))--; // +0x50: another count
        }

        pNode = pNext; // Continue with next node in outer loop

        // Check if active list is empty and we need to signal something
        if (*(int*)(this + 0x48) == 0 && ((*(byte*)(this + 0x5c) & 1) != 0)) {
            FUN_004086d0(&DAT_012069c4);
            *(ushort*)(this + 0x5c) &= 0xfffe; // Clear bit 0
        }
    } while (true);
}

// Notes:
// - Node structure assumed: [next +0, prev +4, type +8, ... , objectPtr +0x20?], 
//   but object ptr at pNode[8] = offset 0x20 from node base.
// - Offsets in NodePool object:
//   +0x1c, +0x20, +0x44, +0x48, +0x4c, +0x50, +0x5c, +0x60, +0x62, +0x64, +0x68, +0x6c, +0x70, +0x74, +0x78, +0x7c
// - The function iterates through active list, returning first node that is "alive" (type != 0 or type 0 with valid object),
//   and reaps dead nodes into a free list. It also handles a special "head of expired list" case.