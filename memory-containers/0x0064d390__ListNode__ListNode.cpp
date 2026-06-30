// FUNC_NAME: ListNode::ListNode
class ListNode {
public:
    // vtable pointer at +0x00
    void* vtable;
    // +0x04: previous node pointer (initially null)
    ListNode* prev;
    // +0x08: next node pointer (initially null)
    ListNode* next;
    // +0x0C: user data 1 (from param_3)
    void* data1;
    // +0x10: user data 2 (from param_2)
    void* data2;

    // Constructor: initializes a doubly-linked list node.
    // param_2 is stored at +0x10 (data2), param_3 at +0x0C (data1).
    __thiscall ListNode(void* param_2, void* param_3) {
        // Set vtable to class's static vtable at 0x00e42df0
        this->vtable = (void*)0x00e42df0;
        this->prev = nullptr;
        this->next = nullptr;
        this->data2 = param_2;
        this->data1 = param_3;
    }
};