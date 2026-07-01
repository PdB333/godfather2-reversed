// FUNC_NAME: EA::LinkedList::removeAllNodes
// Address: 0x00788000
// Removes all nodes from a doubly linked list by unlinking a single node and resetting the list head.
// The list is circular and uses a dummy head node (sentinel). 
// This function appears to take a node and the list head, and clears the list entirely.
// Node layout: 
//   +0x00: prev (pointer)
//   +0x04: next (pointer)
//   +0x08: unknown (possibly a pointer to list data or a second link)
// List head layout:
//   +0x00: first (pointer to first node, or head itself if empty)
//   +0x04: last  (pointer to last node, or head itself if empty)

void __thiscall EA::LinkedList::removeAllNodes(void* pNode, void** pHead) {
    // pHead[0] is 'first', pHead[1] is 'last'
    int* first = (int*)*pHead;               // first node pointer
    if (first == (int*)pHead) return;        // empty list

    // Compute pointers into node fields
    int* nodeNext = *(int**)((char*)pNode + 8); // node->next ?
    int iVar3 = nodeNext ? (int)nodeNext - 4 : 0; // &nodeNext->prev ?

    int iVar4 = first ? (int)first - 4 : 0;      // &first->prev ?

    int* last = (int*)pHead[1];                  // last node pointer
    int iVar5 = last ? (int)last - 4 : 0;        // &last->prev ?

    int iVar2 = iVar4 ? iVar4 + 4 : 0;           // address of first node itself

    // Relink (this appears to move the first node after pNode)
    *(int*)(iVar3 + 4) = iVar2;                  // nodeNext->next = first
    *(int*)(iVar4 + 8) = iVar3 + 4;              // first->prev = &nodeNext->next
    *(int*)(iVar5 + 4) = (int)pNode + 4;         // last->next = &pNode->next (??)
    *(int**)((char*)pNode + 8) = (int*)(iVar5 + 4); // pNode->next = &last->next

    // Clear the list (head now points to itself)
    pHead[0] = (int)pHead;
    pHead[1] = (int)pHead;
}