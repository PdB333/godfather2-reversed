// FUNC_NAME: EARSObject::allocateOrGetExisting
undefined4 EARSObject::allocateOrGetExisting(undefined4 param_1, undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 2;
  local_8 = 0x10;
  local_4 = 0;
  iVar1 = FUN_0043b980(0xf20,&local_c,param_2); // likely EARS::MemoryManager::allocate with type info
  if (iVar1 != 0) {
    uVar2 = FUN_00879160(param_1); // likely constructor or initializer
    return uVar2;
  }
  return 0;
}