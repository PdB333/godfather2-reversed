// FUNC_NAME: ListManager::addNodeAfterHead
// Address: 0x005f92a0
// Inserts a new node into a doubly linked list after the head node.
// The head pointer is stored at offset 0x18 in the manager object.
// The extra parameter (likely allocation size/type) is passed in EAX.

struct ListNode {
    ListNode* prev; // +0x00
    ListNode* next; // +0x04
};

void __fastcall ListManager::addNodeAfterHead(int managerPtr, int extraParam)
{
    ListNode* listHead = *(ListNode**)(managerPtr + 0x18); // +0x18: pointer to list head node
    ListNode* newNode = (ListNode*)FUN_005f9fc0(listHead, listHead->next, extraParam); // allocates and links newNode->next = listHead->next, newNode->prev = listHead?
    FUN_005fa010();                         // initializes newNode (e.g., sets data fields)
    listHead->next = newNode;               // head->next = newNode
    newNode->next->prev = newNode;          // newNode->next->prev = newNode (update the node after newNode)
}
```