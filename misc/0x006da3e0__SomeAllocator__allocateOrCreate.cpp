// FUNC_NAME: SomeAllocator::allocateOrCreate
undefined4 __fastcall FUN_006da3e0(undefined4 param_1)
{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  puVar1 = (undefined4 *)FUN_009c8f80(); // Get allocator instance
  local_c = 2; // Alignment
  local_8 = 0x10; // Size
  local_4 = 0; // Flags
  iVar2 = (**(code **)*puVar1)(0x80,&local_c); // Allocate 0x80 bytes
  if (iVar2 != 0) {
    uVar3 = FUN_006da310(param_1); // Construct object at allocated memory
    return uVar3;
  }
  return 0;
}