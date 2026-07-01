// FUNC_NAME: DebugCommands::handleInputAction
undefined4 __thiscall FUN_00912670(undefined4 param_1)

{
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  switch(param_1) {
  case 6:
    FUN_005a04a0("MoveLeft",0,&DAT_00d84448,0);
    local_c = DAT_011304d8;
    break;
  case 7:
    FUN_005a04a0("MoveRight",0,&DAT_00d84448,0);
    local_c = DAT_011304d8;
    break;
  case 8:
    FUN_005a04a0("MoveUp",0,&DAT_00d84448,0);
    local_c = DAT_011301c0;
    break;
  case 9:
    FUN_005a04a0("MoveDown",0,&DAT_00d84448,0);
    local_c = DAT_011301c0;
    break;
  default:
    goto switchD_00912684_default;
  }
  local_8 = 0;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
switchD_00912684_default:
  return 0;
}