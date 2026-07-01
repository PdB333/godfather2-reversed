// FUNC_NAME: InputManager::constructor
void __fastcall InputManager_constructor(InputManager *this)
{
  // Call base class constructor
  FUN_004bc3f0();
  
  // Set vtable pointers
  // +0x10 (4th element) = second vtable pointer
  this[0x4] = &PTR_LAB_00e35c24;  // secondary vtable
  this[0x0] = &PTR_LAB_00e317cc;  // primary vtable
}