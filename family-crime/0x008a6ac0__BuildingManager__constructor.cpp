// FUNC_NAME: BuildingManager::constructor
void __fastcall BuildingManager_constructor(undefined4 *this)
{
  // Set vtable pointer to BuildingManager's vtable
  *this = &PTR_FUN_00d79a94; // vtable for BuildingManager
  
  // Initialize sub-object pointers
  this[0xf] = &PTR_LAB_00d79a84; // +0x3C - likely a vtable for nested class or interface
  this[0x12] = &PTR_LAB_00d79a80; // +0x48 - another sub-object vtable
  
  // Call base class constructor (likely Entity or Manager base)
  // param_1 + 0x18 = this + 0x60, passing address of member at offset 0x60
  FUN_00408310(this + 0x18); // constructor for member at +0x60
  
  // Call some initialization function
  FUN_008a1380(); // BuildingManager::initialize or similar
}