// FUNC_NAME: PresentationManager::constructor
void __fastcall PresentationManager::constructor(PresentationManager *this)
{
  // Set vtable pointer (offset 0x00)
  this->vtable = (void *)&PTR_FUN_00d8b730;
  
  // Set function pointers at offsets 0x3C (0xF * 4) and 0x48 (0x12 * 4)
  // These appear to be additional virtual function tables or method pointers
  this->field_0x3C = (void *)&PTR_LAB_00d8b720;
  this->field_0x48 = (void *)&PTR_LAB_00d8b71c;
  
  // Initialize sub-objects at offsets 0x8C (0x23 * 4) and 0x94 (0x25 * 4)
  // FUN_004086d0 and FUN_00408310 are likely constructors for member objects
  FUN_004086d0(&this->subObject1); // offset 0x8C
  FUN_00408310(&this->subObject1); // offset 0x8C
  FUN_004086d0(&this->subObject2); // offset 0x94
  FUN_00408310(&this->subObject2); // offset 0x94
  
  // Initialize global singleton instances
  FUN_004086d0((int *)&DAT_0120e93c); // global singleton 1
  FUN_004086d0((int *)&DAT_011301a8); // global singleton 2
  FUN_004086d0((int *)&DAT_01130388); // global singleton 3
  
  // Final initialization routine
  FUN_0046c640();
}