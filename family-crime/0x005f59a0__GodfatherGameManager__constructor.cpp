// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __fastcall GodfatherGameManager::constructor(undefined4 *this)

{
  undefined4 *vtablePtr;
  
  vtablePtr = this + 1;
  *vtablePtr = &PTR_FUN_00e2f19c;  // vtable for base class
  this[2] = 1;                      // +0x08: some flag (initialized to 1)
  this[3] = 0;                      // +0x0C: some counter/state (initialized to 0)
  *this = &PTR_FUN_00e40788;        // +0x00: vtable for GodfatherGameManager
  *vtablePtr = &PTR_LAB_00e4078c;   // +0x04: secondary vtable or interface pointer
  _DAT_0122351c = this;             // Store singleton pointer at 0x0122351c
  if (DAT_012069c4 != 0) {
    FUN_00407e60(vtablePtr, &DAT_012069c4);  // Register with some manager/list
  }
  return this;
}