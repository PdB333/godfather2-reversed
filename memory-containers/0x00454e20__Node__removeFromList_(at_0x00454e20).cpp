// FUNC_NAME: Node::removeFromList (at 0x00454e20)
// Removes this node from a global doubly-linked list (head at gListHead, tail at gListTail)
// The node is assumed to have next at +0x04 and prev at +0x08.
// After removal, this node's next and prev pointers are zeroed out.

// Forward declarations
struct Node;

// Global list head and tail pointers
extern Node* gListHead;   // (DAT_0120e9f4)
extern Node* gListTail;   // (DAT_0120e9f8)

struct Node {
    // +0x04: pointer to next node in global list
    Node* next;
    // +0x08: pointer to previous node in global list
    Node* prev;

    // Removes this node from the global doubly-linked list
    void __thiscall removeFromList();
};

void __thiscall Node::removeFromList() {
    // if prev is null, we are removing the head
    if (this->prev == nullptr) {
        gListHead = this->next;
        if (gListHead != nullptr) {
            gListHead->prev = nullptr;
        }
    } else {
        // link prev->next to this->next
        this->prev->next = this->next;
    }

    // if next is not null, update its prev pointer and clear our links
    if (this->next != nullptr) {
        this->next->prev = this->prev;
        this->next = nullptr;
        this->prev = nullptr;
        return;
    }

    // else (next is null), we are removing the tail
    gListTail = this->prev;
    if (gListTail != nullptr) {
        gListTail->next = nullptr;
    }
    this->next = nullptr;
    this->prev = nullptr;
}