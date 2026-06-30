// FUNC_NAME: SomeClass::initializeSomeFlag
void __fastcall SomeClass::initializeSomeFlag(undefined4 param_1)
{
  uint *unaff_EDI;
  
  *unaff_EDI = *unaff_EDI & 0xffff8001 | 1; // Clear bits 1-14, set bit 0
  *(undefined2 *)((int)unaff_EDI + 2) = 0; // Zero out word at offset +2
  *unaff_EDI = *unaff_EDI | 0x8000; // Set bit 15
  FUN_005a0a00(param_1); // Call some initialization function
  unaff_EDI[8] = 0xbeefceec; // Set magic value at offset +0x20 (8*4)
  return;
}