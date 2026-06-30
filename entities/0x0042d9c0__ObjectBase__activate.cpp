// FUNC_NAME: ObjectBase::activate
void ObjectBase::activate(uint param_1)
{
    preActivate();                    // calls engine init (FUN_00430450)
    this->field_0x84 = 1;             // +0x84: set active flag
}