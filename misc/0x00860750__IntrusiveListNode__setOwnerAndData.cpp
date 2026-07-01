// FUNC_NAME: IntrusiveListNode::setOwnerAndData
void __thiscall IntrusiveListNode::setOwnerAndData(int *owner, int data)
{
    // this->owner == owner (offset +0x00)
    if (this->owner == owner) {
        // Already belongs to this owner; just update the stored data (+0x08)
        this->data = data;
        return;
    }

    // Remove from previous owner's list if currently owned
    if (this->owner != 0) {
        IntrusiveListNode::removeFromList(this);
    }

    // Assign new owner
    this->owner = owner;

    // Insert at head of the owner's linked list
    if (owner != 0) {
        // owner[1] is the pointer to the first node (head->firstNode, offset +0x04)
        this->next = *(int**)(owner + 1);
        *(int**)(owner + 1) = this;
        this->data = data;
        return;
    }

    this->data = data;
    return;
}