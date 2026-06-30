// FUNC_NAME: EARSLinkedListNode::insertIntoList
struct EARSLinkedListNode {
    EARSLinkedListNode* next; // +0x00
    int prev;                 // +0x04 - stored as int; actually a pointer to the slot that points to this node
};

// Inserts this node at the head of a doubly-linked list using anchor pointers.
// pHead: pointer to the list's head pointer (the slot that stores the first node)
// pTailSentinel: pointer to the tail sentinel node, used when the list is empty to fix the prev link.
void __thiscall EARSLinkedListNode::insertIntoList(EARSLinkedListNode** pHead, EARSLinkedListNode* pTailSentinel)
{
    this->next = *pHead;                        // link forward to current first node
    this->prev = reinterpret_cast<int>(pHead); // store address of head pointer slot as prev

    EARSLinkedListNode* oldFirst = *pHead;
    if (oldFirst == nullptr) {
        oldFirst = pTailSentinel;               // use tail sentinel when list is empty
    }
    reinterpret_cast<EARSLinkedListNode**>(oldFirst->prev)[0] = this; // oldFirst->prev was a slot pointer, now points to this
    *pHead = this;
}