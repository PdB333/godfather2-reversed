// FUNC_NAME: SomeClass::constructor
undefined4 * FUN_005fb610(undefined4 *this)

{
  undefined4 *in_EAX;
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  piVar4 = (int *)*in_EAX;
  iVar3 = in_EAX[1];
  (**(code **)(*piVar4 + 8))(piVar4); // Call vtable method at offset 8 (likely some init)
  if (iVar3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(iVar3,piVar4); // Allocate or clone something
  }
  FUN_005fbd30(this,piVar4,uVar1); // Another init function
  puVar2 = (undefined4 *)this[1]; // +0x04
  if (puVar2 == (undefined4 *)0x0) {
    uStack_c = 0;
    uStack_8 = 0;
    uStack_4 = 0;
    puVar2 = &uStack_c;
  }
  iVar3 = (*(code *)**(undefined4 **)*this)(0xc,puVar2); // Virtual call with 0xc (12) as parameter
  if (iVar3 != 0) {
    *(int *)iVar3 = iVar3; // Self-reference for linked list
  }
  if ((int *)(iVar3 + 4) != (int *)0x0) {
    *(int *)(iVar3 + 4) = iVar3; // Another self-reference
  }
  this[7] = 0; // +0x1C
  this[6] = iVar3; // +0x18
  return this;
}