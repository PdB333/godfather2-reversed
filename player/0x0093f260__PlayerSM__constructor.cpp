// FUNC_NAME: PlayerSM::constructor
// Address: 0x0093f260
// Role: Constructor for PlayerSM state machine class. Initializes base class, sets up function tables, and zeroes state fields.

PlayerSM::PlayerSM(undefined4 param_2) {
    // Call base class initialization (likely a base state machine constructor)
    initializeBase(param_2);

    // Set vtable pointer
    this->vtable = &PTR_FUN_00d8b050;

    // Set additional function table pointers (state behavior tables)
    this->stateTable1 = &PTR_LAB_00d8b040;  // +0x3C
    this->stateTable2 = &PTR_LAB_00d8b03c;  // +0x48

    // Initialize state fields to zero
    this->field_0x50 = 0;           // +0x50
    *(short*)((char*)this + 0x54) = 0;  // +0x54
    *(short*)((char*)this + 0x56) = 0;  // +0x56
    this->field_0x58 = 0;           // +0x58
    this->field_0x5C = 0;           // +0x5C
    this->field_0x60 = 0;           // +0x60
    this->field_0x64 = 0;           // +0x64
    this->field_0x68 = 0;           // +0x68
    this->field_0x6C = 0;           // +0x6C
    this->field_0x70 = 0;           // +0x70
    this->field_0x74 = 0;           // +0x74
    this->field_0x78 = 0;           // +0x78
    this->field_0x7C = 0;           // +0x7C
    this->field_0x80 = 0;           // +0x80
    this->field_0x84 = 0;           // +0x84
    this->field_0x88 = 0;           // +0x88
}