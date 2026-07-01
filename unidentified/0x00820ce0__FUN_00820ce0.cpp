// FUNC_NAME: SomeClass::~SomeClass

// Destructor for an unknown class (likely from EARS engine).
// Address: 0x00820ce0
// Parameters:
//   this - pointer to object being destroyed
//   deletingFlag - if bit 0 set, operator delete is called after destruction

undefined4 * __thiscall SomeClass::~SomeClass(undefined4 *this, byte deletingFlag)
{
    int *memberPtr; // pointer to member at offset +0x2c

    memberPtr = (int *)(this + 0x2c); // +0x2c: pointer to some allocated resource

    // Set vtable to first base class vtable
    *this = &PTR_FUN_00d73398;

    // Release the resource if it exists
    if (*memberPtr != 0) {
        FUN_004daf90(memberPtr); // release function
        *memberPtr = 0;
    }

    // Redundant check (always false after above)
    if (*memberPtr != 0) {
        FUN_004daf90(memberPtr);
    }

    // Set vtable to root base class vtable
    *this = &PTR_LAB_00e32854;

    // If deleting flag is set, call operator delete
    if ((deletingFlag & 1) != 0) {
        memberPtr = (int *)FUN_009c89b0(); // get memory manager or operator delete
        (**(code **)(*memberPtr + 4))(this, 0); // call delete via vtable
    }

    return this;
}