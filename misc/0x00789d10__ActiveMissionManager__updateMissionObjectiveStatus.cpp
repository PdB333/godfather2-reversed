// FUNC_NAME: ActiveMissionManager::updateMissionObjectiveStatus
void __fastcall ActiveMissionManager::updateMissionObjectiveStatus(int this)
{
  char bActiveStatus;
  undefined4 uVar2;
  int unaff_EBX;
  int unaff_ESI;
  uint *puVar3;
  uint uVar4;
  float fVar5;
  int local_64;
  int iStack_60;
  int iStack_5c;
  undefined1 auStack_58 [4];
  int local_54;

  if (((*(char *)(this + 0xe4) == '\0') && ((~*(byte *)(this + 0x50) & 1) != 0)) &&
     ((*(int *)(this + 100) != 0 ||
      (((*(int *)(this + 0x68) != 0 || (*(int *)(this + 0x6c) != 0)) ||
       (*(int *)(this + 0x70) != 0)))))) {
    local_64 = 0;
    local_54 = this;
    bActiveStatus = (**(code **)(**(int **)(this + 0xc) + 0x10))(0x38523fc3,&local_64);
    if ((bActiveStatus != '\0') && (unaff_ESI != 0)) {
      iStack_60 = unaff_ESI;
      uVar2 = FUN_00471610();
      FUN_0044b4e0(auStack_58,uVar2);
      puVar3 = (uint *)(this + 0xcc);
      local_64 = 2;
      uVar4 = DAT_00e44680;
      fVar5 = DAT_00e44598;
      do {
        if (((fVar5 < (float)(*puVar3 & uVar4)) || (fVar5 < (float)(puVar3[1] & uVar4))) ||
           (fVar5 < (float)(puVar3[2] & uVar4))) {
          uVar2 = FUN_004df330(&stack0xffffff98,this + 100,auStack_58,0x1ff,0,iStack_60,
                               0xffffffff,puVar3);
          FUN_00414db0(uVar2);
          fVar5 = DAT_00e44598;
          uVar4 = DAT_00e44680;
          if (unaff_EBX != 0) {
            *(undefined4 *)(unaff_EBX + 8) = 0;
            unaff_EBX = 0;
            uVar4 = DAT_00e44680;
          }
        }
        puVar3 = puVar3 + 3;
        local_64 = local_64 + -1;
      } while (local_64 != 0);
      *(undefined1 *)(iStack_5c + 0xe4) = 1;
    }
  }
  return;
}