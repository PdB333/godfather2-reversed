// FUNC_NAME: RefCountedListNode::release
struct RefCountedListNode {
    RefCountedListNode* prev;   // +0x00
    RefCountedListNode* next;   // +0x04
    char flags;                 // +0x08 (low byte of original int field)
    char refCount;              // +0x09 (second byte of original int field)
};

// Global list head (DAT_01205568)
struct ListNodeHead {
    int unknown;                // +0x00
    RefCountedListNode* first;  // +0x04
    RefCountedListNode* last;   // +0x08
    RefCountedListNode* sentinel; // +0x0C (used when list is empty)
};

extern ListNodeHead g_head;

// Unknown cleanup function at 0x0056f4b0
extern void __cdecl OnBeforeRelease(void);

void __thiscall RefCountedListNode::release(void)
{
    if (this == 0) return;

    OnBeforeRelease();                     // pre-release processing

    this->refCount--;                      // decrement reference count

    // If the node is no longer flagged as "in list" and refCount is zero,
    // remove it from the global doubly linked list.
    if (this->flags == '\0' && this->refCount == '\0')
    {
        RefCountedListNode* prevPtr = this->prev;
        RefCountedListNode* nextPtr = this->next;

        if (prevPtr != 0)
        {
            prevPtr->next = nextPtr;       // bypass this node forward
        }

        if (nextPtr != 0)
        {
            nextPtr->prev = prevPtr;       // bypass this node backward
            return;                        // done, node was in the middle
        }

        // Removing the tail node: update head's last pointer
        g_head.last = g_head.first;        // last becomes first (or null)
        g_head.first = prevPtr;            // previous node becomes new first

        if (prevPtr == 0)
        {
            // List is now empty
            g_head.last = g_head.sentinel; // reset sentinel
        }
    }
}