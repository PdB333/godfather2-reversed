// FUNC_NAME: Entity::~Entity
// Address: 0x004e4b80
// Role: Scalar deleting destructor for Entity class. Returns object to free list and optionally deallocates memory.

// Global object manager singleton (DAT_01206880)
static ObjectManager* g_objectManager = reinterpret_cast<ObjectManager*>(0x01206880);

// Offset +0x14 in ObjectManager: pointer to current free list slot (stack pointer)
// Static sentinel node for marking free list end (PTR_LAB_01123be8)
static void* const s_freeListSentinel = reinterpret_cast<void*>(0x01123be8);

// Custom memory deallocation routine
void __fastcall customDelete(void* ptr);

class Entity {
public:
    // Virtual function table pointer (offset +0x00)
    void** vtable;

    // Member fields at offset +0x10 and +0x14: linked list node pointers (or other pointers)
    void* nextNode; // offset +0x10 (param_1[4])
    void* prevNode; // offset +0x14 (param_1[5])

    // Destructor
    __thiscall Entity* __fastcall ~Entity(byte shouldDelete) {
        // Set vtable to base class vtable (static)
        this->vtable = reinterpret_cast<void**>(&PTR_FUN_00e37110);

        // If the nextNode pointer is non-null, return the node to the free list
        if (this->nextNode != 0) {
            // Get pointer to the free list current slot from the object manager
            void** pCurrentSlot = *reinterpret_cast<void***>(reinterpret_cast<char*>(g_objectManager) + 0x14);
            // Write sentinel at the current slot
            *pCurrentSlot = s_freeListSentinel;
            // Advance the slot pointer by 4 bytes
            *reinterpret_cast<char**>(reinterpret_cast<char*>(g_objectManager) + 0x14) += 4;
            // Write the old nextNode pointer into the new slot
            **reinterpret_cast<void***>(reinterpret_cast<char*>(g_objectManager) + 0x14) = this->nextNode;
            // Clear the node pointers
            this->nextNode = 0;
            this->prevNode = 0;
        }

        // If the destroy flag has bit 0 set, deallocate memory
        if ((shouldDelete & 1) != 0) {
            customDelete(this);
        }

        return this;
    }
};