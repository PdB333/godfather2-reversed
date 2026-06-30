// FUNC_NAME: LinkedListContainer::LinkedListContainer
class LinkedListContainer {
public:
    void* vtable1;          // +0x00
    struct ListNode* head;  // +0x04
    // ... possibly other members at +0x08..+0x14
    void* vtable2;          // +0x18
};

struct ListNode {
    void* data;    // +0x00
    ListNode* next;// +0x04
    ListNode* prev;// +0x08
};

void __fastcall operatorDelete(void* ptr); // forward declaration for FUN_009c8eb0

LinkedListContainer* __thiscall LinkedListContainer::LinkedListContainer(byte allocFlag) {
    // Set vtable pointers (likely for base class hierarchies)
    this->vtable2 = (void*)&PTR_LAB_00e317cc; // secondary vtable
    this->vtable1 = (void*)&PTR_LAB_00e42de4; // primary vtable (or base class 1)

    // Clear the linked list: iterate through all nodes and zero their fields
    ListNode* current = this->head;
    while (current != nullptr) {
        ListNode* next = current->next; // save next node before clearing
        current->data = nullptr;
        current->next = nullptr;
        current->prev = nullptr;
        current = next;
    }

    // If the allocation flag's low bit is set, deallocate the object
    if ((allocFlag & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}