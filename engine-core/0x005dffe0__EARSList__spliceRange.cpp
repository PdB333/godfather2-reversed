// FUNC_NAME: EARSList::spliceRange
// Address: 0x005dffe0
// This function implements a range splice operation on an intrusive circular doubly linked list.
// It moves a range of nodes (param_3 to param_5) from the list to form a new list, or removes them.
// The list's head pointer is stored at this+0x1c (int**), and a count/enum field at this+0x20.
// The node layout: offset 0: data (used for comparison), offset 4: next, offset 8: prev.
// The function also performs sanity checks via EARSError (FUN_00b97aea).

struct ListNode {
    int data;         // +0x00
    ListNode* next;   // +0x04
    ListNode* prev;   // +0x08
};

struct EARSList {
    ListNode** headPtr; // +0x1c  pointer to head pointer (doubled indirection)
    int someCount;      // +0x20  maybe count of nodes
};

void EARSError();                   // FUN_00b97aea
void removeNode(ListNode* node);    // FUN_005e1350 - removes a node from its list
void advanceAndInsert(EARSList* list, ListNode* tempBuffer, EARSList* owner, ListNode* current); // FUN_005e09e0 + FUN_005dec30

void EARSList::spliceRange(EARSList* outputList, EARSList* owner1, ListNode* firstNode, EARSList* owner2, ListNode* lastNode)
{
    ListNode* headNodeValue = *(*(this->headPtr)); // value at head node (data field)

    // Validate owners: they must be null or equal to this
    if ((owner1 != nullptr) && (owner1 != this))
        EARSError();
    if (owner2 != nullptr) && (owner2 != this))
        EARSError();

    // If the firstNode is the head node's data, and lastNode is also head node's data
    if (firstNode == headNodeValue && lastNode == headNodeValue)
    {
        // Special case: range is a single node (the head)
        ListNode* detachedNext = (*(this->headPtr))->next; // node's next
        removeNode(detachedNext);
        // Reset the head node to circular self-loop
        ListNode* head = *(this->headPtr);
        head->next = head;     // +0x04
        head->prev = head;     // +0x08
        head->data = (int)head; // +0x00, self-reference
        this->someCount = 0;

        // Output: first element of output list = this, second = headNode
        outputList[1] = (int)headNode; // Actually outputList is int* param_1, so param_1[1] = firstNode (head)
        *outputList = (int)this;
        return;
    }

    // General case: iterate from firstNode to lastNode, removing and reinserting?
    while (true)
    {
        if ((owner1 != nullptr) && (owner1 != owner2))
            EARSError();
        if (firstNode == lastNode)
            break;

        advanceAndInsert(this, local_8, owner1, firstNode); // uses local buffer
    }

    outputList[1] = (int)lastNode;
    *outputList = (int)owner1;
    return;
}