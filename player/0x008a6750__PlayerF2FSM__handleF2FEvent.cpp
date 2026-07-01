// FUNC_NAME: PlayerF2FSM::handleF2FEvent
void PlayerF2FSM::handleF2FEvent(int param_1, int param_2)
{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  int *piVar5;
  undefined4 uVar6;
  int local_4c;
  undefined4 local_48;
  undefined **ppuStack_44;
  int iStack_40;
  undefined4 uStack_3c;
  undefined4 uStack_38;
  undefined ***pppuStack_34;
  undefined1 uStack_30;
  undefined4 uStack_2c;
  undefined ***pppuStack_28;
  undefined1 uStack_24;
  undefined **ppuStack_20;
  int iStack_1c;
  undefined4 uStack_18;
  undefined4 uStack_14;
  int iStack_10;
  int iStack_c;
  undefined4 uStack_8;
  uint uStack_4;
  
  iVar3 = param_2;
  iVar2 = param_1;
  local_4c = *(int *)(param_1 + 0x31b0); // +0x31b0: current F2F target
  local_48 = 0;
  if (local_4c != 0) {
    local_48 = *(undefined4 *)(local_4c + 4); // +0x04: next pointer in linked list
    *(int **)(local_4c + 4) = &local_4c; // remove from list
    if (((int *)(local_4c + -0x48) != (int *)0x0) && (local_4c != *(int *)(param_2 + 0xc))) {
      param_1 = 0;
      cVar4 = (**(code **)(*(int *)(local_4c + -0x48) + 0x10))(0x55859efa,&param_1); // check if entity is valid
      if ((cVar4 != '\\0') &&
         (((param_1 != 0 && (*(int *)(param_1 + 0x1ef8) != *(int *)(iVar2 + 0x1ef8))) &&
          (*(int *)(param_1 + 0x1ef4) != *(int *)(iVar2 + 0x1ef4))))) {
        FUN_008a6510(DAT_0112ebcc,*(int *)(param_1 + 0x1ef8)); // send F2F event to target
      }
    }
  }
  if ((*(int *)(iVar3 + 0xc) != 0) && (*(int *)(iVar3 + 0xc) != 0x48)) {
    if (*(int *)(iVar3 + 0xc) == 0) {
      piVar5 = (int *)0x0;
    }
    else {
      piVar5 = (int *)(*(int *)(iVar3 + 0xc) + -0x48);
    }
    param_1 = 0;
    cVar4 = (**(code **)(*piVar5 + 0x10))(0x55859efa,&param_1); // check if entity is valid
    if ((cVar4 != '\\0') && (param_1 != 0)) {
      iStack_c = *(int *)(iVar2 + 0x1ef8); // +0x1ef8: player ID
      uStack_18 = DAT_0112b6fc;
      iVar1 = *(int *)(param_1 + 0x1ef8); // target player ID
      uStack_8 = 0;
      uStack_4 = 0;
      ppuStack_20 = &PTR_LAB_00d77a04;
      uStack_14 = 1;
      uVar6 = DAT_0112ebd4;
      if (*(int *)(param_1 + 0x1ef4) != *(int *)(iVar2 + 0x1ef4)) { // different family
        if (*(char *)(iVar2 + 0x2454) == '\\0') { // not in combat
          uVar6 = DAT_0112ebe4;
          if ((*(uint *)(param_1 + 0x1ee0) >> 7 & 1) == 0) { // target not aiming
            uVar6 = DAT_0112ebf4;
          }
          uStack_4 = 2; // aggressive
        }
        else {
          uVar6 = DAT_0112ebdc;
          if (*(uint *)(iVar3 + 0x3c) == *(uint *)(param_1 + 0x68c) >> 2) { // same weapon type
            uStack_4 = 1; // defensive
            uVar6 = DAT_0112ec74;
          }
        }
      }
      iStack_1c = *(int *)(iVar3 + 0x30); // +0x30: event type
      if (iStack_1c == 2) {
        switch(*(undefined4 *)(iVar3 + 0x34)) { // +0x34: event subtype
        case 1:
          uStack_4 = uStack_4 | 4; // punch
          break;
        case 2:
          uStack_4 = uStack_4 | 8; // kick
          break;
        case 3:
          uStack_4 = uStack_4 | 0x10; // grab
          break;
        case 4:
          uStack_4 = uStack_4 | 0x20; // throw
          break;
        case 5:
          uStack_4 = uStack_4 | 0x40; // weapon attack
        }
      }
      pppuStack_34 = &ppuStack_20;
      uStack_38 = DAT_0112ecfc;
      uStack_30 = 0;
      iStack_10 = iVar1;
      FUN_00408a00(&uStack_38,0); // initialize event data
      FUN_008a6510(uVar6,iVar1); // send F2F event
      iStack_40 = iVar2 + 0x48; // +0x48: event queue
      ppuStack_44 = &PTR_FUN_00e31e2c;
      uStack_3c = 0;
      if (iStack_40 != 0) {
        uStack_3c = *(undefined4 *)(iVar2 + 0x4c); // +0x4c: next event
        *(int **)(iVar2 + 0x4c) = &iStack_40; // push event
      }
      pppuStack_28 = &ppuStack_44;
      uStack_24 = 0;
      uStack_2c = DAT_0112ebc4;
      if (iStack_10 != iStack_c) { // different player
        uStack_2c = DAT_0112ebb8;
      }
      FUN_00408a00(&uStack_2c,0); // initialize event data
      if (iStack_40 != 0) {
        FUN_004daf90(&iStack_40); // process event queue
      }
    }
  }
  if (local_4c != 0) {
    FUN_004daf90(&local_4c); // cleanup
  }
  return;
}