// FUNC_NAME: UnknownClass::DelegatingThunk
// Function address: 0x0072feb0
// Role: Delegation thunk – passes through to the real function at 0x006fa060.
// This pattern is often used for virtual function overrides that simply forward to a base class implementation.

void __thiscall UnknownClass::DelegatingThunk() {
    // Forward call to base implementation (thunk at 0x006fa060)
    thunk_FUN_006fa060();
    return;
}