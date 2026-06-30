// FUNC_NAME: UnknownEARSClass::constructor
// Address: 0x004de110
// Role: Constructor for an EARS engine object. Calls base constructor and optionally invokes a cleanup/destruction function if a flag is set.
// The second parameter (param_2) likely indicates whether the object was dynamically allocated or requires special cleanup after construction.

int __thiscall UnknownEARSClass::constructor(int thisPtr, byte cleanupFlag) {
    // Call base class constructor (no additional parameters)
    FUN_004de130();
    
    // If the low bit of cleanupFlag is set, invoke cleanup/destruction on this object
    if ((cleanupFlag & 1) != 0) {
        FUN_009c8eb0(thisPtr);
    }
    
    // Return the constructed object (this)
    return thisPtr;
}