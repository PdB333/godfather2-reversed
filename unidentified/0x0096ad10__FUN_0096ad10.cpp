// FUNC_NAME: UnknownClass::initAndGetSubobject
// Address: 0x0096ad10
// Calls an internal initializer (FUN_00968ea0) on the object pointed to by param_1,
// then returns a pointer (as int) to the subobject at offset +0x4.
// This is typical of a base class or member subobject construction in multiple inheritance.
int UnknownClass::initAndGetSubobject(int param_1) {
    // The first argument &param_1 may be a decompiler artifact for passing a reference.
    // Actual semantic: pass the object pointer and some value.
    FUN_00968ea0(&param_1, param_1);
    // Return a pointer to the embedded subobject at offset 0x4.
    return param_1 + 4;
}