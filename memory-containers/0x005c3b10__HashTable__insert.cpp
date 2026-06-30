// FUNC_NAME: HashTable::insert
void __thiscall HashTable::insert(int this, int *param_2)
{
  undefined4 *puVar1;
  uint uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int *piVar7;
  
  uVar4 = *(uint *)(this + 0xc); // current size
  uVar2 = (**(code **)(*param_2 + 4))(); // hash function call
  uVar2 = (&DAT_00f17680)[uVar2 >> 0x10 & 0xff] + (&DAT_00f17680)[uVar2 >> 8 & 0xff] +
          (&DAT_00f17680)[uVar2 >> 0x18] + *(int *)(&DAT_00f17684 + (uVar2 & 0xff) * 4);
  if (DAT_00f17680 + 1 < uVar2) {
    uVar2 = DAT_00f17680;
  }
  if (uVar4 <= uVar2) {
    iVar6 = uVar2 + 1;
    if (*(int *)(this + 0x10) < iVar6) { // capacity check
      uVar3 = FUN_005c27a0(*(undefined4 *)(this + 8),iVar6,4,this + 0xc,this + 0x10);
      *(undefined4 *)(this + 8) = uVar3;
    }
    *(int *)(this + 0xc) = iVar6; // update size
    for (; uVar4 < uVar2; uVar4 = uVar4 + 1) {
      *(undefined4 *)(*(int *)(this + 8) + uVar4 * 4) = 0;
    }
    *(int **)(*(int *)(this + 8) + uVar2 * 4) = param_2;
    return;
  }
  puVar1 = (undefined4 *)(*(int *)(this + 8) + uVar2 * 4);
  if (*(int *)(*(int *)(this + 8) + uVar2 * 4) == 0) {
    *puVar1 = param_2;
    return;
  }
  *(undefined1 *)(this + 0xc0) = 0; // collision flag
  (**(code **)(*(int *)*puVar1 + 4))(); // call vtable method
  uVar5 = FUN_005c3a90(); // rehash or probe
  if (uVar5 != uVar2) {
    piVar7 = *(int **)(*(int *)(this + 8) + uVar2 * 4);
    *(int **)(*(int *)(this + 8) + uVar2 * 4) = param_2;
    param_2 = piVar7;
  }
  uVar2 = uVar2 + 1;
  if (uVar2 < uVar4) {
    piVar7 = (int *)(*(int *)(this + 8) + uVar2 * 4);
    do {
      if (*piVar7 == 0) {
        *(int **)(*(int *)(this + 8) + uVar2 * 4) = param_2;
        return;
      }
      uVar2 = uVar2 + 1;
      piVar7 = piVar7 + 1;
    } while (uVar2 < uVar4);
  }
  piVar7 = (int *)(this + 0xc);
  iVar6 = *(int *)(this + 0xc) + 1;
  if (*(int *)(this + 0x10) < iVar6) {
    uVar3 = FUN_005c27a0(*(undefined4 *)(this + 8),iVar6,4,piVar7,this + 0x10);
    *(undefined4 *)(this + 8) = uVar3;
  }
  iVar6 = *piVar7;
  *piVar7 = iVar6 + 1;
  *(int **)(*(int *)(this + 8) + iVar6 * 4) = param_2;
  return;
}