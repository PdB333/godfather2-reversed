// FUNC_NAME: GodfatherGameManager::constructor
void __fastcall GodfatherGameManager::constructor(GodfatherGameManager *this)
{
  // Call base class constructor (EARS::Framework::Object or similar)
  FUN_005bf9b0(); // base constructor

  // Set vtable pointers and member variables
  // Offset 0x4C: secondary vtable (maybe for type info or another base)
  this->field_0x4C = (void*)&PTR_LAB_00d85d74; // initial vtable

  // Store global singleton pointer
  DAT_0112a9d0 = this;

  // Zero out fields at offsets 0x50, 0x54, 0x58, 0x5C
  this->field_0x50 = 0;
  this->field_0x54 = 0;
  this->field_0x58 = 0;
  this->field_0x5C = 0;

  // Set primary vtable at offset 0x0
  this->vtable = (void*)&PTR_FUN_00d85db8;

  // Set secondary vtable at offset 0x4 (possibly COM-like interface)
  this->field_0x04 = (void*)&PTR_LAB_00d85d90;

  // Overwrite offset 0x4C with a different vtable (derived class vtable)
  this->field_0x4C = (void*)&PTR_LAB_00d85d8c;
}