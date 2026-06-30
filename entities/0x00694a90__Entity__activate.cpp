// FUNC_NAME: Entity::activate
// Function address: 0x00694a90
// This function calls an internal initialization helper and returns the object pointer for chaining.
// The helper function at 0x00694060 likely performs internal setup (e.g., state flag setting, resource acquisition).
__thiscall Entity* Entity::activate(void) {
    // Call internal helper function
    internalInitHelper();
    return this;
}