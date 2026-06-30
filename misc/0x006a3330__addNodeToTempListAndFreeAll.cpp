// FUNC_NAME: addNodeToTempListAndFreeAll
// Function at 0x006a3330: Creates a temporary doubly-linked list, optionally adds a node, then frees all nodes in the list.

struct ListNode {
    ListNode* next; // +0x00
    ListNode* prev; // +0x04
    // Additional data may follow, assumed to be at +0x08
};

// Forward declarations of helper functions.
// FUN_006a2d70: if returns 0, the list is ready for addition; else skip addition.
static int listCheckState(ListNode* head);

// FUN_006a2e80: adds a node (param1) to the list.
static int listAddNode(ListNode* head, int param1);

// FUN_009c8f10: frees/deallocates a single node.
static void freeListNode(ListNode* node);

int addNodeToTempListAndFreeAll(int param1)
{
    ListNode sentinel; // local_c: dummy head (sentinel) on stack
    sentinel.next = &sentinel;
    sentinel.prev = &sentinel;

    int result = listCheckState(&sentinel);
    if (result == 0) {
        // Add the provided element to the list.
        result = listAddNode(&sentinel, param1);
    }

    // Iterate through the list and free all nodes.
    ListNode* currentNode = sentinel.next;
    while (currentNode != &sentinel) {
        ListNode* nextNode = currentNode->next;
        freeListNode(currentNode);
        currentNode = nextNode;
    }

    return result;
}