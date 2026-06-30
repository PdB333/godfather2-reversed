// FUNC_NAME: EARSObject::EARSObject
void __fastcall EARSObject::EARSObject(EARSObject* this)
{
  // Set vtable pointer for EARSObject
  this->vtable = &PTR_FUN_00d5fe00;
  // Set data pointers at offsets 0x3C and 0x48
  this->field_3C = &PTR_LAB_00d5fdf0;
  this->field_48 = &PTR_LAB_00d5fdec;
  // Construct embedded subobject at offset 0x50
  FUN_004086d0(reinterpret_cast<undefined4*>(reinterpret_cast<char*>(this) + 0x50));
  // Initialize embedded subobject
  FUN_00408310(reinterpret_cast<undefined4*>(reinterpret_cast<char*>(this) + 0x50));
  // Call global engine initializer (likely singleton setup)
  FUN_0046c640();
}