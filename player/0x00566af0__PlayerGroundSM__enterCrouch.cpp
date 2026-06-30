//FUNC_NAME: PlayerGroundSM::enterCrouch
// Address: 0x00566af0
// Role: Attempt to transition into crouch state from ground state machine.
// Checks flags at +0x2C: bit4 (canCrouch), bit2 (isCrouching), bit7 (isSprinting), bit6 (crouchTransition).
// Sets state ID at +0x10 to 1, clears substate at +0x14, and sets bit6.

bool __fastcall PlayerGroundSM::enterCrouch(PlayerGroundSM* this) {
    uint flags = *(uint*)((int)this + 0x2C); // +0x2C: state flags
    bool result = false;

    // Condition: not already in crouch transition (bit6=0), can crouch (bit4=1),
    // and either already crouching (bit2=1) OR sprinting with no movement (bit7=1 and +0x20==0)
    if (((flags >> 6 & 1) == 0) && ((flags >> 4 & 1) != 0) &&
        ((flags >> 2 & 1) != 0 || ((flags >> 7 & 1) != 0 && *(int*)((int)this + 0x20) == 0))) {
        *(byte*)((int)this + 0x14) = 0; // +0x14: substate (clear)
        *(uint*)((int)this + 0x2C) |= 0x40; // set bit6 (crouch transition)
        *(int*)((int)this + 0x10) = 1; // +0x10: state ID (crouch)
        if (*(int*)((int)this + 0x0C) == 0) { // +0x0C: owner pointer (e.g., Player)
            FUN_00566d90(); // initialize crouch resources
        }
        FUN_00566e90(); // apply crouch state
        result = true;
    }
    return result;
}