// FUNC_NAME: Entity::constructor
void __fastcall Entity::constructor(Entity *this)
{
  // Set vtable pointer at offset 0x00
  this->vtable = (void *)&PTR_FUN_00d83eb0;
  // Set vtable pointer at offset 0x10 (subobject)
  this->field_0x10 = (void *)&PTR_LAB_00d83e88;
  // Set vtable pointer at offset 0x4C
  this->field_0x4C = (void *)&PTR_LAB_00d83e84;
  // Call base class constructor for subobject at offset 0x10
  FUN_005c02f0(&this->field_0x10, &LAB_00911140, 1);
  // Set multiple vtable pointers to a default value (likely null or shared vtable)
  this->field_0x260 = (void *)&PTR_LAB_00d83b18; // +0x260
  this->field_0x1DC = (void *)&PTR_LAB_00d83b18; // +0x1DC
  this->field_0x158 = (void *)&PTR_LAB_00d83b18; // +0x158
  this->field_0xD4 = (void *)&PTR_LAB_00d83b18;  // +0xD4
  this->field_0x50 = (void *)&PTR_LAB_00d83b18;  // +0x50
  // Overwrite vtable at offset 0x4C with a different pointer
  this->field_0x4C = (void *)&PTR_LAB_00d83b2c;
  // Clear global static flag
  DAT_01130000 = 0;
  // Call additional initialization
  FUN_005c16e0();
}