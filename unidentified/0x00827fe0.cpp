// FUNC_ADDR: 0x00827fe0  
// ROLE: Constructor for an intrusive doubly linked list node – inserts after the given list head.  
// Likely part of EARS engine (e.g., EARS::Node or a similar intrusive container).  
// The node stores the list head pointer, and its link fields (prev/next) are at offsets 0x1C and 0x20.

// Head structure: offset 0x4 holds the "next" pointer (to the first node's prev field address).
// The linked list uses container_of style: head->next points to &node->prev, and node->prev points to head.

// Global timestamp/counter used for sequencing or identification.
extern unsigned int g_nodeTimestamp;   // _DAT_00d5c458

class IntrusiveListNode
{
public:
    // VMT pointer at offset 0x00
    void* vmt;

    // ... other member fields ...

    // Link fields at offsets 0x1C and 0x20 (indices 7 and 8)
    IntrusiveListNode* prev;   // +0x1C
    IntrusiveListNode* next;   // +0x20

    // Additional fields follow:
    // +0x24 (index 9): timestamp copy
    // +0x28 (index 10): 0
    // +0x2C (index 0xB): another timestamp copy
    // +0x30 (index 0xC): 0
    // +0x34 (index 0xD): 0
    // +0x38 (index 0xE): 1
    // +0x3C (index 0xF): a byte (0)
};

// Global base constructor for the object (must be called first)
extern void IntrusiveListNodeBaseCtor(IntrusiveListNode* this);  // FUN_008238b0

IntrusiveListNode* __thiscall IntrusiveListNode::constructor(IntrusiveListNode* this, IntrusiveListNode* pListHead)
{
    // Call base constructor (likely initializes vmt and other base members)
    IntrusiveListNodeBaseCtor(this);

    // Set vtable pointer (comes from base; we override here)
    this->vmt = &g_vtableTable;   // PTR_FUN_00d73594 (external global)

    // Link the node into the list after the given list head.
    this->prev = pListHead;               // +0x1C: store head as previous
    this->next = nullptr;                 // +0x20: initially no next

    if (pListHead != nullptr)
    {
        // Insert: new node's next = head's current next (which is actually &(first node->prev))
        // Head->next (offset 0x4) holds the address of the first node's 'prev' field.
        // We treat head->next as a pointer to the first node's prev field.
        this->next = reinterpret_cast<IntrusiveListNode*>(
                        *(reinterpret_cast<uint32_t*>(pListHead) + 1)   // head + 0x4
                     );
        // Update head's next to point to our prev field (making us first)
        *(reinterpret_cast<uint32_t*>(pListHead) + 1) = reinterpret_cast<uint32_t>(&(this->prev));
    }

    // Initialize timestamp / sequence number
    uint32_t timestamp = g_nodeTimestamp;
    // Indices 9, 10, 11, 12, 13, 14, 15 (offsets 0x24, 0x28, 0x2C, 0x30, 0x34, 0x38, 0x3C)
    *(reinterpret_cast<uint32_t*>(this) + 9) = timestamp;   // +0x24
    *(reinterpret_cast<uint32_t*>(this) + 10) = 0;          // +0x28
    *(reinterpret_cast<uint32_t*>(this) + 11) = timestamp;  // +0x2C
    *(reinterpret_cast<uint32_t*>(this) + 12) = 0;          // +0x30
    *(reinterpret_cast<uint32_t*>(this) + 13) = 0;          // +0x34
    *(reinterpret_cast<uint32_t*>(this) + 14) = 1;          // +0x38
    *(reinterpret_cast<uint8_t*>(this) + 0x3C) = 0;         // +0x3C (byte)

    return this;
}