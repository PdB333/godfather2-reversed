// FUNC_NAME: LinkedList::copyFrom
struct ListNode {
    ListNode* next;   // +0x0
    ListNode* prev;   // +0x4
    int value2;       // +0x8
    int value3;       // +0xC
};

struct LinkedList {
    ListNode* head;   // +0x0
    ListNode* tail;   // +0x4
    int field2;       // +0x8
    int field3;       // +0xC
    int field4;       // +0x10

    LinkedList* __thiscall copyFrom(LinkedList* src);
};

// Custom allocator (likely operator new or pool allocator)
extern void* __cdecl operator_new(size_t size);

LinkedList* LinkedList::copyFrom(LinkedList* src) {
    this->head = nullptr;
    this->tail = nullptr;
    this->field2 = src->field2;
    this->field3 = src->field3;
    this->field4 = 0;

    ListNode* srcNode = src->head;
    while (srcNode != nullptr) {
        ListNode* newNode = (ListNode*)operator_new(0x10);
        if (newNode == nullptr) {
            newNode = nullptr;
        } else {
            new (newNode) ListNode();
            newNode->next = nullptr;
            newNode->prev = nullptr;
            newNode->value2 = srcNode->value2;
            newNode->value3 = srcNode->value3;
        }

        // Link into this list
        newNode->next = nullptr;
        newNode->prev = this->tail;
        if (this->tail == nullptr) {
            this->head = newNode;
        } else {
            this->tail->next = newNode;
        }
        this->tail = newNode;

        srcNode = srcNode->next;
    }

    return this;
}