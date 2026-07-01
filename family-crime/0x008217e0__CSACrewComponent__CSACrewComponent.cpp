//FUNC_NAME: CSACrewComponent::CSACrewComponent
// Address: 0x008217e0
// Constructor for CSACrewComponent. Initializes base class, sets vtable, and initializes debug sentinel fields.
// The second parameter (param2) is passed to an initialization function.

undefined4* __thiscall CSACrewComponent::CSACrewComponent(undefined4* this, undefined4 param2)
{
    // Call base class constructor
    FUN_008334a0();  // BaseClass::BaseClass()

    // Set vtable pointer
    *this = &PTR_FUN_00d73398;  // vtable for CSACrewComponent

    // Initialize debug sentinel fields at offsets 0xA0, 0xA4, 0xA8, 0xAC
    this[0x28] = 0xbadbadba;  // +0xA0: uninitialized marker
    this[0x29] = 0xbeefbeef;  // +0xA4: uninitialized marker
    this[0x2a] = 0xeac15a55;  // +0xA8: uninitialized marker
    this[0x2b] = 0x91100911;  // +0xAC: uninitialized marker

    // Initialize fields at offsets 0xB0 and 0xB4 to zero
    this[0x2c] = 0;  // +0xB0: some pointer or count
    this[0x2d] = 0;  // +0xB4: some pointer or count

    // Call additional initialization functions
    FUN_008202d0();  // initComponent()
    FUN_008212c0(param2);  // initWithParam(param2)

    return this;
}