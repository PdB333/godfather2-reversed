// FUNC_NAME: MissionObject::MissionObject
void __fastcall MissionObject::MissionObject(MissionObject *this)
{
  // Set vtable pointer at offset 0
  this->vtable = (void**)&PTR_FUN_00e3329c;
  // Set additional function pointers at offsets 0x3C and 0x48
  this->field_0x3C = &PTR_LAB_00e332bc;
  this->field_0x48 = &PTR_LAB_00e332cc;
  
  // Initialize embedded subobject at offset 0x50 (size unknown)
  FUN_004086d0(this + 0x14);  // e.g., initStringList
  FUN_00408310(this + 0x14);  // e.g., finalizeStringList
  
  // Global initialization (e.g., increment object count)
  FUN_0046c640();
}