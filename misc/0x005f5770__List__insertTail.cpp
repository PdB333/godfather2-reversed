// FUNC_NAME: List::insertTail

// Address: 0x005f5770
// This function inserts a node at the tail of a doubly-linked list with a fixed maximum size.
// The list structure fields are:
// [this+0x00] ListNode* head
// [this+0x04] ListNode* tail
// [this+0x08] uint16_t maxSize
// [this+0x0A] uint16_t size
// Each node has:
// [node+0x00] ListNode* prev
// [node+0x04] ListNode* next

// The original __fastcall used ECX = this, EDX = newNode.
// EAX appears to carry a previous value (e.g., from a caller) and is used only in the empty‑list case.

struct ListNode {
    ListNode* prev; // +0x00
    ListNode* next; // +0x04
};

struct List {
    ListNode* head;   // +0x00
    ListNode* tail;   // +0x04
    uint16_t maxSize; // +0x08
    uint16_t size;    // +0x0A
};

uint __fastcall List::insertTail(List* _this, ListNode* newNode) {
    uint result;

    // The original code loads EAX and masks off the low byte.
    // This value is only used when the list is empty.
    // Since we cannot determine the caller's intent, we treat it as undefined.
    result = 0; // placeholder for (in_EAX & 0xFFFFFF00)

    if (_this->size < _this->maxSize && newNode != nullptr) {
        if (_this->size == 0) {
            // First node: head becomes the new node
            _this->head = newNode;
            // result remains the initial value (in_EAX & 0xFFFFFF00)
        } else {
            // Insert after current tail
            ListNode* oldTail = _this->tail;
            if (oldTail == nullptr) {
                // Should not happen when size > 0
                return 0;
            }
            // Link old tail to new node
            oldTail->next = newNode;
            // Build return value: (oldTail & 0xFFFFFF00) | 1
            result = (reinterpret_cast<uint>(oldTail) & 0xFFFFFF00) | 1;
        }
        // Set new node's prev (may be nullptr if list was empty)
        newNode->prev = _this->tail;
        // New node has no successor yet
        newNode->next = nullptr;
        // Increase size
        ++_this->size;
        // Update tail
        _this->tail = newNode;
    }
    return result;
}