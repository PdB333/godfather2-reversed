// FUNC_NAME: Player::updateCooldownTimer
// Address: 0x00872aa0
// Role: Decrements a cooldown timer and triggers an effect when the timer reaches zero (or each frame while active).
// The object's state at offset +0x64 must be non-zero and not equal to 0x48 (likely STATE_DEAD or STATE_INACTIVE).
// Each frame, it calls a global function (FUN_00724cf0) to retrieve a manager object, then calls a virtual method at vtable+0x2c
// on that manager with parameters (1, 1, 0, 1.0f, 1.0f) – possibly to spawn a visual effect or play a sound.

void __thiscall Player::updateCooldownTimer(int *thisPtr)
{
    int managerPtr;

    // Check if the current state is active (non-zero and not the special "inactive" state 0x48)
    if ((thisPtr[0x19] != 0) && (thisPtr[0x19] != 0x48)) {
        // Retrieve a manager object (e.g., GameManager, SceneManager, or VFXManager)
        managerPtr = FUN_00724cf0();
        // Decrement the cooldown timer at offset +0x70 (0x1c * 4)
        thisPtr[0x1c] = thisPtr[0x1c] - 1;
        // If the manager exists, call its virtual method at vtable offset 0x2c
        if (managerPtr != 0) {
            (*(void (__thiscall **)(int, int, int, int, float, float))(*(int *)managerPtr + 0x2c))
                (managerPtr, 1, 1, 0, 0x3f800000, 0x3f800000);
        }
    }
    return;
}