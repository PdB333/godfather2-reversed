// FUNC_NAME: PlayerWallCoverSM::updateTimerAndActions
void __thiscall PlayerWallCoverSM::updateTimerAndActions(PlayerWallCoverSM *this, float deltaTime)
{
    int iVar1;

    // Check if update is allowed: flag bit 0 must be clear and state must not be 1
    if (((*(byte *)((uintptr_t)this + 0x3ca) & 1) == 0) && (*(int *)((uintptr_t)this + 0x3cb) != 1)) {
        // Update some subsystems (e.g., animation, physics) with delta time
        FUN_00866820(deltaTime);
        FUN_00869720(deltaTime);

        // Decrement the cooldown timer (if positive)
        if (0.0f < *(float *)((uintptr_t)this + 0x3c9)) {
            *(float *)((uintptr_t)this + 0x3c9) = *(float *)((uintptr_t)this + 0x3c9) - 0.0166666675f; // ~60 fps frame time
        }

        // If timer just expired (was positive but now <= 0), trigger action
        if ((*(float *)((uintptr_t)this + 0x3c9) <= 0.0f) && (*(float *)((uintptr_t)this + 0x3c9) != 0.0f)) {
            // Check flag bit 12 -> trigger "enter cover" or similar
            if (((uint) * (uint *)((uintptr_t)this + 0x3ca) >> 0xc & 1) != 0) {
                // Obtain a pointer from a global manager, possibly the player controller
                if (*(int **)(DAT_012233a0 + 4) == (int *)0x0) {
                    iVar1 = 0;
                } else {
                    iVar1 = *(int *)(*(int *)(DAT_012233a0 + 4)) + -0x1f30;
                }
                // Call virtual function at vtable offset 0x2c4 (index 0xB1)
                (**(code **)(*(uintptr_t *)this + 0x2c4))(iVar1);
                // Clear flag bit 12
                *(uint *)((uintptr_t)this + 0x3ca) = *(uint *)((uintptr_t)this + 0x3ca) & 0xffffefff;
                return;
            }
            // Check flag bit 13 -> trigger "exit cover" or similar
            if (((uint) * (uint *)((uintptr_t)this + 0x3ca) >> 0xd & 1) != 0) {
                // Call virtual function at vtable offset 0x298 (index 0xA6)
                (**(code **)(*(uintptr_t *)this + 0x298))();
                // Clear flag bit 13
                *(uint *)((uintptr_t)this + 0x3ca) = *(uint *)((uintptr_t)this + 0x3ca) & 0xffffdfff;
            }
        }
    }
    return;
}