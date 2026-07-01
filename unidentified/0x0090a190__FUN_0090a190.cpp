// FUNC_NAME: SomeClass::constructor
void __fastcall SomeClass::constructor(SomeClass* thisPtr)
{
    // Set vtable pointer at offset 0x00
    thisPtr->vtable = &PTR_FUN_00d83240;
    // Set pointer at offset 0x3C (0xF * 4)
    thisPtr->field_0x3C = &PTR_LAB_00d83230;
    // Set pointer at offset 0x48 (0x12 * 4)
    thisPtr->field_0x48 = &PTR_LAB_00d8322c;
    // Initialize sub-object at offset 0x50 (0x14 * 4)
    // This likely calls a constructor or initializer for a base class or member
    FUN_004086d0(&thisPtr->subObjectAt0x50);
    FUN_00408310(&thisPtr->subObjectAt0x50);
    // Global initialization call (no arguments)
    FUN_0046c640();
}