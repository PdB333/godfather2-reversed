// FUNC_NAME: SomeClass::constructor
void SomeClass::constructor(undefined4 param_1)
{
  undefined4 uVar1;
  undefined4 *unaff_ESI;
  
  unaff_ESI[1] = 0; // +0x04: some field initialized to 0
  unaff_ESI[2] = 0; // +0x08: some field initialized to 0
  *unaff_ESI = &PTR_LAB_00e42d64; // +0x00: vtable pointer set
  unaff_ESI[4] = 0x5dc; // +0x10: size field = 1500 (0x5dc)
  uVar1 = (*(code *)PTR__malloc_00f0cd88)(0x5dc); // allocate 1500 bytes
  unaff_ESI[3] = uVar1; // +0x0C: pointer to allocated buffer
  *(undefined1 *)(unaff_ESI + 5) = 1; // +0x14: some flag set to 1
  *unaff_ESI = &PTR_LAB_00e43144; // +0x00: vtable pointer updated to second vtable
  unaff_ESI[6] = 0; // +0x18: field initialized to 0
  unaff_ESI[7] = 0; // +0x1C: field initialized to 0
  unaff_ESI[8] = 0; // +0x20: field initialized to 0
  unaff_ESI[10] = 0; // +0x28: field initialized to 0
  *(undefined1 *)(unaff_ESI + 9) = 0; // +0x24: byte field initialized to 0
  FUN_0064bc00(param_1); // call to another initialization function
  FUN_0065f1a0(); // call to another initialization function
  return;
}