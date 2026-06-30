// FUNC_NAME: GodfatherObject::Constructor
void __thiscall GodfatherObject::Constructor(GodfatherObject* this) {
    // Set temporary vtable (base class)
    *this = &g_vtable_BaseClass;                     // PTR_FUN_00d605d8

    // Call base class initialization
    BaseClassConstructor(this);                      // FUN_006f1d40
    BaseInit(this);                                  // FUN_006f1cf0

    // Set final vtable (derived class)
    *this = &g_vtable_DerivedClass;                  // PTR_LAB_00d605d4

    // Reset global initialized flag
    g_initializedFlag = 0;                           // DAT_0112997c
}