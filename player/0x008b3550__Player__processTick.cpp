// FUNC_NAME: Player::processTick
// Function at 0x008b3550 - Delegates update to state machine and movement controller, returns success flag
// __thiscall with player object in ecx
undefined4 __thiscall Player::processTick(Player *this) {
    // +0x30 = pointer to state machine (PlayerSM*)
    // +0x8 = pointer to movement controller (PlayerMovementController*)
    if ((this->stateMachine != (void *)0x0) && (this->movementController != (void *)0x0)) {
        // Call virtual function at vtable+4 (index 1) on stateMachine, which returns a pointer
        // Then call virtual function at vtable+0 (index 0) on that returned pointer
        (**(code **)*((undefined4 *)(**(code **)(*(int *)(this->stateMachine) + 4))()))();
        return 1;
    }
    return 0;
}