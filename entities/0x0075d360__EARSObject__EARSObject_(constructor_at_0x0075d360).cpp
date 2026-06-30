// FUNC_NAME: EARSObject::EARSObject (constructor at 0x0075d360)
// takes a flag byte; bit 0 indicates additional initialization via FUN_00624da0
// FUN_0075cc50 is likely the base class constructor or common initialization

void __thiscall EARSObject::EARSObject(byte flags) {
    // Call base initialization (e.g., base class constructor or internal setup)
    // This is likely the core initialization routine (FUN_0075cc50)
    // Possibly calls other virtual or base class constructors
    FUN_0075cc50();  // base init

    // If the low bit of flags is set, perform additional setup
    // This extra step (FUN_00624da0) might register the object with a manager,
    // allocate resources, or set a flag indicating the object is "active"
    if (flags & 1) {
        FUN_00624da0(this);
    }
}