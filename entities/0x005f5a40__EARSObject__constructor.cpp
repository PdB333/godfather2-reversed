// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this)
{
    // Set vtable pointer to base class vtable (PTR_FUN_00e40788)
    this->vtable = &PTR_FUN_00e40788;
    // Set second pointer (likely self-reference or another vtable)
    this->field_4 = &PTR_LAB_00e4078c;

    // Call subsystem initialization with a global data structure
    initializeSubsystem(&g_someGlobal);  // FUN_004086d0

    // Call default setup routine
    setupDefaults();  // FUN_004083d0

    // Overwrite vtable with derived class vtable (PTR_LAB_00e4079c)
    this->vtable = &PTR_LAB_00e4079c;

    // Reset global initialization flag
    g_initializationFlag = 0;  // _DAT_0122351c
}