// FUNC_NAME: ListNode::insertAtTail

// Node structure: offset +0x04 = next pointer, +0x08 = prev pointer.
// Global doubly-linked list head (0x0120e9f4) and tail (0x0120e9f8).
struct ListNode {
    void*     field_0;   // +0x00 unknown
    ListNode* next;      // +0x04
    ListNode* prev;      // +0x08
};

static ListNode* s_listHead = (ListNode*)0x0120e9f4; // head of global list
static ListNode* s_listTail = (ListNode*)0x0120e9f8; // tail of global list

void __fastcall ListNode::insertAtTail() {
    ListNode* head = s_listHead;
    ListNode* tail = s_listTail;

    // Insert only if this node is not already the head and its prev is null (i.e., not already linked)
    if (head != this && this->prev == nullptr) {
        this->next = nullptr;
        this->prev = tail;

        if (tail != nullptr) {
            // List not empty: link old tail to this and update tail
            tail->next = this;
            s_listTail = this;
            return; // skip the global reassignment below
        }
        // else: list was empty, fall through to set head and tail to this
    }

    // Update head/tail globals (if list was empty and we inserted, this becomes both head and tail)
    s_listHead = head; // effectively no change unless we inserted into empty list
    s_listTail = tail;
}