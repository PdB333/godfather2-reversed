// FUNC_NAME: Entity::updateInternalValue
// Function address: 0x006bab10
// Updates a cached value at +0x98 from a component pointer at +0x9c,
// guarded by a flag at +0x84 (bit 0). If the component exists and the flag is set,
// the value is copied from component's +0xac; otherwise set to 0.

void __thiscall Entity::updateInternalValue(void) {
    // Check if the component pointer is valid and the active flag is set
    if ((*(int*)((int)this + 0x9c) != 0) && ((*(byte*)((int)this + 0x84) & 1) != 0)) {
        // Copy the value from the component's field at +0xac
        *(int*)((int)this + 0x98) = *(int*)(*(int*)((int)this + 0x9c) + 0xac);
    } else {
        // Reset to zero if conditions fail
        *(int*)((int)this + 0x98) = 0;
    }
}