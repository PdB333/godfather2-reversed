// FUNC_NAME: SomeContainer::addOrUpdateEntry
undefined4 * __thiscall SomeContainer::addOrUpdateEntry(undefined4 *this, undefined4 *param_2)
{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  iVar3 = param_2[1]; // +0x04: some value from param_2
  piVar4 = (int *)*param_2; // +0x00: pointer to an object
  (**(code **)(*piVar4 + 8))(piVar4); // call virtual function at vtable+8 (likely release/decRef)
  if (iVar3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(iVar3, piVar4); // some lookup or conversion function
  }
  FUN_0081d2b0(piVar4, uVar1); // associate the value with the object
  puVar2 = (undefined4 *)this[1]; // +0x04: pointer to a container or list
  if (puVar2 == (undefined4 *)0x0) {
    local_c = 0;
    local_8 = 0;
    local_4 = 0;
    puVar2 = &local_c; // use a local empty placeholder
  }
  iVar3 = (*(code *)**(undefined4 **)*this)(0x2c, puVar2); // call virtual function at vtable+0 with size 0x2c (allocate)
  if (iVar3 != 0) {
    *(int *)iVar3 = iVar3; // self-reference at offset 0
  }
  if ((int *)(iVar3 + 4) != (int *)0x0) {
    *(int *)(iVar3 + 4) = iVar3; // self-reference at offset 4
  }
  this[6] = iVar3; // +0x18: store new entry
  this[7] = 0; // +0x1c: reset counter or flag
  return this;
}