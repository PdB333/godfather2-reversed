// FUNC_NAME: PlayerSM::PlayerSM (Constructor for Player state machine)
void __fastcall PlayerSM::PlayerSM(PlayerSM* this)
{
    // Set vtable pointer at offset 0x00
    this->vtbl = &PTR_FUN_00d81bd0;
    // Set state table pointers at offsets 0x3C and 0x48
    this->stateTable1 = &PTR_LAB_00d81bc0;
    this->stateTable2 = &PTR_LAB_00d81bbc;
    // Initialize sub-object at offset 0x50 (this + 0x14 words)
    subObjectConstruct(this + 0x14);
    // Initialize three sub-component state machines at offsets 0x50, 0x58, 0x60
    subObjectInit(this + 0x14);
    subObjectInit(this + 0x16);
    subObjectInit(this + 0x18);
    // Global state machine initialization (e.g., register with manager)
    globalStateMachineInit();
}