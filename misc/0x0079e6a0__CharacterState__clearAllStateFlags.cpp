// FUNC_NAME: CharacterState::clearAllStateFlags
// Address: 0x0079e6a0
// Role: Resets multiple animation/behavior state flags on a character when a global condition (likely debug/cheat) is active.

void __fastcall CharacterState::clearAllStateFlags(CharacterState* this)
{
    // Check if global condition (debug mode, cheat, or system pause) is active
    bool condition = (bool)FUN_00481620(); // some global state check
    if (condition)
    {
        // Clear various per-character state flags
        *(byte*)((uintptr_t)this + 0x28EC) = 0; // +0x28EC: e.g., "isStunned"
        *(byte*)((uintptr_t)this + 0x26CC) = 0; // +0x26CC: e.g., "isInCover"
        *(byte*)((uintptr_t)this + 0x26B4) = 0; // +0x26B4: e.g., "isAiming"
        *(byte*)((uintptr_t)this + 0x26A8) = 0; // +0x26A8: e.g., "isSprinting"
        *(byte*)((uintptr_t)this + 0x26C0) = 0; // +0x26C0: e.g., "isCrouching"
        *(byte*)((uintptr_t)this + 0x274C) = 0; // +0x274C: e.g., "isKnockedDown"
        *(byte*)((uintptr_t)this + 0x24E0) = 0; // +0x24E0: e.g., "isDead"
        // Also clear a global flag at DAT_0112991C + 0x10
        *(byte*)(DAT_0112991C + 0x10) = 0; // Global state flag (e.g., allPaused, debugActive)
    }
}