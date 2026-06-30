// FUNC_NAME: LinkedList::~LinkedList
// Address: 0x006f06d0
// Destructor for a doubly-linked intrusive list. Clears all nodes by unlinking them.
// Optionally frees memory if the low bit of the flag (freeFlag) is set.

struct LinkedListNode {
    LinkedListNode* prev; // +0x00
    LinkedListNode* next; // +0x04
};

class LinkedList {
public:
    void* vtable;       // +0x00
    LinkedListNode* head; // +0x04, pointer to first node (or null if empty)

    __thiscall LinkedList() {
        vtable = &PTR_FUN_00e32808; // set to correct vtable
        head = nullptr;
    }

    __thiscall ~LinkedList(byte freeFlag) {
        vtable = &PTR_FUN_00e32808; // ensure vtable is set during destruction

        LinkedListNode* cur = head;
        while (cur != nullptr) {
            LinkedListNode* next = cur->next; // +0x04
            cur->next = nullptr;              // clear next
            cur->prev = nullptr;              // clear prev
            cur = next;
        }

        // freeFlag & 1 indicates whether to deallocate this object
        if ((freeFlag & 1) != 0) {
            // custom memory deallocation (likely operator delete, specific to engine)
            FUN_009c8eb0(this);
        }
    }
};