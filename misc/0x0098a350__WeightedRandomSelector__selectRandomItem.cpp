// FUNC_NAME: WeightedRandomSelector::selectRandomItem
void __thiscall WeightedRandomSelector::selectRandomItem(int this, uint param_2, float param_3)
{
  float fVar1;
  float fVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  float10 fVar6;
  float fVar7;
  
  if (param_3._0_1_ == '\0') {
    puVar3 = *(undefined2 **)(this + 0x18); // +0x18: pointer to weight array
    if (puVar3 == (undefined2 *)0x0) {
      puVar3 = &DAT_00e2df14; // default weight array
    }
    FUN_00698ec0(puVar3 + *(int *)(this + 0x30)); // +0x30: current index
    return;
  }
  fVar1 = *(float *)(this + 0x4c); // +0x4c: max threshold
  fVar2 = *(float *)(this + 0x44); // +0x44: min threshold
  fVar7 = *(float *)(this + 0x90) * DAT_00d5c454; // +0x90: some multiplier
  iVar5 = *(int *)(this + 0x30); // +0x30: current index
  param_3 = 0.0;
  if (iVar5 < *(int *)(this + 0x28)) { // +0x28: array size
    do {
      if (*(char *)(this + 0x34) == '\0') { // +0x34: flag for using default weight
        uVar4 = (uint)*(ushort *)(*(int *)(this + 0x18) + iVar5 * 2); // +0x18: weight array
      }
      else {
        uVar4 = 0x2a; // default weight value
      }
      fVar6 = (float10)FUN_0098a210(*(undefined4 *)(this + 0x90), uVar4); // +0x90: some parameter
      param_3 = (float)fVar6 + param_3;
      if ((fVar1 - fVar2) - fVar7 <= param_3) {
        return;
      }
      param_2 = uVar4;
      FUN_004dbd90(&param_2, 0, 1); // random number generation
      iVar5 = iVar5 + 1;
    } while (iVar5 < *(int *)(this + 0x28));
  }
  return;
}