// FUNC_NAME: GodfatherGameManager::constructor
undefined4 * __thiscall GodfatherGameManager::constructor(undefined4 *this, byte flags)
{
  int *piVar1;
  
  *this = &PTR_FUN_00d738c0;  // vtable pointer for GodfatherGameManager
  FUN_0082a340();  // base class constructor call
  this[0xc] = &PTR_LAB_00e32854;  // +0x30: secondary vtable or interface pointer
  FUN_00821f60();  // member initialization
  if ((flags & 1) != 0) {
    piVar1 = (int *)FUN_009c8f80();  // operator new
    (**(code **)(*piVar1 + 4))(this, 0xd0);  // placement new with size 0xD0
  }
  return this;
}