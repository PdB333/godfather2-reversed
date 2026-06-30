// FUNC_NAME: Entity::~Entity
// Destructor for Entity class at address 0x0066efa0
// Handles cleanup of sub-object and optional deallocation

#include <cstdint>

class Entity {
public:
    void** vtable;              // +0x00
    // ... other members ...
    void* m_pSubObject;         // +0xA1C (offset 0x287 * 4)
    // ... 
};

// External helper function (likely base class destructor or common cleanup)
extern void baseDestroy(void);

// Aligned free function
extern void __aligned_free(void* ptr);

// Vtable symbol
extern void* PTR_FUN_00e444d0;

Entity* __thiscall Entity::~Entity(Entity* this, byte deallocate)
{
    // Set vtable to this class's vtable
    this->vtable = &PTR_FUN_00e444d0;

    // If sub-object exists, call its virtual function at offset 0xC (likely release/shutdown)
    if (this->m_pSubObject != nullptr)
    {
        // Call function at vtable+0xC on sub-object (index 3 in vtable)
        void (**vtableFunc)(void) = *(void (***)(void))this->m_pSubObject;
        vtableFunc[3]();
    }

    // Call base class or common cleanup routine
    baseDestroy();

    // Free memory if deallocation flag is set (bit 0)
    if (deallocate & 1)
    {
        __aligned_free(this);
    }

    return this;
}