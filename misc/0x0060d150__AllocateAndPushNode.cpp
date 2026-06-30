// FUNC_NAME: AllocateAndPushNode

struct Node {
    uint32_t data;   // +0x00
    Node* next;      // +0x04
    Node* prev;      // +0x08
};

// Global allocator state (static data)
static uint32_t* g_pDefaultData = (uint32_t*)0x012224b8;   // Default data source
static uint32_t** g_allocatorVTable = (uint32_t**)(0x012224bc); // Allocator vtable
static Node* g_pStackHead = nullptr;  // Top of stack (head) at 0x012224b0
static int32_t g_nodeCount = 0;       // Number of nodes at 0x012224b4
static Node* g_pStackTail = nullptr;  // Bottom of stack (tail) at 0x012224ac

// Allocate a node, initialize it, and push onto the top of the stack.
void AllocateAndPushNode(void)
{
    uint32_t* dataSource;
    Node* pNewNode;

    // Select the data source: use g_pDefaultData if not null, otherwise fallback.
    if (g_pDefaultData != (uint32_t*)0x0) {
        dataSource = g_pDefaultData;
    } else {
        dataSource = (uint32_t*)0x01218a14; // fallback static data
    }

    // Allocate 12 bytes (sizeof(Node)) from the custom allocator.
    // The allocator is invoked via vtable call at g_allocatorVTable[0].
    pNewNode = (Node*)((*(code**)*g_allocatorVTable)[0])(0xC);
    if (pNewNode != (Node*)0x0) {
        pNewNode->data = *dataSource;
        pNewNode->next = nullptr;
        pNewNode->prev = nullptr;
    }

    if (g_pStackHead != nullptr) {
        // Stack not empty: insert new node at the top.
        g_pStackHead->next = pNewNode;
        if (pNewNode != nullptr) {
            pNewNode->prev = g_pStackHead;
        }
        g_nodeCount++;
        // Move head to the newly inserted node (LIFO behavior)
        g_pStackHead = (Node*)g_pStackHead->next;
    } else {
        // Stack empty: initialize head and tail to the new node.
        g_nodeCount = 1; // Actually increments from 0 to 1
        g_pStackTail = pNewNode;
        g_pStackHead = pNewNode;
    }
    return;
}