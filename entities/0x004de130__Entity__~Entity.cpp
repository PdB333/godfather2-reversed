// FUNC_NAME: Entity::~Entity
#include <cstddef>

// Global head of a singly linked list tracking all Entity instances
extern Entity* g_objectListHead; // DAT_012054b8

// Forward declaration of child node structure (used for internal linked list)
struct ChildNode {
    ChildNode* next; // offset +0x04
    // other data...
};

// Definition of the Entity class (partial, only relevant members)
class Entity {
public:
    // Vtable pointer at offset +0x00
    void** vtable;

    // Offset +0x30: pointer to head of child linked list (ChildNode*)
    ChildNode* childList;
    
    // Offset +0x04: next pointer for the global list (assumed from unlink logic)
    // In the global singly linked list, the next pointer is at offset +0x04
    Entity* next;

    // Vtable addresses (from the binary, symbolic names)
    static void** s_vtableDerived; // PTR_FUN_00e36f14
    static void** s_vtableBase;    // PTR_LAB_00e36f0c

    // Destructor: cleans up children and removes from global list
    void __thiscall ~Entity();
};

// External helper to destroy a single child node (calls its destructor)
extern void destroyChild(ChildNode* child); // FUN_009c8eb0

void Entity::~Entity() {
    // Set vtable to the derived class (current level)
    this->vtable = s_vtableDerived; // PTR_FUN_00e36f14

    // Destroy the linked list of child objects
    ChildNode* curChild = this->childList; // +0x30
    while (curChild != nullptr) {
        ChildNode* nextChild = curChild->next; // ChildNode+0x04
        destroyChild(curChild);
        curChild = nextChild;
    }

    // Set vtable to base class (parent level)
    this->vtable = s_vtableBase; // PTR_LAB_00e36f0c

    // Remove this Entity from the global object list (singly linked)
    if (g_objectListHead == this) {
        // This is the head: update head to next
        g_objectListHead = this->next; // Entity+0x04
    } else {
        // Walk the list to find the predecessor
        Entity* prev = g_objectListHead;
        while (prev->next != this) { // prev->next at offset +0x04
            prev = prev->next;
        }
        // Unlink this node
        prev->next = this->next; // Entity+0x04
    }
}