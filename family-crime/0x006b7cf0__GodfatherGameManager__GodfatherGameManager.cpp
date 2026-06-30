// FUNC_NAME: GodfatherGameManager::GodfatherGameManager
undefined4 * __thiscall GodfatherGameManager::GodfatherGameManager(undefined4 *this, byte flags)
{
  // Set primary vtable pointer
  *this = &PTR_FUN_00d5e588;
  
  // Set secondary vtable pointers for virtual inheritance
  this[0xf] = &PTR_LAB_00d5e578;   // +0x3C
  this[0x12] = &PTR_LAB_00d5e574;  // +0x48

  // Initialize global mutex
  FUN_004086d0(&DAT_0120e93c);  // likely a mutex/init routine
  
  // Some global initialization
  FUN_0046c640();

  // If flags & 1, call placement delete on failure (releases memory of size 0x68)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x68);
  }

  return this;
}