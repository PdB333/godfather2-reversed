// FUNC_NAME: SomeAllocator::allocateOrReuse
int __fastcall SomeAllocator::allocateOrReuse(int this)
{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = FUN_00840250(); // likely getPoolSize or getBlockSize
  iVar2 = FUN_008401e0(0xa4, uVar1); // allocate block of size 0xa4 from pool
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_008421f0(); // initialize or construct the allocated block
  }
  uVar1 = FUN_00848c30(*(undefined4 *)(param_1 + 0x40)); // release or free old pointer at +0x40
  *(undefined4 *)(param_1 + 0x40) = uVar1; // store new pointer at +0x40
  if (iVar2 != 0) {
    return iVar2 + 0xc; // return pointer to data after header (offset 0xc)
  }
  return 0;
}