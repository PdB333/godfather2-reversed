// FUNC_NAME: GameObject::~GameObject

// Destructor at 0x0069ad00
// Sets vtable to base class vtable, destroys child object at offset 0x14,
// then optionally deallocates memory if param_2 bit 0 is set.
// Calling convention: __thiscall
// Parameter: byte param_2 – flag indicating whether to free this object's memory

class GameObject {
public:
    // VTable entry at 0x00d5ce9c (base class vtable)
    void* m_vtable; // +0x00

    // +0x04 ... (other members)
    // +0x14 child object pointer (type unknown, but destructor is FUN_0069a0e0)
    void* m_pChildObject; // +0x14 (offset 0x14)

    // Destructor
    void __thiscall ~GameObject(byte doDelete) {
        // Step 1: Set vtable to base class vtable for proper destruction order
        m_vtable = (void*)&PTR_FUN_00d5ce9c;

        // Step 2: Destroy the child object at offset 0x14
        // FUN_0069a0e0 is the destructor for the child object
        FUN_0069a0e0(m_pChildObject); // likely calls child's destructor

        // Step 3: If flag is set, deallocate this object's memory
        if (doDelete & 1) {
            FUN_009c8eb0(this); // custom deallocation function
        }
    }

    // Static helper to invoke destructor from a pointer
    static void __thiscall destructor_wrapper(GameObject* obj, byte doDelete) {
        obj->~GameObject(doDelete);
    }
};