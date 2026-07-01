// FUNC_NAME: SomeEntity::~SomeEntity
void __thiscall SomeEntity::~SomeEntity(SomeEntity *this)
{
    // Set vtable to base class vtable (likely derived -> base transition)
    this->vfptr = (void **)&PTR_LAB_00d6f6dc;
    // Unregister or signal cleanup of this type (0x27 = some ID)
    FUN_007f6420(0x27);
    // Delete member at offset +0x7C (31 * 4)
    if (this->memberAt0x7C != 0) {
        FUN_004daf90(&this->memberAt0x7C);
    }
    // Delete member at offset +0x74 (29 * 4)
    if (this->memberAt0x74 != 0) {
        FUN_004daf90(&this->memberAt0x74);
    }
    // Transition to base vtable and call base destructor
    this->vfptr = (void **)&PTR_LAB_00d6b95c;
    FUN_0080ea60();
}