// FUNC_NAME: Player::handleGameMessage
undefined1 __thiscall Player::handleGameMessage(int this, undefined4 param_2, undefined4 param_3, undefined4 param_4, undefined4 messageType, undefined4 param_6)
{
  undefined1 result;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
  undefined1 local_31;
  undefined8 local_30;
  undefined1 local_28;
  undefined **local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined8 local_14;
  undefined4 local_c;
  undefined1 local_8;
  undefined4 local_4;
  
  uVar3 = DAT_00e445fc;
  local_31 = 1;
  switch(messageType) {
  case 0x23: // 35 - e.g. MSG_PLAYER_ENTER_VEHICLE
    uVar3 = *(undefined4 *)(this + 0x5c); // +0x5C: player's vehicle pointer
    FUN_007f63e0(1); // some vehicle entry function
    result = FUN_0076a790(); // get player state
    *(undefined1 *)(this + 0x84) = result; // +0x84: player state flag
    FUN_00939620(uVar3,4); // set vehicle state
    return 1;
  case 0x24: // 36 - e.g. MSG_PLAYER_EXIT_VEHICLE
    uVar3 = *(undefined4 *)(this + 0x5c);
    FUN_007f6420(1); // vehicle exit function
    FUN_009396c0(uVar3); // clear vehicle state
    return 1;
  case 0x25: // 37 - e.g. MSG_PLAYER_ACTION
    if (((uint)(*(int **)(this + 0x5c))[0x238] >> 10 & 1) != 0) { // check some flag in vehicle
      (**(code **)(**(int **)(this + 0x5c) + 0x260))(); // call vehicle action function
      return 1;
    }
    break;
  case 0x26: // 38 - e.g. MSG_PLAYER_SPAWN
    if ((*(int *)(this + 0x70) != 0) && (*(int *)(this + 0x70) != 0x48)) { // +0x70: some index
      iVar2 = *(int *)(this + 0x70);
      if ((iVar2 == 0) || (iVar2 == 0x48)) {
        iVar2 = 0;
      }
      else {
        iVar2 = iVar2 + -0xc;
      }
      FUN_00440590(&DAT_0112e020,iVar2,_DAT_00e51bd8,0,4); // some initialization
      FUN_0076a180(0x2000000); // set spawn flag
      local_30 = (longlong)ROUND(_DAT_00e51bd8 * DAT_00d60d04);
      uVar3 = FUN_0090e2d0(0,(undefined4)local_30,2,0,0,0); // create entity
      if (*(int *)(this + 0x70) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(this + 0x70) + -0x48;
      }
      *(undefined4 *)(iVar2 + 0xe4c) = uVar3; // store entity ID
      // Setup for some callback
      local_c = 0;
      local_14 = 0;
      local_24 = &PTR_FUN_00d5dbbc;
      local_1c = 0;
      local_18 = 0;
      local_8 = 0;
      local_4 = DAT_01205228;
      local_20 = 0x9b69c164;
      FUN_0044b210(*(undefined4 *)(this + 0x5c)); // some setup
      iVar2 = FUN_00471610(); // get some manager
      local_8 = 1;
      local_14 = *(undefined8 *)(iVar2 + 0x30);
      local_c = *(undefined4 *)(iVar2 + 0x38);
      local_30 = CONCAT44(&local_24,DAT_0112ad8c);
      local_28 = 0;
      FUN_00408a00(&local_30,0); // register callback
      FUN_006ad490(); // execute
      // Second callback setup
      local_c = 0;
      local_14 = 0;
      local_24 = &PTR_FUN_00d5dbbc;
      local_1c = 0;
      local_18 = 0;
      local_8 = 0;
      local_4 = DAT_01205228;
      local_20 = 0x3bd0fe1e;
      if (*(int *)(this + 0x70) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(this + 0x70) + -0x48;
      }
      FUN_0044b210(iVar2);
      iVar2 = FUN_00471610();
      local_8 = 1;
      local_14 = *(undefined8 *)(iVar2 + 0x30);
      local_c = *(undefined4 *)(iVar2 + 0x38);
      local_30 = CONCAT44(&local_24,DAT_0112ad8c);
      local_28 = 0;
      if (*(int *)(this + 0x5c) == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(this + 0x5c) + 0x3c;
      }
      FUN_00408bf0(&local_30,iVar2,0); // register callback with vehicle
      FUN_006ad490(); // execute
      return 1;
    }
    break;
  case 0x27: // 39 - e.g. MSG_PLAYER_UPDATE
    fVar4 = *(float *)(this + 0x88) + DAT_012067e8; // +0x88: some timer
    *(float *)(this + 0x88) = fVar4;
    FUN_00939760(*(undefined4 *)(this + 0x5c),fVar4,uVar3); // update vehicle
    return 1;
  default:
    local_31 = FUN_0073e610(param_2,param_3,param_4,messageType,param_6); // default handler
  }
  return local_31;
}