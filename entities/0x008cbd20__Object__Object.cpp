// FUNC_NAME: Object::Object
void __fastcall Object::Object(Object* this)
{
    // Set vtable pointer for this class
    *reinterpret_cast<undefined4**>(this) = &PTR_FUN_00d7c2e8;

    // Initialize associated global data (likely a singleton or static manager)
    FUN_004086d0(&DAT_012069d4);

    // Perform additional object-specific initialization
    FUN_004083d0();
}