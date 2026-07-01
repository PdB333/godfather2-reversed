// FUNC_NAME: Entity::update
void __thiscall Entity::update(int this, uint param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int unaff_EDI;
  undefined4 *puVar4;
  
  iVar3 = **(int **)(DAT_012233a0 + 4);
  if (((iVar3 != 0) && ((int *)(iVar3 + -0x1f30) != (int *)0x0)) &&
     ((*(uint *)(iVar3 + 0x570) >> 7 & 1) == 0)) {
    (**(code **)(*(int *)(iVar3 + -0x1f30) + 0x14c))(0x46f5c7b4,1,0);
    // Check if bit 1 of +0x100 is set -> flag to overlay 0x1000
    if ((*(uint *)(this + 0x100) >> 1 & 1) != 0) {
      param_2 = param_2 | 0x1000;
    }
    // Copy data from +0xc0 (or from FUN_00471610 result) to stack buffer
    if ((*(byte *)(this + 0x100) & 1) == 0) {
      puVar1 = (undefined4 *)(this + 0xc0);
      puVar4 = (undefined4 *)&stack0xffffffa4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
    }
    else {
      puVar1 = (undefined4 *)FUN_00471610();
      puVar4 = (undefined4 *)&stack0xffffffa4;
      for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar4 = puVar4 + 1;
      }
    }
    uVar2 = FUN_007dcf50();
    FUN_0079e3c0(&stack0xffffffa4,param_2,unaff_EDI + 0xb4,uVar2);
  }
  return;
}