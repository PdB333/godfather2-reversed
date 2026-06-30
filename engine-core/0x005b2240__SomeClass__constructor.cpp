// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(undefined4 param_1, uint *param_2)
{
  uint *puVar1;
  int iVar2;
  undefined4 unaff_EDI;
  
  puVar1 = param_2;
  iVar2 = (*DAT_0119caf0)(0x70,0x10); // allocate memory, size 0x70, alignment 0x10
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0059c700(unaff_EDI); // likely base class constructor
  }
  FUN_005b1f80(param_1,puVar1,0,&stack0x0000000c,&param_2); // some initialization
  if ((param_2 != (uint *)0x0) && ((~(byte)(*param_2 >> 0xf) & 1) == 0)) {
    FUN_0059bf00(); // handle error or cleanup
  }
  *(undefined4 *)(iVar2 + 0x58) = unaff_EDI; // +0x58: store some value
  *(uint **)(iVar2 + 0x30) = puVar1; // +0x30: store param_2 pointer
  FUN_005b21e0(); // finalize construction
  return;
}