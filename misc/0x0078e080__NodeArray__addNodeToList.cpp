//FUNC_NAME: NodeArray::addNodeToList
// Function address: 0x0078e080
// Role: Adds a new node to the dynamic array and optionally inserts it into an intrusive linked list
// The list head is at offset 0x48 of the object passed as param_2 (if non-null)
// Node structure: { void* m_pListHead; Node* m_pNext; } (8 bytes)
// Class layout: this+0x50 = m_pNodes array, this+0x54 = m_nodeCount, this+0x58 = m_nodeCapacity

void __thiscall NodeArray::addNodeToList(void* pListOwner) {
    int* pNode;
    int iVar3;

    // Check if we need to grow the array
    iVar3 = *(int*)(this + 0x58); // m_nodeCapacity
    if (*(int*)(this + 0x54) == iVar3) { // m_nodeCount == m_nodeCapacity
        if (iVar3 == 0) {
            iVar3 = 1;
        } else {
            iVar3 = iVar3 * 2;
        }
        growArray(iVar3); // FUN_0078dac0 - reallocate with new capacity
    }

    // Get pointer to the new node at current count
    pNode = (int*)(*(int*)(this + 0x50) + *(int*)(this + 0x54) * 8); // m_pNodes + m_nodeCount * sizeof(Node)
    if (pNode != nullptr) {
        *pNode = 0;          // m_pListHead = nullptr
        *(pNode + 1) = 0;    // m_pNext = nullptr
    }

    // Increment count
    *(int*)(this + 0x54) = *(int*)(this + 0x54) + 1;

    // Determine the list head pointer (offset 0x48 from pListOwner)
    int* pListHead;
    if (pListOwner == nullptr) {
        pListHead = nullptr;
    } else {
        pListHead = (int*)((char*)pListOwner + 0x48);
    }

    // If the node's list head pointer is different, update it and manage linked list
    if (*pNode != (int)pListHead) {
        if (*pNode != 0) {
            destroyNode(pNode); // FUN_004daf90 - cleanup old list head reference
        }
        *pNode = (int)pListHead; // Set node's list head pointer

        if (pListHead != nullptr) {
            // Insert node at head of the list: node->next = listHead->next; listHead->next = node
            *(pNode + 1) = *(int*)((char*)pListHead + 4); // node->next = listHead->next
            *(int**)((char*)pListHead + 4) = pNode;       // listHead->next = node
        }
    }
    return;
}