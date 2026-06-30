// FUNC_NAME: Entity::clearFields
void __fastcall Entity::clearFields(Entity* thisPtr)
{
    // Call base class (likely Entity or SimObject) initialization at 0x00612e00
    // This may set up vtable, ref counting, etc.
    FUN_00612e00(); // TODO: rename to base class init function

    // Clear two fields at offsets +0x10 and +0x14 (likely a pointer pair or state flags)
    thisPtr->field_0x10 = 0; // +0x10
    thisPtr->field_0x14 = 0; // +0x14

    // Clear two fields at offsets +0xa4 and +0xa8 (possibly timer, cooldown, or object reference)
    thisPtr->field_0xa4 = 0; // +0xa4
    thisPtr->field_0xa8 = 0; // +0xa8
}