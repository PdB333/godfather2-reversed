// FUNC_NAME: PlayerActionableInfo::constructor
void __fastcall PlayerActionableInfo::constructor(PlayerActionableInfo *this)
{
  // Set vtable pointer
  *this = &PTR_FUN_00d80554; // vtable for PlayerActionableInfo
  
  // Initialize member at offset +0x3C (0xF * 4)
  this[0xf] = &PTR_LAB_00d80544; // likely a function pointer or interface
  
  // Initialize member at offset +0x48 (0x12 * 4)
  this[0x12] = &PTR_LAB_00d80540; // another function pointer or interface
  
  // Initialize sub-object at offset +0x50 (0x14 * 4)
  FUN_004086d0(&this[0x14]); // likely base class or member constructor
  
  // Another initialization at same offset
  FUN_00408310(&this[0x14]); // likely another base/member init
  
  // Global initialization call
  FUN_0046c640(); // possibly registering or setting up global state
}