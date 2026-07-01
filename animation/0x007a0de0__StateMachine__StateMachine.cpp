// FUNC_NAME: StateMachine::StateMachine
// Reconstructed constructor for a state machine object (EARS engine, Godfather 2)
// Sets up vtable (base then derived), state function tables, and initialization flags
// param1: this pointer
// param2: flag indicating whether to auto-create a sub-object (e.g., an initial state data)
undefined4 * __thiscall StateMachine::StateMachine(StateMachine* this, int autoCreate) {
    undefined4 subObject;

    // If autoCreate is true, allocate a sub-object; otherwise null
    if (autoCreate == 0) {
        subObject = 0;
    } else {
        subObject = FUN_00481610();  // Allocate/create sub-object (e.g., initial state data)
    }

    // Global initialization call (likely memory or system related)
    FUN_0064d390(1, 1);

    // Set base class vtable (will be overwritten by derived vtable below)
    this->vtable = (void*)PTR_LAB_00e317dc;         // +0x00 Base vtable pointer
    this->stateId = 0;                               // +0x18 Initialize state ID (initial state)
    FUN_00454a10(subObject);                         // Base class initialization with sub-object

    this->stateCount = 1;                            // +0x24 Number of states or enable flag
    // Overwrite vtable with derived class vtable
    this->vtable = (void*)PTR_LAB_00d6a9b4;         // +0x00 Derived vtable pointer

    this->field_0x34 = 0;                            // +0x34 Unknown field, zeroed
    this->stateFunctionTable = &PTR_LAB_00d6a76c;   // +0x28 Pointer to array of state function pointers
    this->currentStateFunction = &LAB_0079b190;     // +0x30 Pointer to current state's update function (initial state)

    FUN_004a8ec0(0);                                 // Derived class specific initialization

    // List pointer points to the state function table (self-referencing)
    this->listPointer = (int*)(this + 10);           // +0x14 Points to offset 0x28 (address of stateFunctionTable)

    return this;
}