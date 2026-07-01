// FUNC_NAME: FUN_008f82b0
undefined4 __fastcall FUN_008f82b0(int thisPtr)
{
  undefined4 uVar1;
  
  // Check if pointer at offset +0x160 is non-null
  if (*(int *)(thisPtr + 0x160) != 0) {
    // Call function at 0x007ff880 - likely returns a value from the referenced sub-object
    uVar1 = FUN_007ff880();
    return uVar1;
  }
  return 0;
}