// FUNC_NAME: ListNode::relinkIntoList
// Function address: 0x005df960
// Purpose: Relinks this node into the list specified by pContainer.
//          The node is removed from its current list and inserted at the front of the new list.
// Parameters:
//   this - node to relink
//   pContainer - pointer to a container object that has a pointer to list head at +0x1c

struct ListNode {
    ListNode* pNext;      // +0x00
    ListNode* pPrev;      // +0x04
    ListNode* pList;      // +0x08  pointer to list head/sentinel
    char bVisible;        // +0x15  flag indicating if node is active
};

struct ListContainer {
    // ...
    ListNode* pHeadNode;  // +0x1c  pointer to sentinel node
};

void __thiscall ListNode::relinkIntoList(ListContainer* pContainer) {
    ListNode* oldNext = this->pNext;   // iVar1
    this->pNext = oldNext->pList;      // *this = oldNext->pList (set this->next to oldNext's list pointer)

    // If the node pointed to by oldNext's pList is not visible, update its prev
    if (oldNext->pList->bVisible == '\0') {
        oldNext->pList->pPrev = this;
    }

    oldNext->pPrev = this->pPrev;      // set oldNext's prev to this's prev

    // Get the head node from container
    ListNode* headNode = pContainer->pHeadNode;  // pContainer->pHeadNode is at pContainer+0x1c

    // Check if this node is the last node (i.e., the prev of head node)
    if (this == headNode->pPrev) {
        headNode->pPrev = oldNext;
        oldNext->pList = this;
        this->pPrev = oldNext;
        return;
    }

    // Otherwise, get the previous node
    ListNode* prevNode = this->pPrev;
    if (this == prevNode->pList) {     // if this node is the first node after head? Actually check if this equals prev's pList
        prevNode->pList = oldNext;
        oldNext->pList = this;
        this->pPrev = oldNext;
        return;
    }

    // Default case
    prevNode->pNext = oldNext;
    oldNext->pList = this;
    this->pPrev = oldNext;
    return;
}