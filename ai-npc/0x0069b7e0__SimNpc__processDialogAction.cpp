// FUNC_NAME: SimNpc::processDialogAction
undefined4 __thiscall SimNpc::processDialogAction(int thisPtr, undefined4 param_2, int param_3)

{
  char cVar1;
  int local_50 [3];
  code *local_44;
  int local_40 [3];
  code *local_34;
  int local_30 [3];
  code *local_24;
  int aiStack_20 [3];
  code *pcStack_14;
  int local_10;
  code *pcStack_4;
  
  FUN_004d3bc0(param_2);
  local_40[0] = 0;
  local_40[1] = 0;
  local_40[2] = 0;
  local_34 = (code *)0x0;
  local_50[0] = 0;
  local_50[1] = 0;
  local_50[2] = 0;
  local_44 = (code *)0x0;
  cVar1 = FUN_004d5210(&DAT_00d5ceec,local_40,local_50);
  if (cVar1 != '\\0') {
    FUN_0069b040(local_40);
    FUN_0069b040(local_50);
    if ((*(uint *)(param_3 + 0x1c) >> 1 & 1) != 0) {
      cVar1 = FUN_00699ec0(local_40);
      if (cVar1 != '\\0') {
        local_30[0] = 0;
        local_30[2] = 0;
        local_30[1] = 0;
        FUN_00698f20(*(undefined4 *)(thisPtr + 0x28),thisPtr + 0x3c,thisPtr + 0x2c,local_30,0);
        if (*(code **)(thisPtr + 4) != (code *)0x0) {
          (**(code **)(thisPtr + 4))(2,local_40,local_50);
        }
        if (local_30[0] != 0) {
          (*local_24)(local_30[0]);
        }
      }
    }
    if ((*(uint *)(param_3 + 0x1c) >> 2 & 1) != 0) {
      local_30[0] = 0;
      local_30[1] = 0;
      local_30[2] = 0;
      local_24 = (code *)0x0;
      cVar1 = FUN_0069b130(local_50,local_30);
      if (cVar1 != '\\0') {
        aiStack_20[0] = 0;
        aiStack_20[2] = 0;
        aiStack_20[1] = 0;
        FUN_00698f20(*(undefined4 *)(thisPtr + 0x28),thisPtr + 0x3c,thisPtr + 0x2c,aiStack_20,0);
        if (*(code **)(thisPtr + 4) != (code *)0x0) {
          (**(code **)(thisPtr + 4))(4,local_40,local_50);
        }
        if (aiStack_20[0] != 0) {
          (*pcStack_14)(aiStack_20[0]);
        }
      }
      if (local_30[0] != 0) {
        (*local_24)(local_30[0]);
      }
    }
    FUN_0069b380(local_40);
    FUN_004d3e20(local_50);
    if (local_50[0] != 0) {
      (*local_44)(local_50[0]);
    }
    if (local_40[0] != 0) {
      (*local_34)(local_40[0]);
    }
    if (local_10 != 0) {
      (*pcStack_4)(local_10);
    }
    return 1;
  }
  if (local_50[0] != 0) {
    (*local_44)(local_50[0]);
  }
  if (local_40[0] != 0) {
    (*local_34)(local_40[0]);
  }
  if (local_10 != 0) {
    (*pcStack_4)(local_10);
  }
  return 0;
}