// FUNC_NAME: SList::~SList
// Address: 0x006d9ab0
// Role: Destructor for a simple linked list class. Clears the list by zeroing each node's data and next pointer,
// then optionally deallocates the list object itself if the flag is set.

// Node structure used in the linked list
struct SListNode {
    void* data;        // +0x00
    SListNode* next;   // +0x04
};

class SList {
public:
    void** vtable;     // +0x00 (virtual function table)
    SListNode* head;   // +0x04 (pointer to first node)

    // Destructor with deleting flag (byte param_2)
    // Returns 'this' for compatibility (as seen in decompilation)
    SList* __thiscall ~SList(unsigned char deletingFlag);
};

SList* __thiscall SList::~SList(unsigned char deletingFlag) {
    // Set vtable (usually done in constructor; here it's for destructor chaining?)
    this->vtable = (void**)&PTR_FUN_00e32808;

    SListNode* currentNode = this->head;
    // Traverse the list and clear each node's fields (but do not free the nodes themselves)
    while (currentNode != (SListNode*)0x0) {
        SListNode* nextNode = currentNode->next; // Save next pointer
        currentNode->next = (SListNode*)0x0;      // Clear next
        currentNode->data = (void*)0x0;           // Clear data
        currentNode = nextNode;                   // Move to next node
    }

    // If the delete flag is set, deallocate the list object itself
    if ((deletingFlag & 1) != 0) {
        // Call to operator delete or custom deallocation (FUN_009c8eb0)
        FUN_009c8eb0(this);
    }

    return this;
}