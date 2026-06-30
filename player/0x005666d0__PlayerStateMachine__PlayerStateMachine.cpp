// FUNC_NAME: PlayerStateMachine::PlayerStateMachine
void __fastcall PlayerStateMachine::PlayerStateMachine(PlayerStateMachine* this, Player* owner)
{
    // Offset +0x00: First vtable pointer (base class 1)
    this->vtableBase1 = &PTR_FUN_00e3a7a8;
    // Offset +0x04: Second vtable pointer (base class 2, initially set)
    this->vtableBase2 = &PTR_LAB_00e3a840;
    // Global static pointer to this instance (likely the active state machine)
    DAT_012234b8 = this;
    // Offset +0x28 (10*4): Store owner (passed as param_1)
    this->owner = owner;
    // Re-set first vtable (maybe from base constructor?)
    this->vtableBase1 = &PTR_FUN_00e3a7a8;
    // Override second vtable to final derived class table
    this->vtableBase2 = &PTR_LAB_00e3a844;
    // Zero out several flags/counters
    this->field_08 = 0;   // +0x08
    this->field_0C = 0;   // +0x0C
    this->field_1C = 0;   // +0x1C (7*4)
    this->field_20 = 0;   // +0x20 (8*4)
    this->field_24 = 0;   // +0x24 (9*4)
    // Buffer capacity (number of entries)
    this->bufferCapacity = 0x14;  // +0x2C (11*4)
    // More zeroed fields
    this->field_30 = 0;   // +0x30 (12*4)
    this->field_34 = 0;   // +0x34 (13*4)
    this->field_38 = 0;   // +0x38 (14*4)
    this->field_3C = 0;   // +0x3C (15*4)
    this->field_40 = 0;   // +0x40 (16*4)
    this->field_44 = 0;   // +0x44 (17*4)
    this->field_48 = 1;   // +0x48 (18*4) - some active flag
    this->field_4C = 0;   // +0x4C (19*4)
    this->field_50 = 0;   // +0x50 (20*4)
    this->field_54 = 0;   // +0x54 (21*4)
    this->field_58 = 0;   // +0x58 (22*4)

    // Call base class constructor (likely part of base1)
    FUN_00ae9710();

    // Additional fields initialized after base constructor
    this->field_11C = 0;  // +0x11C (0x47*4)
    this->field_120 = 0;  // +0x120 (0x48*4)
    this->field_10 = 0;   // +0x10 (4*4)
    // Zero a single byte at offset +0x14 (5*4)
    *(byte*)(&this->field_14) = 0;
    // Set buffer size in elements (0x80 = 128)
    this->bufferElementSize = 0x80;  // +0xEC (0x3B*4)

    // Call another initialization function
    FUN_00adbf50();

    // Set pointer to internal buffer (offset +0x5C = 0x17*4)
    this->bufferPtr = &this->bufferStorage;  // +0xE8 (0x3A*4)
    // Mark state machine as active
    this->isActive = 1;  // +0x114 (0x45*4)

    // Call a virtual function on the owner (offset +0x08 in owner's vtable)
    // Probably an 'update' or 'attach' method
    (owner->vtable->func8)(owner);

    // Register a callback/function pair for later use
    thunk_FUN_00aedbc0(FUN_005677c0, &LAB_005677f0);
    // Perform additional registration/initialization
    thunk_FUN_00af0c90();

    // Allocate a new object from a factory and call its constructor with args (0,0)
    void* newObj = FUN_00ad8270();
    (**(void(**)(void*,uint,uint))newObj)(newObj, 0, 0);
}