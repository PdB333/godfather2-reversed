// FUNC_NAME: BaseClass::BaseClass
// Constructor for a base class with optional self-deletion flag.
// Address: 0x00567e30
undefined4 * __thiscall BaseClass::BaseClass(undefined4 *this, byte deleteFlag)
{
    // Set vtable pointer (PTR_FUN_00e3a9cc points to BaseClass's vtable)
    this[0] = &PTR_FUN_00e3a9cc;
    // Call base class constructor (FUN_00ad9db0)
    BaseClass::BaseClassBase();
    // If deleteFlag's lowest bit is set, destroy this object
    if ((deleteFlag & 1) != 0) {
        BaseClass::~BaseClass(); // FUN_009c8eb0 - destructor or deallocation
    }
    return this;
}