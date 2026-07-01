// FUNC_NAME: GameObject::GameObject

undefined4 __thiscall GameObject::GameObject(GameObject *this, byte param_2) {
    // Initialize base class (likely Entity or similar)
    baseClassConstructor(this);
    
    // If the lowest bit of param_2 is set, allocate a subcomponent of size 0x1bc (444 bytes)
    // The allocation function (likely operator new or a memory pool allocator) returns a pointer
    // that is stored at a specific member offset (e.g., +0x00, depending on class layout)
    if ((param_2 & 1) != 0) {
        // Calls FUN_0043b960(this, 0x1bc) - interpreted as allocating memory and storing pointer
        allocSubcomponent(this, 0x1bc);  // e.g., create a physics or collision component
    }
    
    return this;
}