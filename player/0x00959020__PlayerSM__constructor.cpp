// FUNC_NAME: PlayerSM::constructor
//
// Constructor for the PlayerSM class (player state machine).
// Address: 0x00959020
// Sets up multiple virtual function tables, initializes base class,
// and resets a global counter.

void __fastcall PlayerSM::constructor(PlayerSM *this)
{
    // Set primary vtable (main class virtual functions)
    *(void **)this = (void *)&PTR_FUN_00d8c6c8;

    // Set secondary vtable (base class or interface) at offset +0x10
    *(void **)((char *)this + 0x10) = &PTR_LAB_00d8c6a4;

    // Set another vtable at offset +0x4C
    *(void **)((char *)this + 0x4C) = &PTR_LAB_00d8c6a0;

    // Call base class constructor (e.g., StateMachine::constructor)
    // This takes a pointer to the base subobject (this+0x10), a label, and a flag
    FUN_005c02f0((char *)this + 0x10, &LAB_00959010, 1);

    // Set multiple vtable slots to a common default vtable (0x00d83b18)
    // Offsets: +0x210, +0x18C, +0x108, +0x84
    *(void **)((char *)this + 0x210) = &PTR_LAB_00d83b18; // param_1[0x84]
    *(void **)((char *)this + 0x18C) = &PTR_LAB_00d83b18; // param_1[99] => 0x63*4=0x18C
    *(void **)((char *)this + 0x108) = &PTR_LAB_00d83b18; // param_1[0x42] => 0x42*4=0x108
    *(void **)((char *)this + 0x84)  = &PTR_LAB_00d83b18; // param_1[0x21] => 0x21*4=0x84

    // Reset the vtable at offset +0x4C to a different pointer
    *(void **)((char *)this + 0x4C) = &PTR_LAB_00d8c4e0;

    // Global counter or reference to singleton, initialize to 0
    DAT_011304fc = 0;

    // Call additional initialization routine
    FUN_005c16e0();
}