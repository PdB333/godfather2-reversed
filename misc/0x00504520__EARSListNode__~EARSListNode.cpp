// FUNC_NAME: EARSListNode::~EARSListNode
// Address: 0x00504520
// Destructor that unlinks the node from a doubly linked list (offsets +0x10 next, +0x14 prev)
// and optionally frees memory via operator delete when freeMemoryFlag bit 0 is set.

void __thiscall EARSListNode::~EARSListNode(uint8_t freeMemoryFlag)
{
    // Switch vtable to intermediate destructor vtable
    this->__vtable = &PTR_FUN_00e37f48;

    // If this node has a next pointer, remove it from the doubly linked list
    if (this->next != nullptr)
    {
        // prev->next = next
        this->prev->next = this->next;
        // next->prev = prev
        this->next->prev = this->prev;
        // Clear this node's next pointer
        this->next = nullptr;
    }

    // Switch vtable to final destructor vtable
    this->__vtable = &PTR_LAB_00e37304;

    // If the free memory flag is set, call operator delete (via wrapper at 0x009c8eb0)
    if ((freeMemoryFlag & 1) != 0)
    {
        FUN_009c8eb0(this);  // operator delete(this)
    }
}