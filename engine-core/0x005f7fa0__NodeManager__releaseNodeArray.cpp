//FUNC_NAME: NodeManager::releaseNodeArray
// Function address: 0x005f7fa0
// Role: Releases all objects in a node array, removes nodes from their linked lists, and frees the array.
// Structure layout:
//   Node (12 bytes): +0x00: pointer to list head, +0x04: next pointer, +0x08: object pointer
//   ListHead (at least 8 bytes): +0x04: pointer to first node

#include <cstdint>

// Forward declaration for the object class (vtable-based)
class IReleaseable {
public:
    virtual void release(int flag) = 0; // vtable offset 0x04
};

// Structure for a node in a singly linked list
struct ListNode {
    ListNode* listHead; // +0x00: pointer to the list head structure
    ListNode* next;     // +0x04: next node in the list
    IReleaseable* obj;  // +0x08: pointer to the object to release
};

// Structure for the list head (contains pointer to first node at +0x04)
struct ListHead {
    // +0x00: unknown (maybe size or other data)
    ListNode* first; // +0x04: pointer to first node
};

// Global pointer to some manager object (used for vtable calls)
extern void* g_ManagerVTable; // DAT_01223520

// This function is a member of NodeManager (param_1 = this)
int NodeManager::releaseNodeArray(ListNode* nodeArray, uint32_t* countPtr) {
    if (nodeArray == nullptr) {
        return 0;
    }

    uint32_t count = *countPtr;
    ListNode* currentNode = nodeArray;

    for (uint32_t i = 0; i < count; i++) {
        // Release the object if present
        if (currentNode->obj != nullptr) {
            // Call virtual release function (vtable offset 0x04) on the object
            // The vtable is obtained from g_ManagerVTable + 0x10
            void** vtable = *(void***)((uint8_t*)g_ManagerVTable + 0x10);
            void (*releaseFunc)(IReleaseable*, int) = (void (*)(IReleaseable*, int))vtable[1]; // offset 4
            releaseFunc(currentNode->obj, 0);
            currentNode->obj = nullptr;
        }

        // Remove the node from its linked list
        ListHead* head = currentNode->listHead;
        if (head != nullptr) {
            ListNode* firstNode = head->first;
            if (firstNode == currentNode) {
                // Node is the first in the list; update head
                head->first = currentNode->next;
            } else {
                // Traverse to find the previous node
                ListNode* prev = firstNode;
                while (prev->next != currentNode) {
                    prev = prev->next;
                }
                prev->next = currentNode->next;
            }
        }

        // Move to next node (each node is 3 ints = 12 bytes)
        currentNode++;
    }

    // Release the node array itself via a virtual call on the manager
    void** managerVTable = *(void***)((uint8_t*)g_ManagerVTable + 0x10);
    void (*releaseArrayFunc)(ListNode*, int) = (void (*)(ListNode*, int))managerVTable[1];
    releaseArrayFunc(nodeArray, 0);

    return 0;
}