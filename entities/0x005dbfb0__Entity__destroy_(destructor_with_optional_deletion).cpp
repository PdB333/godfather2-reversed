// FUNC_NAME: Entity::destroy (destructor with optional deletion)

undefined4* __thiscall Entity::destroy(undefined4* this, byte param_2) {
    // Retrieve a cleanup function from the secondary vtable (offset +0x10 +0x04)
    code* cleanupFunc = *(code**)(this[4] + 4);
    // Set primary vtable to the first destruction placeholder
    *this = &PTR_FUN_00e3f2e0;
    // Invoke the internal cleanup handler (likely a virtual destructor thunk)
    cleanupFunc();
    // Call base class or component cleanup
    FUN_005de2f0(); // Entity::onDestroy? or Entity::stop
    // Update secondary vtable to the next destruction stage
    this[4] = &PTR_FUN_00e3f2e8;
    // Final cleanup step
    FUN_004de130(); // Entity::release?
    // Set primary vtable to the final destruction vtable
    *this = &PTR_LAB_00e3f2e4;
    // Clear global active flag (e.g., g_bEntityActive)
    DAT_01223508 = 0;
    // If bit 0 is set, free the memory
    if (param_2 & 1) {
        FUN_009c8eb0(this); // operator delete(this)
    }
    return this;
}