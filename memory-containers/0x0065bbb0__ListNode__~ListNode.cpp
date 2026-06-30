// FUNC_NAME: ListNode::~ListNode
// Function at 0x0065bbb0: Destructor for a doubly-linked list node; unlinks from list and optionally deallocates.
class ListNode {
public:
    void *vtable;       // +0x00
    ListNode *next;     // +0x04
    ListNode *prev;     // +0x08
    // ...
};

// Global head of the linked list (DAT_01205a54)
ListNode *g_nodeListHead;

__thiscall ListNode * ListNode::~ListNode(ListNode *this, byte deallocFlag)
{
    // Set vtable to base destructor vtable (PTR_FUN_00e433e8)
    this->vtable = &vtable_00e433e8;

    // Unlink this node from the doubly-linked list
    if (this->next != nullptr) {
        // next->prev = this->prev
        this->next->prev = this->prev;
    }
    if (this->prev == nullptr) {
        // This node is the head of the list; update global head
        g_nodeListHead = this->next;
    } else {
        // prev->next = this->next
        this->prev->next = this->next;
    }

    // If the deallocation flag's low bit is set, free memory (operator delete)
    if ((deallocFlag & 1) != 0) {
        operator delete(this);  // equivalent to FUN_009c8eb0
    }
    return this;
}