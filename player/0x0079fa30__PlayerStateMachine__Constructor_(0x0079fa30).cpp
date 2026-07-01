// FUNC_NAME: PlayerStateMachine::Constructor (0x0079fa30)
// Initializes a state machine object with two-stage vtable setup,
// sets default state to 1, installs a state function pointer,
// and links an embedded list node to itself.

undefined4 * __thiscall PlayerStateMachine::Constructor(undefined4 *this, int doAllocate)
{
    undefined4 allocResult;
    
    if (doAllocate == 0) {
        allocResult = 0;
    }
    else {
        allocResult = FUN_00481610();  // allocate subsystem or handle
    }
    FUN_0064d390(0, 1);                // debug/log initialization (params: flags?)
    this[0] = &PTR_LAB_00e317dc;       // base vtable (e.g., EARS::StateMachine)
    this[6] = 0;                       // +0x18 clear base field
    FUN_00454a10(allocResult);         // register allocResult with manager
    this[9] = 1;                       // +0x24 default state value (e.g., kStateIdle)
    this[0] = &PTR_LAB_00d6a7fc;       // override vtable to derived class
    this[10] = &PTR_LAB_00d6a6ac;      // +0x28 secondary vtable (interface, e.g., ITicked)
    this[0xd] = 0;                     // +0x34 clear
    this[0xc] = &LAB_0079b140;         // +0x30 state function pointer (e.g., updateFunction)
    *(byte *)(this + 0xf) = 1;         // +0x3C byte flag (e.g., isActive = true)
    this[0x10] = 0;                    // +0x40 clear
    this[0x11] = 0;                    // +0x44 clear
    this[0x12] = 0;                    // +0x48 clear
    this[5] = this + 10;               // +0x14 self-link to embedded list node at +0x28
    return this;
}