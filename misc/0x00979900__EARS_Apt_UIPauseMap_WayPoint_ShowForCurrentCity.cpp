// Xbox PDB: EARS_Apt_UIPauseMap_WayPoint_ShowForCurrentCity
// FUNC_NAME: WaypointManager::spawnWaypoint
void __thiscall WaypointManager::spawnWaypoint(int this, char param_2)
{
  int iVar1;
  int *piVar2;
  int local_a4;
  undefined4 local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined1 local_60 [16];
  undefined1 local_50 [76];
  
  if (param_2 == '\0') {
LAB_00979a5a:
    if (*(int *)(this + 0xb0) != 0) {
      FUN_004df600(); // destroyWaypoint
    }
  }
  else {
    if (*(int *)(this + 0xa0) != 0) {
      if ((*(int *)(this + 0x14c) == 1) || (1 < *(int *)(this + 0x14c) - 3U)) {
        iVar1 = *(int *)(this + 0x140); // +0x140 = waypointTypeA
      }
      else {
        iVar1 = *(int *)(this + 0x144); // +0x144 = waypointTypeB
      }
      if (*(int *)(this + 0xa0) != iVar1) goto LAB_00979a5a;
    }
    local_64 = _DAT_00d5780c; // global zero constant
    local_78 = _DAT_00d5780c;
    local_8c = _DAT_00d5780c;
    local_a0 = _DAT_00d5780c;
    local_94 = 0;
    local_90 = 0;
    local_98 = 0;
    local_9c = 0;
    local_84 = 0;
    local_7c = 0;
    local_80 = 0;
    local_88 = 0;
    local_74 = 0;
    local_70 = *(undefined4 *)(this + 0xa4); // +0xa4 = positionX
    local_6c = *(undefined4 *)(this + 0xa8); // +0xa8 = positionY
    local_68 = *(undefined4 *)(this + 0xac); // +0xac = positionZ
    FUN_0044b4e0(local_50,&local_a0); // createWaypointData
    piVar2 = (int *)(this + 0xb0); // +0xb0 = currentWaypointPtr
    if (*piVar2 != 0) {
      FUN_004df720(local_50); // updateWaypoint
      return;
    }
    FUN_004eacb0(PTR_s_dv_waypoint_00e5759c); // getWaypointTemplate
    FUN_004df420(&local_a4,local_60,local_50,0x2ff,4,0,0xffffffff,0); // allocateWaypoint
    if (*piVar2 != 0) {
      *(undefined4 *)(*piVar2 + 8) = 0;
      *piVar2 = 0;
    }
    *piVar2 = local_a4;
    if (local_a4 != 0) {
      *(int **)(local_a4 + 8) = piVar2;
      return;
    }
  }
  return;
}