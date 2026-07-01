// FUNC_NAME: BuildingManager::BuildingManager
void __thiscall BuildingManager::BuildingManager(BuildingManager *this)
{
  // Set vtable pointer (offset 0x00)
  *this = (BuildingManager *)&PTR_FUN_00d7cae8;
  // Set function pointers at offsets 0x3C and 0x48
  this->field_0x3C = &PTR_LAB_00d7cad8;
  this->field_0x48 = &PTR_LAB_00d7cad4;
  // Initialize sub-object at offset 0x50 (likely a container or string)
  FUN_004086d0(&this->subObject); // construct sub-object
  FUN_00408310(&this->subObject); // initialize sub-object
  // Global initialization call
  FUN_0046c640();
}