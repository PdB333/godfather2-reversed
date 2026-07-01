// FUNC_NAME: GameObject::~GameObject
// Address: 0x007aa930
// Destructor for a game object. Sets vtable to base class vtable (to avoid virtual calls during destruction),
// calls base destructor, and optionally frees heap-allocated memory.

class GameObject {
public:
    ~GameObject(unsigned char shouldFreeMemory);
};

// Implementation
void __thiscall GameObject::~GameObject(unsigned char shouldFreeMemory) {
    // Point vtable to the base class vtable (global table address)
    // +0x00: vtable pointer
    *(unsigned int**)this = &PTR_LAB_00d6b95c;  // vtable for base class

    // Call base class destructor
    FUN_0080ea60();  // likely BaseClass::~BaseClass()

    // If the object was allocated on the heap, free the memory
    if (shouldFreeMemory & 1) {
        FUN_00624da0(this);  // operator delete(this)
    }
}