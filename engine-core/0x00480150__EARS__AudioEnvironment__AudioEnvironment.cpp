// FUNC_NAME: EARS::AudioEnvironment::AudioEnvironment
void __thiscall EARS::AudioEnvironment::AudioEnvironment(AudioEnvironment *this)
{
  // Set main vtable pointer at +0x00
  this->vtable = (void **)&PTR_FUN_00e33384;
  // Set secondary vtable at +0x3C (param_1[0xf])
  this->subObject1.vtable = (void **)&PTR_LAB_00e333a0;
  // Set third vtable at +0x48 (param_1[0x12])
  this->subObject2.vtable = (void **)&PTR_LAB_00e333b0;
  // Initialize sub-object at +0xD0 (param_1 + 0x34) – likely a string or array
  FUN_004086d0(&this->field_D0);
  // Initialize sub-object at +0xD8 (param_1 + 0x36)
  FUN_004086d0(&this->field_D8);
  // Further initialization at +0xD0 and +0xD8
  FUN_00408310(&this->field_D0);
  FUN_00408310(&this->field_D8);
  // Global audio environment setup
  FUN_0046c640();
}