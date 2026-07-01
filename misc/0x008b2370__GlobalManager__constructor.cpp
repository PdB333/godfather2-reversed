// FUNC_NAME: GlobalManager::constructor
void __fastcall GlobalManager::constructor(GlobalManager* this)
{
  // Store global instance pointer
  g_theGlobalManager = this;
  // Set vtable pointer (offset 0x00) to class-specific vtable
  this->vtable = &PTR_LAB_00d7ac20;
  // Set second field (offset 0x04) to another vtable (likely for secondary inheritance or companion interface)
  this->field_4 = &PTR_LAB_00d7ac1c;
}