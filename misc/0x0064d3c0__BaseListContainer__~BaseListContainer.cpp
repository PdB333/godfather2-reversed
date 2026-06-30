// FUNC_NAME: BaseListContainer::~BaseListContainer
class BaseListContainer {
public:
    void* vtable;               // +0x00: virtual function table pointer
    struct ListNode* head;      // +0x04: head of linked list

    struct ListNode {
        uint32_t unknown0;      // +0x00
        uint32_t unknown1;      // +0x04
        ListNode* next;         // +0x08: pointer to next node
    };

    void* __thiscall ~BaseListContainer(byte flags) {
        // Set vtable to base class vtable (likely to disable virtual calls during destruction)
        this->vtable = (void*)&PTR_LAB_00e42de4;  // Base vtable label

        // Walk and clear all nodes in the linked list
        ListNode* currentNode = this->head;
        while (currentNode != nullptr) {
            ListNode* nextNode = currentNode->next;
            // Zero out node contents (likely freeing data or resetting)
            currentNode->unknown0 = 0;
            currentNode->unknown1 = 0;
            currentNode->next = nullptr;
            currentNode = nextNode;
        }

        // If the deallocation flag is set, free the memory of this object
        if (flags & 1) {
            operator delete(this);
        }

        return this;
    }
};