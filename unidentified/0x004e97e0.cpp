// FUN_004e97e0: FreeNode::unlinkAndFree

// This function removes 'this' node from an intrusive singly linked list.
// The node stores a pointer to the list head at offset 0x00 and a next pointer at offset 0x04.
// After unlinking, the node is freed via FUN_009c8eb0 (likely operator delete or pool return).

class FreeListHead {
public:
    int count;          // +0x00 (could be padding or unused)
    FreeNode* first;    // +0x04
};

class FreeNode {
public:
    FreeListHead* list; // +0x00 - pointer to owning list head
    FreeNode* next;     // +0x04
};

void FreeNode::unlinkAndFree(void)
{
    FreeListHead* head = this->list;
    if (head != nullptr) {
        FreeNode* walker = head->first; // head->first at offset +0x04 from head
        if (walker == this) {
            // 'this' is the first (and possibly only) node in the list
            head->first = this->next;
        } else {
            // Scan the list to find the predecessor of 'this'
            FreeNode* prev = walker;
            walker = walker->next;
            while (walker != this) {
                prev = walker;
                walker = walker->next;
            }
            // Unlink 'this' by updating predecessor's next
            prev->next = this->next;
        }
    }
    // Release the node (memory free, object pool return, etc.)
    FUN_009c8eb0(); // called after unlinking; likely frees 'this'
}