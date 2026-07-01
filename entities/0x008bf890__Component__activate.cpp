// FUNC_NAME: Component::activate
// Function address: 0x008bf890
// Role: Activates a component by setting a flag and initializing a sub-component.

void __thiscall Component::activate(Component* this) {
    // Check if bit 5 (0x20) is not set in flags at offset +0x84
    if ((*(uint*)((uintptr_t)this + 0x84) >> 5 & 1) == 0) {
        // Set bit 5 to mark as active
        *(uint*)((uintptr_t)this + 0x84) |= 0x20;
        // Call initialization/reset on sub-component at offset +0x54 with parameter 0
        // FUN_006b08c0 is likely a reset/init function for the sub-component
        subComponentInit(*(void**)((uintptr_t)this + 0x54), 0);
    }
}