// FUNC_NAME: UnknownClass::~UnknownClass
// Address: 0x0051a060
// Destructor: cleans up a linked list of nodes, then optionally deallocates memory.

struct ListNode {
    void *data;       // +0x00: pointer to contained data
    ListNode *next;   // +0x04: next node in list
};

struct UnknownClass {
    void **vtable;    // +0x00: virtual function table
    ListNode *head;   // +0x04: head of linked list
    ListNode *tail;   // +0x08: tail of linked list (or similar secondary pointer)
};

// External vtable symbols
extern void *VTable_Base;    // PTR_FUN_00e38258
extern void *VTable_Derived; // PTR_FUN_00e32808

// External operator delete (called when flags & 1)
extern void __fastcall operator_delete(void *ptr); // FUN_009c8eb0

undefined4 * __thiscall UnknownClass::~UnknownClass(UnknownClass *this, byte flags)
{
    ListNode *current;
    ListNode *next;

    // Set vtable to base class vtable
    this->vtable = &VTable_Base;

    // If tail pointer exists, clear it
    if (this->tail != 0) {
        *(undefined4 *)this->tail = 0;
        this->tail = 0;
    }

    // Set vtable to derived class vtable (or second stage)
    this->vtable = &VTable_Derived;

    // Traverse the linked list and zero out each node's fields
    current = this->head;
    while (current != 0) {
        next = current->next;
        current->next = 0;
        current->data = 0;
        current = next;
    }

    // If deletion flag is set, free the object memory
    if ((flags & 1) != 0) {
        operator_delete(this);
    }

    return (undefined4 *)this;
}