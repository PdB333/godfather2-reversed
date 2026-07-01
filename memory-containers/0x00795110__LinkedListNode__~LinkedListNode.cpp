// FUNC_NAME: LinkedListNode::~LinkedListNode
// Address: 0x00795110
// Role: Destructor for a doubly-linked list node. Unlinks the node from its list,
// calls the base class destructor, and conditionally deallocates memory.

int __thiscall LinkedListNode::~LinkedListNode(byte deleteMemory)
{
    // Set vtable to base class vtable to prevent virtual calls during destruction
    *(void***)(this + 0x28) = &PTR_LAB_00e317cc;  // Base vtable

    // Node structure offsets used for list manipulation:
    // +0x18: pointer to previous node (ListNode*)
    // +0x1c: pointer to next node (ListNode*)
    // +0x20: pointer to the node's stored value (void*)
    // The list nodes themselves are assumed to have layout:
    // +0: vtable pointer? (unused here)
    // +4: next pointer
    // +8: prev pointer

    ListNode* prev = *(ListNode**)(this + 0x18);
    ListNode* next = *(ListNode**)(this + 0x1c);
    void* value = *(void**)(this + 0x20);

    if (prev != nullptr)
    {
        if (next == nullptr)
        {
            // This node is the last in the list: update prev's next to point to value
            *(void**)(prev + 4) = value;
        }
        else
        {
            // This node is in the middle: update next's prev to point to value
            *(void**)(next + 8) = value;
        }
    }

    if (value != nullptr)
    {
        // Update value's "next" pointer (offset +4) to point to the node that was after this one
        *(void**)(value + 4) = next;
    }

    // Call base class destructor (likely Node::~Node or ReferencedObject::~ReferencedObject)
    FUN_0064d150();

    // If the deleteMemory flag has bit 0 set, deallocate the memory for this node
    if ((deleteMemory & 1) != 0)
    {
        FUN_009c8eb0(this);
    }

    return (int)this;
}