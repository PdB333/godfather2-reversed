// FUNC_NAME: ListNode::removeFromList
// Function at 0x004d1ea0: removes current node from a doubly linked list and outputs new head/tail if endpoints changed.
// Structure offset: +0x00 = next, +0x04 = prev

void __thiscall ListNode::removeFromList(int* outNewHeadTail)
{
    ListNode* next = this->next;    // in_EAX[0]
    ListNode* prev = this->prev;    // in_EAX[1]

    if (prev == nullptr) {
        // Removing head node
        outNewHeadTail[0] = (int)next;  // new head
        if (next != nullptr) {
            next->prev = nullptr;       // unlink head
        }
        if (next == nullptr) {
            goto handle_tail;
        }
        goto unlink_self;
    }
    else {
        // Removing non-head node
        prev->next = next;
    }

    if (next != nullptr) {
        // Remove node from middle or end (but not head)
        next->prev = prev;
    }

    // Self-zeroing
    this->next = nullptr;
    this->prev = nullptr;
    return;

handle_tail:
    // If node being removed was also the tail (i.e., list becomes empty or head removal when next == nullptr)
    outNewHeadTail[1] = (int)prev;
    if (prev != nullptr) {
        prev->next = nullptr;   // new tail has null next
    }
    this->next = nullptr;
    this->prev = nullptr;
}