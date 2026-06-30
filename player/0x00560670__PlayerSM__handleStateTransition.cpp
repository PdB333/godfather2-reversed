// FUNC_NAME: PlayerSM::handleStateTransition
// Address: 0x00560670
// Role: Handles state transitions for the player state machine.
// Called from: 0x0055d870
// Structure offsets:
//   +0x10c: int mState (1=Air, 2=Ground)
//   +0x110: uint mFlags (bit2 = pendingAction, bit3 = otherFlag)
//   +0xd4:  int mOnGround (non-zero when grounded)

void __fastcall PlayerSM::handleStateTransition(int param1)
{
    int state = *(int*)((char*)this + 0x10c);
    uint flags = *(uint*)((char*)this + 0x110);
    int onGround = *(int*)((char*)this + 0xd4);

    if (state == 2) // Ground state
    {
        // Transition out of ground if:
        // - bit2 (pending action) set, or
        // - not on ground, or
        // - bit3 (other condition) set
        if (((flags >> 2) & 1) != 0 || onGround == 0 || ((flags >> 3) & 1) != 0)
        {
            FUN_005606c0(param1);   // applyStateAction
            FUN_00560b30();         // clearTransitionFlags
            // Clear pending action flag
            *(uint*)((char*)this + 0x110) &= ~(1 << 2);
        }
    }
    else if (state == 1) // Air state
    {
        FUN_005606c0(param1);   // applyStateAction
    }
}