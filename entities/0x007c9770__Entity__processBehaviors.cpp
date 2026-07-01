// FUNC_NAME: Entity::processBehaviors
void __thiscall Entity::processBehaviors() {
    char cVar1;
    int iVar2;

    // Clear flag bit 10 (0x400) - likely a "processing" or "active" flag for a behavior
    flags &= ~0x400;

    // Check if the entity is initialized (bit 0 set)
    if ((flags & 1) == 0) {
        // Query the state of the behavior component at offset 0x58
        iVar2 = getBehaviorState(*(undefined4*)(this + 0x58));
        if (iVar2 == 2) {
            // If behavior state is 2 (active/running) and bit 12 is not set
            if ((flags >> 0xc & 1) == 0) {
                startBehavior2(); // static/global helper to activate behavior
            }
            // Set flag bit 10 to mark behavior as active
            flags |= 0x400;
        }
    }

    // Update behavior state machine
    updateBehaviorState();
    // Update physics or animation
    updatePhysics();

    cVar1 = isDebugModeActive(); // global debug/toggle check
    if (cVar1 != '\0') {
        // Debug-specific update
        doDebugUpdate();
    }

    // Virtual method call on the behavior component at +0x58 (vtable slot 0x164)
    (**(code (__thiscall **)(int))(**(int**)(this + 0x58) + 0x164))();
}