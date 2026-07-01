// FUNC_NAME: Entity::setupStartState
void __thiscall Entity::setupStartState(int propertyValue, int propertyArg) {
    // Call initialization subroutines (order matters for state setup)
    performPreInit();
    configureResources();
    applyProperty(2, propertyValue, propertyArg, 1);

    // Set persistent flag at offset 0x10 (bit 0x1000 = active state)
    *(uint *)(this + 0x10) = *(uint *)(this + 0x10) | 0x1000;

    // Finalize post-setup logic
    finalizeStart();
}