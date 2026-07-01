// FUNC_NAME: GameObject::~GameObject
// Destructor for a game object. Swaps vtable to a destructing vtable,
// releases child object at offset 0xC if present, then sets vtable to base class vtable.
// Address: 0x008ca450
class GameObject {
    // +0x00: pointer to virtual function table
    void* m_vtable;
    // ... other members ...
    // +0x0C: pointer to child object or resource handle
    void* m_childPtr;
    // ... rest of object ...
};

__thiscall GameObject::~GameObject() {
    // Switch to destructing vtable (prevents virtual calls during cleanup)
    this->m_vtable = &PTR_FUN_00d7bf50;

    // If child pointer is valid, release it
    if (this->m_childPtr != nullptr) {
        FUN_009f01a0(); // releases the child object / resource
    }

    // Restore vtable to base class vtable (for correct inheritance cleanup)
    this->m_vtable = &PTR_LAB_00e2f638;
}