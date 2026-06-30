// FUNC_NAME: ObjectBase::constructor
// Address: 0x0046e890
// Calls base constructor FUN_0046ea20, then conditionally calls a virtual initialization method if param_2's bit 0 is set.

undefined4 __thiscall ObjectBase::constructor(void* this, byte initFlags) {
    // Call base class constructor (presumably sets up vtable and base members)
    FUN_0046ea20(); // Base constructor

    // If the low bit of initFlags is set, call the virtual initialization function
    if ((initFlags & 1) != 0) {
        // Dereference global pointer at g_someGlobalData+0x2d4 to get a vtable pointer,
        // then call the second virtual function (offset +4) with (this, 0)
        (**(code**)(**(int**)(DAT_01223410 + 0x2d4) + 4))(this, 0);
    }

    return this; // Return the constructed object pointer
}