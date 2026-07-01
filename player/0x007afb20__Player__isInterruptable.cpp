// FUNC_NAME: Player::isInterruptable
bool __thiscall Player::isInterruptable(void)
{
    // State machine pointer at offset +0x58 from the Player object
    int* stateMachine = *(int**)((int)this + 0x58);
    // Current state ID stored at offset +0x1010 within the state machine
    int currentStateID = *(int*)(stateMachine + 0x1010); // +0x1010: state ID
    // Check if this player is locally controlled (cVar2 = 0 means local? Unknown)
    bool isLocal = (FUN_004ac260() == 0); // Inverted? Original: if cVar2==0 then proceed
    // If the player is not local and the state is not in the allowed list,
    // then the character is not interruptable.
    // The following states are considered "busy" and block interruption:
    // 0, 5, 0x25, 8, 10, 0xC, 0xE, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C,
    // 0x54, 0x56, 0x58, 0x5A
    if (isLocal && (currentStateID != 0) && (currentStateID != 5) &&
        (currentStateID != 0x25) && (currentStateID != 8) &&
        (currentStateID != 10) && (currentStateID != 0xC) &&
        (currentStateID != 0xE) && (currentStateID != 0x10) &&
        (currentStateID != 0x12) && (currentStateID != 0x14) &&
        (currentStateID != 0x16) && (currentStateID != 0x18) &&
        (currentStateID != 0x1A) && (currentStateID != 0x1C) &&
        (currentStateID != 0x54) && (currentStateID != 0x56) &&
        (currentStateID != 0x58) && (currentStateID != 0x5A))
    {
        // For movement states (0x1F, 0x22, 0x2A, 0x2B), check if dialog is playing
        if (((currentStateID == 0x1F) || (currentStateID == 0x22) ||
             (currentStateID == 0x2A) || (currentStateID == 0x2B)) &&
            (FUN_007f7e90(0xFFFFFFFF) == 0))
        {
            return true; // Interruptable during movement if no dialog
        }
        return false; // Not interruptable in other states
    }
    // If local player, or blocked state, the character is interruptable (true)
    return true;
}