// FUNC_NAME: Entity::~Entity
// Destructor at 0x007d5480 – handles child object cleanup and memory deallocation

#include <cstddef>

class Entity {
public:
    void* vtable;            // +0x00 vtable pointer
    // ... other members ...
    void* mChildObject;      // +0x24 (param_1[9]) pointer to a child sub‑object

    // Virtual destructor implemented here
    virtual ~Entity();
};

// External functions called during destruction
extern void destroySubObject(void* obj);              // 0x009e7530
extern void finalizeSubObjectCleanup();               // 0x009f01a0
extern void operatorDelete(void* ptr);                // 0x009c8eb0

// External vtable symbols
extern void* PTR_FUN_00d6efa0;   // base class vtable
extern void* PTR___purecall_00e407a4; // purecall vtable (prevents double deletion)

// __thiscall destructor reconstruction
void* __thiscall Entity::~Entity(Entity* this, byte flags) {
    // Set vtable to base class version
    this->vtable = &PTR_FUN_00d6efa0;

    // If a child object exists, clean it up
    if (this->mChildObject != nullptr) {
        // If child object has an internal pointer at offset +0x08, destroy it
        if (*(void**)((char*)this->mChildObject + 8) != nullptr) {
            destroySubObject(this->mChildObject);
        }
        // Finalize any remaining child cleanup (e.g., release resources)
        finalizeSubObjectCleanup();
    }

    // Set vtable to purecall to catch accidental post‑destruction calls
    this->vtable = &PTR___purecall_00e407a4;

    // If the `flags` low bit is set, deallocate memory
    if ((flags & 1) != 0) {
        operatorDelete(this);
    }

    return this;
}