// FUNC_NAME: GameObject::GameObject
// Address: 0x004bee40
// Role: Constructor for a base game object (sets vtable and secondary pointer, then calls base init)

#include <cstddef>

// Forward declaration of external vtable and label pointers
extern void* s_GameObjectVTable;     // &PTR_FUN_00e35d30
extern void* s_GameObjectLabel;      // &PTR_LAB_00e35d78

// Class definition with documented offsets
class GameObject {
public:
    void** m_vtbl;                    // +0x00: Virtual function table pointer
    void*  m_pSecondary;              // +0x04: Secondary pointer (another vtable or class info)
    // ... further members follow

    __thiscall GameObject(void);
    // ... other methods
};

// Define the called base initializer (likely from derived class or object system)
extern void __thiscall __vectorcall FUN_00567a20(GameObject* this);

// Constructor implementation
__thiscall GameObject::GameObject(GameObject *this) {
    // Assign virtual function table (first pointer at offset 0)
    this->m_vtbl = (void**)&s_GameObjectVTable;
    // Assign secondary pointer (offset 4), likely another vtable for multiple inheritance
    this->m_pSecondary = (void*)&s_GameObjectLabel;
    // Call base class initializer (e.g., EARSObject or Entity)
    FUN_00567a20(this);
}