// FUNC_NAME: GodfatherGameManager::handleMissionCompletion
void __thiscall GodfatherGameManager::handleMissionCompletion(int thisPtr, int missionData)
{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  undefined1 local_2c [4];
  int local_28 [2];
  undefined **local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  int local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (((missionData != 0) &&
      ((((cVar4 = FUN_00481620(), cVar4 != '\0' || (*(int *)(thisPtr + 0x50) == DAT_0112f814)) ||
        (*(int *)(thisPtr + 0x50) == DAT_0112f81c)) &&
       ((*(int *)(thisPtr + 0x68) = *(int *)(thisPtr + 0x68) + 1, iVar3 = DAT_0112b9b4,
        *(int *)(thisPtr + 0x68) == *(int *)(thisPtr + 0x5c) && (*(int *)(DAT_0112b9b4 + 0x40) != 0)
        ))))) && (iVar1 = *(int *)(missionData + 0x1ef8), iVar1 != -1)) {
    cVar4 = FUN_00481620();
    if ((cVar4 != '\0') && (iVar2 = *(int *)(iVar3 + 0x34), iVar2 != -1)) {
      FUN_008bce30(*(undefined4 *)(*(int *)(iVar3 + 0x28) + iVar2 * 4),
                   *(undefined4 *)(thisPtr + 0x58));
    }
    local_1c = *(undefined4 *)(thisPtr + 0x58);
    local_c = 0xffffffff;
    local_8 = 0;
    local_4 = 0;
    local_20 = &PTR_LAB_00d77a04;
    local_18 = DAT_00e54400;
    local_14 = 0;
    local_10 = iVar1;
    FUN_0045c400(&DAT_0112ecfc,&local_20,0);
    FUN_0045ca00(missionData);
    FUN_0045c400(thisPtr + 0x60,local_2c,0);
    if (local_28[0] != 0) {
      FUN_004daf90(local_28);
    }
  }
  return;
}