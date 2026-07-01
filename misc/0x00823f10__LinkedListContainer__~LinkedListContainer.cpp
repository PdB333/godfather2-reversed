// FUNC_NAME: LinkedListContainer::~LinkedListContainer
// Address: 0x00823f10
// Role: Destructor for a linked list container class. Clears a back pointer and iterates the linked list, zeroing out list nodes, then optionally deletes the object.

class LinkedListContainer {
public:
    void* vtable;                              // +0x00
    struct ListNode* listHead;                 // +0x04 (param_1[1])
    // padding or other members between +0x04 and +0x18
    void* unknownPtr;                          // +0x18 (param_1[6]) - pointer to some parent or manager

    // Destructor (scalar deleting)
    void __thiscall destroy(byte deletingFlag) {
        // Set vtable to first base vtable
        this->vtable = &PTR_FUN_00d73438;

        // If the pointer at +0x18 is valid, clear the back-reference at offset +8 of that object
        if (this->unknownPtr != 0) {
            *(int*)((int)this->unknownPtr + 8) = 0;
            this->unknownPtr = 0;
        }

        // Set vtable to second base vtable (next in inheritance chain)
        this->vtable = &PTR_FUN_00e32808;

        // Clear the linked list: walk through nodes, zeroing pointers
        ListNode* currentNode = this->listHead;
        while (currentNode != 0) {
            ListNode* nextNode = currentNode->next; // offset +4
            currentNode->next = 0;                   // clear next pointer
            currentNode->data = 0;                   // clear data (offset +0)
            currentNode = nextNode;
        }

        // If the deleting flag is set, call operator delete (via FUN_009c8eb0)
        if (deletingFlag & 1) {
            FUN_009c8eb0(this);
        }
    }
};

// ListNode structure used in the linked list
struct ListNode {
    int data;      // +0x00
    ListNode* next; // +0x04
};