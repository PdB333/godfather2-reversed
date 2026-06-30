// FUN_00486340: BaseObject::BaseObject(byte flags)
undefined4 __thiscall BaseObject::BaseObject(byte flags) {
    // Call base class or common initialization (likely sets vtable, clears members, etc.)
    BaseObject::init(); // FUN_00486360 - no parameters; assumes this is implicit

    // If the low bit of flags is set, perform additional cleanup or destruction
    // This pattern is used for objects that may need immediate cleanup after construction
    // (e.g., temporary objects in EA's EARS engine)
    if ((flags & 1) != 0) {
        BaseObject::cleanup(); // FUN_009c8eb0 - likely deallocates internal buffers or frees memory
    }

    // Return this pointer as per convention for constructors in this codebase
    return this;
}