// FUNC_NAME: EntityDataManager::addEntityFromFactory
// Function address: 0x005196f0
// Role: Inserts a new entity node into a doubly linked list managed by EntityDataManager.
// The factory (passed via ECX) creates the node, and then it's added at the head of the list.
// The EntityDataManager's head pointer is at offset 0x10.
// Entity nodes have next at +0xC4 (196) and prev at +0xC8 (200).

struct EntityNode {
    // ... other fields up to 0xC4
    EntityNode* next; // +0xC4
    EntityNode* prev; // +0xC8
    // ... possibly more after
};

struct EntityDataManager {
    // other fields...
    EntityNode* head; // +0x10 offset from this pointer (passed in ESI)
};

// Abstract factory with virtual create function at vtable index 1
struct EntityFactory {
    virtual EntityNode* create(/* param3, param4, param5, param6, param2 */) = 0; // vtable+4
};

// __thiscall? Actually this is a member of EntityDataManager, with this in ESI.
// ECX holds the factory, EDX is param2, stack has param3-6.
void __fastcall EntityDataManager::addEntityFromFactory(
    EntityFactory* factory,           // param_1 in ECX
    int param2,                       // param_2 in EDX (e.g., ID or type)
    int param3, int param4, int param5, int param6 // stack args passed to factory
)
{
    // ESI is the EntityDataManager's this pointer (unaff_ESI)
    EntityNode* newNode = factory->create(param3, param4, param5, param6, param2);
    if (newNode != nullptr)
    {
        newNode->prev = nullptr;     // +0xC8 = 200
        newNode->next = this->head;  // +0xC4 = next; this->head at +0x10
        if (this->head != nullptr)
        {
            this->head->prev = newNode; // Update old head's prev
        }
        this->head = newNode;         // New node becomes head
    }
}