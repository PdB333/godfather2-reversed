// FUNC_NAME: BaseObject::constructor
void __fastcall BaseObject::constructor(BaseObject* this)
{
    // Zero out most fields; index 4 (offset 0x10) is intentionally left uninitialized
    this->field_0 = 0;
    this->field_1 = 0;
    this->field_2 = 0;
    this->field_3 = 0;
    this->field_5 = 0;
    this->field_6 = 0;
    this->field_7 = 0;
    this->field_8 = 0;
    this->field_9 = 0;
    this->field_10 = 0;
    this->field_11 = 0;
}