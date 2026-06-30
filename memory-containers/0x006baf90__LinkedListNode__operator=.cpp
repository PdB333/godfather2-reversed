// FUNC_NAME: LinkedListNode::operator=
int* __thiscall LinkedListNode::operator=(LinkedListNode* this, LinkedListNode* other)
{
    if (this != other) {
        int* prevNode = other->prev; // other->prev is a pointer to the previous node
        if (this->prev != prevNode) {
            if (this->prev != nullptr) {
                // Release the previous node (likely decrement refcount or free)
                FUN_004daf90(this);
            }
            this->prev = prevNode;
            if (prevNode != nullptr) {
                // Insert this node after prevNode in the linked list
                this->next = prevNode->next; // prevNode->next is at offset +4
                prevNode->next = this;       // Update prevNode's next to point to this
            }
        }
    }
    // Copy data fields (offsets +8, +12, +16, +20)
    this->data0 = other->data0;
    this->data1 = other->data1;
    this->data2 = other->data2;
    this->data3 = other->data3;
    return this;
}