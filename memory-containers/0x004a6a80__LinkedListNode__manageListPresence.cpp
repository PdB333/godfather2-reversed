// FUNC_NAME: LinkedListNode::manageListPresence
// 0x004a6a80 - Manages a node's presence in a global doubly linked list (head/tail at 0x01205488/0x0120548c).
// param_2: false = remove this node from the list; true = ensure it's not in any list, then append to tail.

class LinkedListNode {
public:
    // Offsets: +0x8c = prev, +0x90 = next
    LinkedListNode* prev;   // +0x8c
    LinkedListNode* next;   // +0x90
};

// Global list pointers (addresses: 0x01205488, 0x0120548c)
extern LinkedListNode* g_listHead;
extern LinkedListNode* g_listTail;

void __thiscall LinkedListNode::manageListPresence(bool isAdd) {
    if (isAdd == false) {
        // Remove this node from the list
        if (this->prev != nullptr) {
            // Point previous node's next to this->next
            this->prev->next = this->next;
        }
        if (this->next != nullptr) {
            // Point next node's prev to this->prev
            this->next->prev = this->prev;
        }
        if (g_listHead == this) {
            g_listHead = this->next;
        }
        if (g_listTail == this) {
            g_listTail = this->prev;
        }
        // Disconnect this node entirely
        this->prev = nullptr;
        this->next = nullptr;
    } else {
        // First, ensure this node is removed from any list
        this->manageListPresence(false);  // Recursive call to remove

        // Then append to the tail of the global list
        if (g_listTail != nullptr) {
            g_listTail->next = this;
            this->prev = g_listTail;
            g_listTail = this;
            this->next = nullptr;
        } else {
            // List was empty
            g_listHead = this;
            this->prev = nullptr;
            g_listTail = this;
            this->next = nullptr;
        }
    }
}