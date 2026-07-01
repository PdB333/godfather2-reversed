// FUNC_NAME: GameManager::constructor
undefined4 * __fastcall GameManager::constructor(undefined4 *thisPtr)
{
  // Call base class constructor 6 times (likely vtables for multiple inheritance)
  // Each call initializes a base sub-object
  FUN_005953b0();
  FUN_005953b0();
  FUN_005953b0();
  FUN_005953b0();
  FUN_005953b0();
  FUN_005953b0();
  
  // Set vtable pointer for this object
  *thisPtr = &PTR_LAB_00d745c0;  // vtable for GameManager
  
  // Additional initialization call
  FUN_005953b0();
  
  return thisPtr;
}