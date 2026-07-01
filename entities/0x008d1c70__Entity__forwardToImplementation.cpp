// FUNC_NAME: Entity::forwardToImplementation
void __thiscall Entity::forwardToImplementation(Entity* this) {
    // This function is a simple thunk that delegates to another implementation.
    // It likely overrides a virtual method and forwards the call to the base class
    // or a helper function at address 0x008d5d40.
    FUN_008d5d40(this);  // calls the actual implementation (0x008d5d40)
    return;
}