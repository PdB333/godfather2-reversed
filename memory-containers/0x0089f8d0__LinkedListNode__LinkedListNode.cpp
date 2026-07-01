// FUNC_NAME: LinkedListNode::LinkedListNode
// Function address: 0x0089f8d0
// Role: Constructor for a doubly linked list node (circular sentinel). Sets both prev and next pointers to itself.

void __fastcall LinkedListNode::LinkedListNode(int this)
{
    LinkedListNode::constructor(this);
    *(int *)this = this;         // +0x00: next = this
    *(int *)(this + 4) = this;   // +0x04: prev = this
    return;
}