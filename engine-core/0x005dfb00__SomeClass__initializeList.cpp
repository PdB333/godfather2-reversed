// FUNC_NAME: SomeClass::initializeList
void SomeClass::initializeList(void)
{
  undefined4 *in_EAX; // this pointer
  undefined4 uVar1;
  int iVar2;
  int unaff_ESI; // some other object pointer
  int *piVar3; // pointer to vtable
  
  piVar3 = (int *)*in_EAX; // get vtable pointer
  iVar2 = in_EAX[1]; // some member at offset 0x4
  (**(code **)(*piVar3 + 8))(piVar3); // call virtual function at vtable+8 (likely destructor or cleanup)
  if (iVar2 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(iVar2,piVar3); // some allocation or conversion function
  }
  FUN_005e0800(unaff_ESI,piVar3,uVar1); // initialize list node or similar
  iVar2 = FUN_005e10a0(); // allocate new object
  *(int *)(unaff_ESI + 0x1c) = iVar2; // store at offset 0x1c
  *(undefined1 *)(iVar2 + 0x15) = 1; // set byte at offset 0x15 to 1
  *(int *)(*(int *)(unaff_ESI + 0x1c) + 4) = *(int *)(unaff_ESI + 0x1c); // self-reference for linked list
  *(undefined4 *)*(undefined4 *)(unaff_ESI + 0x1c) = *(undefined4 *)(unaff_ESI + 0x1c); // self-reference
  *(int *)(*(int *)(unaff_ESI + 0x1c) + 8) = *(int *)(unaff_ESI + 0x1c); // self-reference
  *(undefined4 *)(unaff_ESI + 0x20) = 0; // clear member at offset 0x20
  return;
}