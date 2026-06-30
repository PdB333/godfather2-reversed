// FUNC_NAME: BaseInitObject::BaseInitObject
void __fastcall BaseInitObject::BaseInitObject(BaseInitObject *this)
{
  // +0x00: type flag (set to 0)
  this->field_0x00 = 0;
  // +0x04: pointer to some global data
  this->field_0x04 = DAT_00d5e288;
  // +0x08: pointer to another global data
  this->field_0x08 = DAT_00d5efd0;
  // +0x10..+0x2c: zero out remaining fields (assuming size 0x30)
  this->field_0x10 = 0;
  this->field_0x14 = 0;
  this->field_0x18 = 0;
  this->field_0x1c = 0;
  this->field_0x20 = 0;
  this->field_0x24 = 0;
  this->field_0x28 = 0;
  this->field_0x2c = 0;
}