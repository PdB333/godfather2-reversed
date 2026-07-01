// FUNC_NAME: Object::constructor
// Function address: 0x00816740
// Role: Constructor with optional initialization flag.
// param_2: byte flags – if bit 0 is set, calls additionalInit().

undefined4 __thiscall Object::constructor(undefined4 this, byte flags)
{
    // Call base initialization (likely virtual or global)
    FUN_00604da0(); // baseInit() – note: no explicit 'this' parameter, might be static or global

    // If the lowest bit of flags is set, perform additional setup
    if ((flags & 1) != 0) {
        FUN_009c8eb0(this); // additionalInit(this)
    }

    return this;
}