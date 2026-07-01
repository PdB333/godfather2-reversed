// FUNC_NAME: SimManager::addResourceItem
#include <cstdint>

// Forward declarations (engine internals)
extern uint32_t _DAT_00e546a0;
extern uint32_t _DAT_00d80de4;

// External helper functions (inferred from usage)
uint32_t getResource(const char* name, uint32_t global, int flags);  // FUN_00404280
void setResourceProperty(uint32_t resource, uint32_t propId, uint32_t value); // FUN_004035c0
int getChildObject(uint32_t object); // FUN_004025a0
bool isFlagSet(); // FUN_00402c80
void attachToParent(int child, uint32_t resource, uint32_t parentData); // FUN_00406130
uint32_t* getListHead(const char* name); // FUN_008ef250
void* allocateMemory(size_t size); // FUN_009c8e50
uint32_t constructNode(uint32_t extraInfo); // FUN_008eacb0 (returns pointer to node)
void notifyAfterAdd(const char* name, uint32_t resource); // FUN_008ee940

// Node structure for the linked list (size 0x2C)
struct ListNode {
    uint32_t data;      // +0x00: pointer to something (resource handle?)
    ListNode* next;     // +0x04: next node in list
    // remaining 0x28 bytes unknown but not used in this function
};

// Method: SimManager::addResourceItem
// Adds a resource (e.g., entity definition) to the manager, creates a node in a name-keyed list.
uint32_t __thiscall SimManager::addResourceItem(void* pData, const char* name, int parentObject, uint32_t extraInfo) {
    uint32_t resource;
    int iVar3;
    int* piVar4;
    int iVar5;
    ListNode* newNode;

    // Set a flag on the data (e.g., "loaded" or "active")
    *(uint32_t*)((uint8_t*)pData + 8) = 1;

    // Load the resource (e.g., from a database) using name and global flag
    resource = getResource(name, _DAT_00e546a0, 0);

    // Set a property on the resource: index 0x46 = 70, value = this pointer
    setResourceProperty(resource, 0x46, (uint32_t)this);

    // If a parent object is provided, try to attach the resource to it
    if (parentObject != 0) {
        iVar3 = getChildObject(parentObject);
        if (iVar3 != 0) {
            if (!isFlagSet()) {
                attachToParent(iVar3, resource, _DAT_00d80de4);
            }
        }
    }

    // Get the head of the linked list associated with this name
    piVar4 = (int*)getListHead(&name);

    // Allocate memory for a new list node (size 0x2C = 44 bytes)
    iVar5 = (int)allocateMemory(0x2C);
    if (iVar5 == 0) {
        newNode = nullptr;
    } else {
        newNode = (ListNode*)constructNode(extraInfo);
    }

    // Insert the new node at the head of the linked list
    newNode->data = (uint32_t)piVar4[0];   // old head's data pointer (unused here)
    newNode->next = nullptr;               // new node's next pointer
    if (*piVar4 == 0) {
        // If list is empty, set tail pointer (piVar4[1]) to new node
        piVar4[1] = (int)newNode;
    } else {
        // Otherwise, link the old head's next to the new node
        *(ListNode**)(*piVar4 + 4) = newNode;
    }
    *piVar4 = (int)newNode;  // update head to new node

    // If the resource has a specific property (offset 0x24 == 3), notify after addition
    iVar3 = getChildObject(resource);
    if ((iVar3 != 0) && (*(int*)(iVar3 + 0x24) == 3)) {
        notifyAfterAdd(&name, resource);
    }

    return resource;
}