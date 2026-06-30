// FUNC_NAME: ObjectBase::Constructor
undefined4 __thiscall ObjectBase::Constructor(byte flag) {
    // Perform base initialization (common to all constructors)
    FUN_0053f0c0();

    // If the lowest bit of the flag is set, execute extra setup
    // (e.g., when allocating from a pool or creating a copy)
    if ((flag & 1) != 0) {
        FUN_009c8eb0(this);
    }

    return this;
}