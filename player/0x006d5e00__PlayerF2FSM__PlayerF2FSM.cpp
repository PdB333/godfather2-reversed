// FUNC_NAME: PlayerF2FSM::PlayerF2FSM
void __fastcall PlayerF2FSM::PlayerF2FSM(PlayerF2FSM* this) {
    // Set vtable pointer for PlayerF2FSM (0x00d5f42c)
    *this = &PTR_FUN_00d5f42c;

    // Initialize state machine data at offsets 0x3C and 0x48
    this->field_0x3C = &PTR_LAB_00d5f41c;   // likely parent state pointer
    this->field_0x48 = &PTR_LAB_00d5f418;   // likely transition table pointer

    // Initialize base class subobject at offset 0x14 (e.g., FSMBase)
    FUN_004086d0(&this->fsmBase);
    FUN_00408310(&this->fsmBase);

    // Global state machine registration/init
    FUN_0046c640();
}