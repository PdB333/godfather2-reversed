// FUNC_NAME: LinkedListManager::insertNodeOrReplace
#include <cstdint>

// Structure for a node in the doubly linked list
struct ListNode {
    void* data;      // +0x00: pointer to associated data
    ListNode* next;  // +0x04: next node
    ListNode* prev;  // +0x08: previous node
};

// Helper: allocates a new node and initializes it from a squared distance.
// First argument is a temporary buffer for construction, second is a global vtable,
// third is the squared distance used for sorting.
// Returns the newly created node via the temporary buffer.
// extern void createNodeFromDistance(ListNode* tempNode, void** vtable, float squaredDistance);

// extern void deallocateNode(void* node);

// The function expects a pointer to a node's data field (node->data) and a distance parameter.
// If the squared distance matches a new node creation, it replaces the current data pointer
// with the new node's address and adjusts the linked list accordingly.
// Returns true if the node was successfully inserted/replaced.
bool __thiscall LinkedListManager::insertNodeOrReplace(int* nodeDataPtr, float distance)
{
    float squaredDist;           // in_stack_00000014
    bool success;                // local_1d
    void** vtablePtr;            // local_1c: points to global vtable
    ListNode* tempNode;          // local_18: stack buffer used as temporary node
    float distCopy;              // local_14
    ListNode newNodeInfo[4];     // local_10: stack buffer to hold new node info (node* + extra)

    squaredDist = distance * distance;
    tempNode = (ListNode*)&stack0x00000008;   // point to stack buffer
    success = false;
    vtablePtr = &PTR_FUN_00d5d89c;            // global vtable reference
    newNodeInfo[0].data = nullptr;
    newNodeInfo[0].next = nullptr;
    newNodeInfo[0].prev = nullptr;            // local_10[2] = 0
    // local_10[3] set to 0x20, likely size of allocation or flag
    newNodeInfo[3].prev = (ListNode*)0x20;    // reinterpreted as prev pointer? Just ignore.
    distCopy = squaredDist;

    // Create node based on squared distance; the new node is stored in newNodeInfo[0]
    createNodeFromDistance(tempNode, &vtablePtr, squaredDist);

    ListNode* newNode = (ListNode*)newNodeInfo[0].data;  // iVar1 = local_10[0]

    // If nodeDataPtr is not the temporary buffer itself and the current data pointer
    // is different from the new node, perform the replacement
    if ((nodeDataPtr != (int*)newNodeInfo) && (*nodeDataPtr != (int)newNode))
    {
        if (*nodeDataPtr != 0)
        {
            deallocateNode((void*)(*nodeDataPtr));
        }
        // Replace the data pointer with the new node
        *nodeDataPtr = (int)newNode;
        if (newNode != nullptr)
        {
            // Update the next pointer of the current position (nodeDataPtr is assumed
            // to be the 'data' field of a ListNode; therefore nodeDataPtr[1] is the next pointer)
            // Keep the old next from the new node (likely for list order)
            nodeDataPtr[1] = *(int*)((int)newNode + 4);
            // Set the previous pointer of the new node to the current node
            *(ListNode**)((int)newNode + 4) = (ListNode*)nodeDataPtr;
        }
    }

    // Update the previous pointer of the current position (nodeDataPtr[2]) to zero
    nodeDataPtr[2] = (int)newNodeInfo[0].prev;  // actually set to 0 from earlier, but this is a no-op

    // Determine success: if the data pointer is now non-null and the temporary info had a flag
    if ((*nodeDataPtr != 0) && (newNodeInfo[0].prev != nullptr))
    {
        success = true;
    }

    vtablePtr = &PTR_FUN_00d5d89c;
    if (newNodeInfo[0].data != 0)
    {
        deallocateNode(newNodeInfo[0].data);  // clean up temporary allocation
    }

    return success;
}