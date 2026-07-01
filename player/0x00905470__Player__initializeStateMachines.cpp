//FUNC_NAME: Player::initializeStateMachines
void __fastcall Player::initializeStateMachines(Player* this)
{
    // Global initialization for state machine system
    FUN_00564eb0(0);
    FUN_00564bf0();

    // Initialize each player state machine sub-object
    // Offsets: +0x04 = PlayerGroundSM, +0x218 = PlayerWallCoverSM,
    //          +0x43c = PlayerF2FSM, +0x65c = PlayerGrappleSM
    FUN_00564d20(this + 0x04);      // PlayerGroundSM constructor
    FUN_00564d20(this + 0x218);     // PlayerWallCoverSM constructor
    FUN_00564d20(this + 0x43c);     // PlayerF2FSM constructor
    FUN_00564d20(this + 0x65c);     // PlayerGrappleSM constructor
}