// FUNC_NAME: GodfatherGameManager::updateDonControlGadgets
void GodfatherGameManager::updateDonControlGadgets(void *param_1)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  uint uVar7;
  undefined8 uVar8;
  undefined **local_53c;
  undefined4 uStack_538;
  undefined4 uStack_434;
  undefined4 uStack_430;
  undefined4 uStack_42c;
  undefined1 auStack_428 [1064];
  
  if ((DAT_01223484 != 0) && (*(int *)(DAT_01223484 + 0xc) != 0)) {
    piVar6 = (int *)0x0;
    piVar1 = (int *)FUN_00ad8d40(); // GetDonControlManager
    if ((piVar1 != (int *)0x0) && (iVar2 = (**(code **)(*piVar1 + 0x34))(), iVar2 != 0)) {
      piVar1 = (int *)(**(code **)(*piVar1 + 0x34))(); // GetDonControlGadget
      piVar6 = (int *)(**(code **)(*piVar1 + 0x24))(); // GetGadgetList
    }
    piVar1 = (int *)(**(code **)(*piVar6 + 0x18))(param_1); // GetGadgetByIndex
    if (piVar1 != (int *)0x0) {
      uVar3 = (**(code **)(*piVar6 + 0x20))(); // GetGadgetCount
      uVar7 = 0;
      if (uVar3 != 0) {
        do {
          uVar8 = FUN_00965910(); // GetPlayerManager
          uVar5 = (uint)((ulonglong)uVar8 >> 0x20);
          iVar2 = (int)uVar8;
          if (((iVar2 != 0) && (uVar7 < *(uint *)(iVar2 + 0x50))) &&
             (iVar2 = *(int *)(*(int *)(iVar2 + 0x4c) + uVar7 * 4), iVar2 != 0)) {
            local_53c = &PTR_LAB_00d79770;
            uStack_538 = 6;
            uStack_434 = 0;
            uStack_430 = 0;
            uStack_42c = 0;
            FUN_008b5c70(*(undefined4 *)(iVar2 + 0x5c)); // GetPlayerName
            FUN_008a2f80(&local_53c); // FormatString
            uVar4 = FUN_008b5c10(); // GetGadgetType
            FUN_00b21d90(uVar4); // SetGadgetType
            FUN_00b21ed0(&local_53c); // SetGadgetLabel
            (**(code **)(*piVar1 + 0x2c))(auStack_428,1,0); // SetGadgetEnabled
            FUN_00b19550(); // UpdateGadget
            uVar5 = uVar3;
          }
          uVar7 = uVar7 + 1;
        } while (uVar7 < uVar5);
      }
    }
  }
  return;
}