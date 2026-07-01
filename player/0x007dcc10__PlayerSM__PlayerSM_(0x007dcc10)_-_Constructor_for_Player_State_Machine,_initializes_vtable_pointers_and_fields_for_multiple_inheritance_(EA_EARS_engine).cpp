// FUNC_NAME: PlayerSM::PlayerSM (0x007dcc10) - Constructor for Player State Machine, initializes vtable pointers and fields for multiple inheritance (EA EARS engine)
PlayerSM * __thiscall PlayerSM::PlayerSM(PlayerSM *this, uint param2) {
    // Base class initialization (likely EARSObject or similar)
    FUN_0046c590(param2);

    // Set up vtable pointers for this class and inherited interfaces
    this->field_0x50 = &PTR_LAB_00e32854;          // Temporary assignment
    this->vtable = &PTR_FUN_00d6f480;              // Primary vtable at +0x00
    this->field_0x3c = &PTR_LAB_00d6f470;          // Second vtable at +0x3c
    this->field_0x48 = &PTR_LAB_00d6f46c;          // Third vtable at +0x48
    this->field_0x50 = &PTR_LAB_00d6f468;          // Fourth vtable at +0x50

    // Class-specific initialization
    FUN_007dcae0();

    // Zero all state fields (timers, counters, flags)
    this->field_0xa8 = 0;                          // +0xa8 (0x2a*4)
    this->field_0xac = 0;                          // +0xac (0x2b*4)
    *(uint16 *)((uint8 *)this + 0xb0) = 0;         // +0xb0, short
    *(uint16 *)((uint8 *)this + 0xb2) = 0;         // +0xb2, short
    this->field_0xb4 = 0;                          // +0xb4 (0x2d*4)
    *(uint16 *)((uint8 *)this + 0xb8) = 0;         // +0xb8, short
    *(uint16 *)((uint8 *)this + 0xba) = 0;         // +0xba, short
    this->field_0xcc = 0;                          // +0xcc (0x33*4)
    this->field_0xdc = 0;                          // +0xdc (0x37*4)
    this->field_0xec = 0;                          // +0xec (0x3b*4)
    this->field_0xfc = _DAT_00d5780c;              // +0xfc, global initializer
    this->field_0x100 = 0;                         // +0x100 (0x40*4)

    // Second initialization pass
    FUN_007dcb50();
    this->field_0xa8 = 0;                          // Redundant zero

    return this;
}