// FUNC_NAME: LinkedList::destroyAllNodes
// Address: 0x0089ebc0
// Role: Destroys all nodes in a circular doubly linked list with sentinel.
// Each node has: next (offset 0), prev (offset 4), and a pointer to a sub-object (offset 8).
// If the sub-object pointer is non-null, it is destroyed via FUN_004daf90.
// Then the node itself is deallocated via FUN_009c8f10.

struct ListNode {
    ListNode* next;      // +0x00
    ListNode* prev;      // +0x04
    void*   subObject;   // +0x08
};

void __fastcall LinkedList::destroyAllNodes(ListNode* sentinel)
{
    ListNode* currentNode = sentinel->next;
    while (currentNode != sentinel) {
        ListNode* nextNode = currentNode->next;
        if (currentNode->subObject != nullptr) {
            FUN_004daf90(currentNode->subObject); // Destroy sub-object
        }
        FUN_009c8f10(currentNode); // Deallocate node
        currentNode = nextNode;
    }
}