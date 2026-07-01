// FUNC_NAME: BaseObject::BaseObject
// Function address: 0x00911810
// Role: Constructor for a base EA EARS object. Calls base initialization and conditionally calls a shutdown/cleanup routine if the flag's bit 0 is set.

// +0x0: vtable pointer (implied)
// Additional fields unknown without more context.

BaseObject* __thiscall BaseObject::BaseObject(BaseObject* this_ptr, byte flag) {
    // Call base class initialization (likely sets up vtable and default members)
    // This corresponds to callee FUN_00911190, probably a static init or a base constructor.
    baseInit(this_ptr); // or reinterpret_cast<BaseObject*>(0x00911190)(this_ptr)

    // If the lower bit of the flag is set, perform cleanup (possibly deallocation or resource release)
    if ((flag & 1) != 0) {
        shutdown(this_ptr); // corresponds to FUN_005c4480
    }

    // Return the constructed object pointer
    return this_ptr;
}