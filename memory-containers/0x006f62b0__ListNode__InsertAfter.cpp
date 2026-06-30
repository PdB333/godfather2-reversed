// FUNC_NAME: ListNode::InsertAfter
// Function address: 0x006f62b0
// Role: Inserts this node after the list node at offset 0x48 in the given container object.
// If the container pointer is null, the node's prev pointer is set to null (detaching it).

struct ListNode {
    ListNode* prev; // offset 0
    ListNode* next; // offset 4
};

// Forward declaration of the removal function (at 0x004daf90)
void __thiscall removeFromList(ListNode* node);

__thiscall ListNode* ListNode::InsertAfter(void* container) {
    ListNode* newNode = nullptr;
    if (container != nullptr) {
        // The container has a ListNode at offset 0x48
        newNode = reinterpret_cast<ListNode*>(reinterpret_cast<char*>(container) + 0x48);
    }

    if (this->prev != newNode) {
        if (this->prev != nullptr) {
            // Remove this node from its current list
            removeFromList(this);
        }
        this->prev = newNode;
        if (newNode != nullptr) {
            // Insert this node after newNode in the doubly linked list
            this->next = newNode->next;
            newNode->next = this;
        }
    }

    return this;
}