// FUNC_NAME: PlayerSM::PlayerSM
PlayerSM* __thiscall PlayerSM::PlayerSM(PlayerSM* this, int playerIndex)
{
    int playerId;

    if (playerIndex == 0) {
        playerId = 0;
    } else {
        playerId = FUN_00481610(); // retrieve player object ID from index
    }
    FUN_0064d390(1, 1); // memory or subsystem init (e.g., debug tracker)
    this->baseVtable = (void*)0x00e317dc; // base class vtable pointer
    this->field_0x18 = 0; // +0x18: flags or timer
    FUN_00454a10(playerId); // associate player ID with this state machine
    this->field_0x24 = 2; // +0x24: initial state type (e.g., 2 = idle)
    this->vtable = (void*)0x00d6a988; // derived class vtable pointer
    this->field_0x34 = 0; // +0x34: pointer to next state instance
    this->field_0x28 = (void*)0x00d6a754; // +0x28: interface/behavior vtable
    this->field_0x30 = (void*)0x0079b120; // +0x30: state machine callback
    FUN_004a8ec0(0); // final initialization step
    this->field_0x14 = &this->field_0x28; // +0x14: self-pointer to embedded subobject at +0x28
    return this;
}