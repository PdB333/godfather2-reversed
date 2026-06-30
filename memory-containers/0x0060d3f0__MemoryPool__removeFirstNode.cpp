// FUNC_NAME: MemoryPool::removeFirstNode
// Function address: 0x0060d3f0
// Removes the first node from a global free list and updates the global head/tail pointers.
// The node is then deallocated via a virtual function in the global allocator object.

// Node structure for the doubly-linked list
struct MemoryNode {
    MemoryNode* next;  // +0x00
    MemoryNode* prev;  // +0x04
    // +0x08: additional data (not used here)
};

// Global variables (from Ghidra DAT)
extern MemoryNode* g_pHead;       // DAT_012224e0
extern MemoryNode* g_pTail;       // DAT_012224e4
extern int g_nCount;              // DAT_012224e8
extern class Allocator* g_alloc;  // DAT_012224f0 (pointer to an allocator with vtable)

// Allocator interface (assumed)
class Allocator {
public:
    virtual void deallocate(void* ptr, int flags);  // offset +4 in vtable
    // first virtual function at offset 0, this is second
};

// The function uses two pointer parameters passed in registers (ESI: ppHead, EDI: ppNewHead)
// In this reconstruction, we treat it as a regular function.
void removeFirstNode(MemoryNode** ppHead, MemoryNode** ppNewHead)
{
    MemoryNode* pNode = *ppHead;
    MemoryNode* pNext = (pNode != nullptr) ? pNode->next : nullptr;

    // Update the local list head
    *ppHead = pNext;

    // Adjust global head/tail pointers if the removed node was at either end
    if (pNode == g_pHead) {
        if (pNode == g_pTail) {
            // Removing the only node
            g_pTail = nullptr;
            g_pHead = nullptr;
        } else {
            g_pHead = pNode->next;
            if (g_pHead != nullptr) {
                g_pHead->prev = nullptr;
            }
        }
    } else if (pNode == g_pTail) {
        g_pTail = pNode->prev;
        if (g_pTail != nullptr) {
            g_pTail->next = nullptr;
        }
    } else {
        // Standard doubly-linked list removal from middle
        pNode->prev->next = pNode->next;
        pNode->next->prev = pNode->prev;
    }

    // Call the allocator's deallocate function (virtual, offset +4)
    g_alloc->deallocate(pNode, 0);

    // Decrement global node count
    g_nCount--;

    // Return the new list head through the output parameter
    *ppNewHead = *ppHead;
}