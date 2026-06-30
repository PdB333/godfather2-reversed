// FUNC_NAME: TraverseAndProcessNodeList
// Function at 0x005313d0: Traverses a linked list starting from global head pointer, 
// calling FUN_005326c0 on each node. Node structure has 'next' pointer at offset 0x10.

// Forward declaration of the node struct
struct Node {
    // +0x00: unknown data
    // +0x10: pointer to next node
    Node* next; // offset 0x10
};

// Global head pointer (DAT_01194a68)
extern Node* g_pNodeHead;

// Processing function called on each node (FUN_005326c0)
void ProcessNode(Node* pNode);

void TraverseAndProcessNodeList(void)
{
    Node* pCurrent = g_pNodeHead;
    while (pCurrent != nullptr)
    {
        Node* pNext = pCurrent->next; // save next before processing (in case node is freed)
        ProcessNode(pCurrent);
        pCurrent = pNext;
    }
}