// FUNC_NAME: Entity::checkAndStopState
// Function address: 0x004e6720
// Role: Conditional stop of a component based on state fields at +0x44 and +0x48.
// Calls FUN_004ebc00 (likely stopSomething) with pointer at +0x4 and argument 0.

void __thiscall Entity::checkAndStopState(void)
{
    // +0x44: state field (expected 1)
    // +0x48: substate field (expected 0)
    if (*(int *)(this + 0x44) != 1 || *(int *)(this + 0x48) != 0) {
        // +0x4: pointer to another object (e.g., component or controller)
        stopSomething(*(int *)(this + 4), 0);  // FUN_004ebc00
    }
}