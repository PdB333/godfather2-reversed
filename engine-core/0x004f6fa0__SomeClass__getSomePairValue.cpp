// FUNC_NAME: SomeClass::getSomePairValue
void FUN_004f6fa0(void)
{
  undefined4 *puVar1;
  undefined4 *unaff_ESI; // this pointer (likely)
  undefined1 local_c [12]; // stack buffer for temporary storage

  *unaff_ESI = 0; // clear first member (offset +0x00)
  unaff_ESI[1] = 0; // clear second member (offset +0x04)
  puVar1 = (undefined4 *)FUN_004f7050(local_c); // call helper to fill buffer
  *unaff_ESI = *puVar1; // copy first value to this->member0
  unaff_ESI[1] = puVar1[1]; // copy second value to this->member4
  return;
}