// FUNC_NAME: GameObject::constructor
GameObject* __thiscall GameObject::constructor(GameObject* this, byte flags) {
    // Call base class constructor (likely sets vtable, initializes base fields)
    this->baseConstructor(); // FUN_005026d0
    
    // If the 'flags' parameter has bit 0 set, perform an additional action.
    // Based on the callee address (0x009c8eb0), this could be a memory deallocation
    // or a registration with a manager. Since 'this' is returned afterward,
    // deallocation seems unlikely; it's more probable that this registers the
    // object with a game-world list, triggers post-construction setup, etc.
    if (flags & 1) {
        this->postConstruct(); // FUN_009c8eb0 – exact purpose unknown; likely registers or finalizes object
    }
    
    return this;
}