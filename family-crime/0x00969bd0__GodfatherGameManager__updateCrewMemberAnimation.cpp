// FUNC_NAME: GodfatherGameManager::updateCrewMemberAnimation

void __thiscall GodfatherGameManager::updateCrewMemberAnimation(int this, int param_2, undefined4 *param_3)
{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint uVar4;
  int *piVar5;
  
  iVar1 = DAT_01223484;
  if (DAT_01223484 != 0) {
    iVar2 = FUN_00965910();
    if (iVar2 != 0) {
      uVar4 = 0;
      if (*(uint *)(iVar2 + 0x50) != 0) {
        puVar3 = *(undefined4 **)(iVar2 + 0x4c);
LAB_00969c00:
        if (((undefined4 *)*puVar3)[0x17] != param_2) goto code_r0x00969c07;
        puVar3 = (undefined4 *)*puVar3;
        for (iVar2 = 0x14; iVar2 != 0; iVar2 = iVar2 + -1) {
          *puVar3 = *param_3;
          param_3 = param_3 + 1;
          puVar3 = puVar3 + 1;
        }
      }
    }
LAB_00969c20:
    piVar5 = (int *)(this + 0x2ec);
    if (*(int *)(iVar1 + 8) == 0) {
      piVar5 = (int *)(this + 0x378);
    }
    (**(code **)(*piVar5 + 0x94))();
  }
  return;
code_r0x00969c07:
  uVar4 = uVar4 + 1;
  puVar3 = puVar3 + 1;
  if (*(uint *)(iVar2 + 0x50) <= uVar4) goto LAB_00969c20;
  goto LAB_00969c00;
}