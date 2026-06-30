// FUNC_NAME: EARSObject::~EARSObject

#include <cstdint>

// External helper functions identified from callees
extern void destroyComponent(void* ptr);    // FUN_0069a0e0 – destructor for member at +0x14
extern void deallocateObject(void* ptr);    // FUN_009c8eb0 – operator delete or custom deallocator

// VTable pointers (placeholders – actual symbols would be in the binary)
extern void* PTR_FUN_00d5cec4;  // first base class vtable
extern void* PTR_FUN_00d5ce9c;  // second base class vtable

class EARSObject {
public:
    // +0x00: vtable pointer
    void** vtable;

    // +0x14: pointer to a sub-object that must be destroyed
    void* m_pComponent;          // offset 0x14

    // +0x2C: pointer to second base class sub-object (e.g., another component)
    void* m_pSubObj2;            // offset 0x2C

    // +0x38: function pointer to destructor of m_pSubObj2 (from its vtable)
    void* m_pSubObj2Destructor;  // offset 0x38

    // +0x3C: pointer to first base class sub-object
    void* m_pSubObj1;            // offset 0x3C

    // +0x48: function pointer to destructor of m_pSubObj1 (from its vtable)
    void* m_pSubObj1Destructor;  // offset 0x48

    // Destructor
    // @param isDeallocating: if bit 0 is set, the object's memory is freed after destruction
    void* __thiscall ~EARSObject(uint8_t isDeallocating) {
        // Set vtable to first base class to ensure correct virtual dispatch during destruction
        this->vtable = &PTR_FUN_00d5cec4;

        // Destroy first sub-object (if present)
        if (this->m_pSubObj1 != 0) {
            auto destructor1 = (void (*)(void*))this->m_pSubObj1Destructor;
            destructor1(this->m_pSubObj1);
        }

        // Destroy second sub-object (if present)
        if (this->m_pSubObj2 != 0) {
            auto destructor2 = (void (*)(void*))this->m_pSubObj2Destructor;
            destructor2(this->m_pSubObj2);
        }

        // Switch vtable to second base class for its destruction phase
        this->vtable = &PTR_FUN_00d5ce9c;

        // Destroy the component member at +0x14
        destroyComponent(this->m_pComponent);

        // If the object should be deallocated, free its memory
        if ((isDeallocating & 1) != 0) {
            deallocateObject(this);
        }

        return this;
    }
};