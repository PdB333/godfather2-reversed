// FUNC_NAME: EARSObject::constructor
// Address: 0x0091d770
// Role: Constructor that calls a global initialization routine (likely base class setup) and then conditionally invokes a cleanup/destructor function if the flag's lowest bit is set.
//       The flag (param_2) likely indicates whether the object was heap-allocated or requires special handling.

undefined4 __thiscall EARSObject::constructor(EARSObject* this, byte flags)
{
    // Call the common initialization function (probably sets up vtable, default members, etc.)
    FUN_005c16e0();

    // If the low bit of flags is set, call the cleanup routine (possibly a destructor or memory release)
    if ((flags & 1) != 0) {
        FUN_005c4480(this);
    }

    return (undefined4)this;
}