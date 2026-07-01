// FUNC_NAME: CrimeManager::updateCrimeHeatAndTriggerThreatNotifications
void __fastcall CrimeManager::updateCrimeHeatAndTriggerThreatNotifications(int thisPtr)
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  uint uVar6;
  float fVar7;
  undefined **local_54;
  int local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined ***local_44;
  undefined1 local_40;
  undefined4 local_3c;
  undefined ***local_38;
  undefined1 local_34;
  undefined4 local_30;
  undefined ***local_2c;
  undefined1 local_28;
  undefined4 local_24;
  undefined ***local_20;
  undefined1 local_1c;
  int *local_18;
  int local_14;
  int *local_c;
  int local_8;
  
  iVar3 = FUN_008b5310(); // GetCurrentFamilyID or similar
  FUN_008b4270(&local_c, iVar3, 0); // Allocator for list of crime scenes
  FUN_008b4270(&local_18, iVar3 == 0, 0); // Allocator for list of crimes matching family
  uVar4 = FUN_0043ff40(); // Get number of active crime scenes
  uVar6 = 0;
  if (uVar4 != 0) {
    do {
      iVar1 = *(int *)(*(int *)(DAT_012233a0 + 4) + uVar6 * 4); // Get crime scene data pointer
      if ((iVar1 != 0) && (iVar1 != 0x1f30)) {
        local_50 = iVar1 + -0x1ee8; // Offset to some crime scene field
        local_54 = &PTR_FUN_00e31e2c;
        local_4c = 0;
        if (local_50 != 0) {
          local_4c = *(undefined4 *)(iVar1 + -0x1ee4);
          *(int **)(iVar1 + -0x1ee4) = &local_50;
        }
        iVar2 = *(int *)(iVar1 + -0x38); // Family ID of crime
        if (*(int *)(iVar1 + -0x3c) == iVar3) { // Check if crime is by current family
          local_48 = DAT_0112f788;
          local_40 = 0;
          puVar5 = &local_48;
          local_44 = &local_54;
        }
        else {
          local_3c = DAT_0112f824;
          local_34 = 0;
          puVar5 = &local_3c;
          local_38 = &local_54;
        }
        FUN_00408a00(puVar5, 0); // Fire event/notification for crime (own family or other)
        if ((local_8 != 0) && (*local_c == iVar2)) {
          local_2c = &local_54;
          local_30 = DAT_0112f814;
          local_28 = 0;
          FUN_00408a00(&local_30, 0); // Fire threat notification
        }
        if ((local_14 != 0) && (*local_18 == iVar2)) {
          local_20 = &local_54;
          local_24 = DAT_0112f81c;
          local_1c = 0;
          FUN_00408a00(&local_24, 0); // Fire family-specific threat notification
        }
        if (local_50 != 0) {
          FUN_004daf90(&local_50); // Free or cleanup local_50
        }
        local_54 = &PTR_LAB_00e2f0c0;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar4);
  }
  DAT_0112ff60 = 1; // Set some flag that update is done
  // Check heat reduction logic
  if (*(float *)(DAT_0112b9b4 + 0x3c) <= *(float *)(DAT_01129908 + 0x14)) {
    fVar7 = *(float *)(DAT_01129908 + 0x14) - *(float *)(DAT_0112b9b4 + 0x3c);
    if ((*(uint *)(thisPtr + 0x7c) >> 0xb & 1) == 0) { // Check if bit 11 is set (some flag)
      FUN_00907ac0(0x20, fVar7); // Decrease heat
    }
    else if (DAT_01223484 != 0) {
      FUN_008a2c50(0x20, fVar7); // Alternative heat decrease
    }
  }
  if (local_18 != (int *)0x0) {
    FUN_009c8f10(local_18); // Free allocation
  }
  if (local_c != (int *)0x0) {
    FUN_009c8f10(local_c); // Free allocation
  }
  return;
}