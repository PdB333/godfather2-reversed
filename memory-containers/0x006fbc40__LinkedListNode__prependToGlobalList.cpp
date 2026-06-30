// FUNC_NAME: LinkedListNode::prependToGlobalList
// Address: 0x006fbc40
// Role: Doubly-linked list node constructor that inserts the node at the head of a global list.
// The node structure (size 0x10):
//   +0x00: data1 (param_2)
//   +0x04: data2 (param_3)
//   +0x08: pPrev (pointer to previous node)
//   +0x0C: pNext (pointer to next node)

// Global head of the list
extern LinkedListNode* g_pHead; // DAT_0112aaa8

struct LinkedListNode {
    DWORD data1;           // +0x00
    DWORD data2;           // +0x04
    LinkedListNode* pPrev; // +0x08
    LinkedListNode* pNext; // +0x0C

    // Prepends this node to the global list
    void __thiscall prependToGlobalList(DWORD param_2, DWORD param_3)
    {
        // Initialize node data
        data1 = param_2;
        data2 = param_3;

        // New node becomes the head: its prev is null, next points to current head
        pPrev = 0;
        pNext = g_pHead;

        // If the list was not empty, update old head's prev to point to this node
        if (g_pHead != 0)
        {
            g_pHead->pPrev = this;
        }

        // Update global head
        g_pHead = this;
    }
};