// Xbox PDB: EARS_Modules_PlayerTargetingSM_UpdatePassiveTargetHUD
// FUNC_NAME: HUDManager::updateLockOnIndicator
void __fastcall HUDManager::updateLockOnIndicator(int thisPtr)
{
  bool bIsDestructible;
  undefined4 uVar2;
  char cVar3;
  int *piVar4;
  uint uVar5;
  uint local_10;
  uint local_c;
  uint local_8;
  undefined4 local_4;
  
  local_4 = *(undefined4 *)(thisPtr + 0x58); // +0x58: currentTargetEntity
  piVar4 = (int *)FUN_007ab690(); // GetPlayerController()
  uVar5 = 0;
  if (piVar4 != (int *)0x0) {
    local_10 = 0;
    cVar3 = (**(code **)(*piVar4 + 0x10))(0x55859efa,&local_10); // PlayerController::getCurrentTarget()
    uVar5 = -(uint)(cVar3 != '\\0') & local_10;
  }
  local_8 = 0;
  if (piVar4 != (int *)0x0) {
    local_c = 0;
    cVar3 = (**(code **)(*piVar4 + 0x10))(0xa5975eb2,&local_c); // PlayerController::getAimTarget()
    local_8 = -(uint)(cVar3 != '\\0') & local_c;
  }
  bIsDestructible = false;
  if (piVar4 != (int *)0x0) {
    local_c = 0;
    cVar3 = (**(code **)(*piVar4 + 0x10))(0xa7039c8,&local_c); // PlayerController::getCrosshairTarget()
    uVar2 = local_4;
    if (((cVar3 != '\\0') && (local_c != 0)) && ((*(uint *)(local_c + 0x18c) >> 0x19 & 1) != 0)) {
      bIsDestructible = true;
    }
    if (uVar5 == 0) {
      if (local_8 == 0) {
        cVar3 = FUN_007f7c60(); // IsHUDVisible()
        if ((cVar3 == '\\0') && (bIsDestructible)) {
          FUN_007e6990(uVar2,piVar4,"hud_Destructible"); // ShowHUDWidget()
          return;
        }
      }
    }
    else {
      cVar3 = FUN_007f7c60(); // IsHUDVisible()
      if (cVar3 == '\\0') {
        cVar3 = FUN_007f7c60(); // IsHUDVisible()
        if (cVar3 == '\\0') {
          FUN_007e6990(uVar2,piVar4,"hud_passivelock"); // ShowHUDWidget()
          return;
        }
      }
    }
  }
  FUN_004df600(); // HideHUDWidget()
  FUN_004df600(); // HideHUDWidget()
  if (*(int *)(thisPtr + 0x26c) != 0) {
    FUN_004daf90((undefined4 *)(thisPtr + 0x26c)); // DestroyWidget()
    *(undefined4 *)(thisPtr + 0x26c) = 0;
  }
  return;
}