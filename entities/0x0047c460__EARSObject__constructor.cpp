// FUNC_NAME: EARSObject::constructor
void __fastcall EARSObject::constructor(EARSObject* this)
{
    // Set vtable pointer
    this->vtable = &PTR_FUN_00e3317c;

    // Offsets: 0x3C and 0x48 set to static function pointers/labels
    this->field_0x3C = &PTR_LAB_00e33198; // +0x3C: likely a method table or static data
    this->field_0x48 = &PTR_LAB_00e331a8; // +0x48: another static reference

    // Initialize sub-object at offset 0x50 (size unknown)
    FUN_004086d0(&this->subObject);  // constructor for subObject
    FUN_00408310(&this->subObject);  // additional initialization for subObject

    // Global engine initialization call
    FUN_0046c640();
}