// FUNC_NAME: PlayerGroundSM::setCoverState
// Sets the ground state machine to cover state (state=9, substate=2) with given wall index.
void __thiscall PlayerGroundSM::setCoverState(int wallIndex) {
    // +0x10: main state (kState_Cover = 9)
    *(int *)(this + 0x10) = 9;
    // +0x14: cover substate (kCoverSubstate_High = 2)
    *(int *)(this + 0x14) = 2;
    // +0x18: cover wall/hint node index
    *(int *)(this + 0x18) = wallIndex;
}