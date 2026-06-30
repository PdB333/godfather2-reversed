// FUNC_NAME: Node::insertIntoManagerList
void __thiscall Node::insertIntoManagerList(Manager* manager)
{
    // Node fields:
    // +0x00: next pointer
    // +0x04: prev pointer
    // +0x08: head pointer (points to a list of nodes, like a free list)
    // +0x15: flag byte (if zero, indicates node is available)

    Node* pNode = *(Node**)(this + 8); // get the node pointed by this->head
    *(Node**)(this + 8) = *(Node**)pNode; // this->head = pNode->next (pop pNode from this's list)

    if (*(char*)(pNode + 0x15) == '\0') {
        *(int*)(pNode + 4) = (int)this; // pNode->prev = this if flag is zero
    }

    *(int*)(pNode + 4) = *(int*)(this + 4); // pNode->prev = this->prev

    // Manager field at +0x1c points to a structure with a tail pointer at +0x04
    Node** tailTracker = *(Node***)(manager + 0x1c);
    if (this == tailTracker[1]) { // if this is the tail of the manager's list
        tailTracker[1] = pNode; // update tail
        pNode->next = this; // pNode->next = this
        this->prev = pNode; // this->prev = pNode
        return;
    }

    Node* prevNode = *(Node**)(this + 4); // this->prev
    if (this == prevNode->next) { // if this is the first node after prevNode (i.e., head)
        prevNode->next = pNode; // prevNode->next = pNode
        pNode->next = this; // pNode->next = this
        this->prev = pNode; // this->prev = pNode
        return;
    }

    // General case: this is in the middle of the list
    *(Node**)(prevNode + 8) = pNode; // prevNode->someOtherLink = pNode
    pNode->next = this; // pNode->next = this
    this->prev = pNode; // this->prev = pNode
}