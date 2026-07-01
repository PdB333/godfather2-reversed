// FUNC_NAME: SomeContainer::insertSortedByKey
void __thiscall SomeContainer::insertSortedByKey(int *this, int param_2)
{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  
  // Call virtual function at vtable+0x28 (likely getKey or compareKey) on param_2
  iVar1 = (**(code **)(*this + 0x28))(param_2);
  uVar4 = 0;
  // this+0x98 (0x26*4) is the count of elements
  if (this[0x26] != 0) {
    uVar4 = 0;
    do {
      // this+0x94 (0x25*4) is the array of pointers (8 bytes per element? or pointer+data?)
      iVar2 = *(int *)(this[0x25] + uVar4 * 8);
      if ((iVar2 != 0) && (iVar2 = iVar2 + -0x48, iVar2 != 0)) {
        iVar2 = (**(code **)(*this + 0x28))(iVar2);
        if (iVar2 <= iVar1) break;
      }
      uVar4 = uVar4 + 1;
    } while (uVar4 < (uint)this[0x26]);
  }
  // Allocate or get node at index uVar4
  piVar3 = (int *)FUN_0083e730(uVar4);
  if (param_2 == 0) {
    param_2 = 0;
  }
  else {
    param_2 = param_2 + 0x48;
  }
  // Insert into linked list (piVar3 is node, param_2 is data with offset 0x48)
  if (*piVar3 != param_2) {
    if (*piVar3 != 0) {
      FUN_004daf90(piVar3);
    }
    *piVar3 = param_2;
    if (param_2 != 0) {
      piVar3[1] = *(int *)(param_2 + 4);
      *(int **)(param_2 + 4) = piVar3;
    }
  }
  return;
}