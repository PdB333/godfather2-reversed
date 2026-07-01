// FUNC_NAME: PlayerGroundSM::setCrouchState
// Address: 0x00875d10
// Role: Sets the crouching flag (bit 0x800 at +0xc88) and triggers animation/state updates

void __thiscall PlayerGroundSM::setCrouchState(PlayerGroundSM* this, bool enableCrouch)
{
    uint flags = *(uint*)((char*)this + 0xc88); // +0xc88: state flags bitfield
    uint animId;

    if (!enableCrouch) {
        // Clear crouch flag (bit 11 = 0x800)
        if ((flags & 0xfffff7ff) != flags) {
            // Notify state change (event type 0x10)
            (**(code**)(*(int*)((char*)this + 0x58) + 0x28))(0x10);
            *(uint*)((char*)this + 0xc88) = flags & 0xfffff7ff;
        }
        animId = DAT_00e2cd20; // Global crouch-to-stand animation ID
    } else {
        // Set crouch flag
        if ((flags | 0x800) != flags) {
            (**(code**)(*(int*)((char*)this + 0x58) + 0x28))(0x10);
            *(uint*)((char*)this + 0xc88) = flags | 0x800;
        }
        animId = 2; // Crouch animation ID
    }

    // Update animation state with the chosen animation ID
    FUN_0087f980(enableCrouch);

    // If there's an active animation controller at +0x360, play the animation
    if (*(int*)((char*)this + 0x360) != 0) {
        FUN_0055d7d0(animId);
    }
}