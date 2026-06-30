// FUNC_NAME: SomeClass::forwardToField4
// Address: 0x005830d0
// Identified role: Thin forwarding method that calls another function with a member variable at offset 0x04 as the first argument.
// The function takes one explicit parameter (param2) and implicitly uses 'this' from ECX (__thiscall).
void SomeClass::forwardToField4(void* param) {
    // Call FUN_005781f0 with field at +0x04 and the explicit parameter
    FUN_005781f0(*(void**)((int)this + 4), param);
}