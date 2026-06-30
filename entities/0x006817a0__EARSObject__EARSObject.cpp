// FUNC_NAME: EARSObject::EARSObject
void __thiscall EARSObject::constructor(EARSObject* this)
{
    // Call base class initializer
    EARSObject::initializeBase(); // FUN_006809b0
    // Initialize field at offset 0x20 to 0 (likely flag or pointer)
    this->field_0x20 = 0;
}