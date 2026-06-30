// FUNC_NAME: ListNodePool::resetList
// Function address: 0x0065fa40
// Clears a linked list of nodes (each with 3 fields: two data pointers + next pointer)
// Optionally deallocates the object if param_2 bit 0 is set.

class ListNodePool {
public:
    void* vtable;           // +0x00 (set to PTR_LAB_00e42de4)
    ListNodePool* head;     // +0x04 (pointer to first node in list)
};

struct ListNode {
    void* field0;           // +0x00
    void* field1;           // +0x04
    ListNode* next;         // +0x08
};

// Extern: cleanup function (likely operator delete or custom deallocate)
extern void __cdecl deallocateObject(ListNodePool* obj);

ListNodePool* __thiscall ListNodePool::resetList(byte param_2) {
    ListNodePool* ret = this;

    // Set the virtual table pointer (constructor-like initialization)
    this->vtable = &LAB_00e42de4; // VTable for ListNodePool

    // Traverse the linked list starting at offset +0x04
    ListNode* currentNode = this->head;
    while (currentNode != nullptr) {
        ListNode* nextNode = currentNode->next; // Save next pointer before clearing
        currentNode->field0 = nullptr;
        currentNode->field1 = nullptr;
        currentNode->next = nullptr;            // Sever link
        currentNode = nextNode;
    }

    // If the low bit of param_2 is set, deallocate the pool object itself
    if ((param_2 & 1) != 0) {
        deallocateObject(this);
    }

    return ret;
}