// FUNC_NAME: GameAlloc::allocateWithTag
undefined4 GameAlloc::allocateWithTag(void)

{
  undefined4 *allocator;
  int iVar2;
  undefined4 retVal;
  undefined4 unaff_retaddr;
  undefined4 tag;
  undefined4 size_10;
  undefined4 unk0;
  
  allocator = (undefined4 *)FUN_009c8f80(); // likely getDefaultAllocator() or similar
  tag = 2;
  size_10 = 0x10;
  unk0 = 0;
  iVar2 = (**(code **)*allocator)(0x80, &tag); // call allocator function with size 0x80 and tag params
  if (iVar2 != 0) {
    retVal = FUN_008ccae0(unk0, unaff_retaddr); // possibly zero-init or construct
    return retVal;
  }
  return 0;
}