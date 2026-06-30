// FUNC_NAME: streamOperation_validateStreamHandle
uint streamOperation_validateStreamHandle(uint handle)
{
  int iVar1;
  uint uVar2;
  
  uVar2 = 0;
  if (((((handle & 0xffff) < 0x200) &&
       (iVar1 = (handle & 0xffff) * 0x30 + 0x10 + DAT_012234bc, iVar1 != 0)) &&
      (*(uint *)(iVar1 + 0x2c) == handle)) && (iVar1 != 0)) {
    // Call to validate/finalize stream operation
    FUN_00414aa0();
    uVar2 = 1;
  }
  return uVar2;
}