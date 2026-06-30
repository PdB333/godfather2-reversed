// FUNC_NAME: MemoryPool::releaseAll

// Reconstructs the member function at 0x0065ba30.
// Releases all nodes from the allocated list (m_allocatedList) back to the static free list.
// The free list head and count are static members of the pool.

class MemoryPool {
public:
    struct Node {
        Node* next; // +0x00: pointer to next node in list
    };

    Node* m_allocatedList; // +0x00: head of the allocated list (this pointer points here)
};

// Static globals (from Ghidra data references)
static int s_poolInitFlag = 0;               // _DAT_01223ba4
static int s_totalAllocatedCount = 0;        // _DAT_01223b98
static MemoryPool::Node* s_freeListHead = nullptr; // DAT_01223ba0

// Forward declarations for internal functions
void initMemoryPool(void);                   // FUN_0065ba80
void cleanupMemoryPool(void);                // LAB_00d51450

void MemoryPool::releaseAll()
{
    Node* currentNode = m_allocatedList; // traverse the allocated list
    Node* nextNode;

    while (currentNode != nullptr)
    {
        nextNode = currentNode->next; // save next before freeing

        // One-time initialization (flag check and set)
        if ((s_poolInitFlag & 1) == 0)
        {
            s_poolInitFlag |= 1;
            initMemoryPool(); // initialize the pool
            atexit(&cleanupMemoryPool); // register destructor at exit
        }

        s_totalAllocatedCount--; // decrement global allocation count

        // Push the node onto the free list (singly linked LIFO)
        currentNode->next = s_freeListHead;
        s_freeListHead = currentNode;

        currentNode = nextNode;
    }

    return;
}