// FUNC_NAME: CrashHandler::reportOrSomethingWithCallStack
void __fastcall CrashHandler::crashReport(int param_1)

{
  int iVar1;
  undefined4 local_24;
  undefined ***local_20;
  undefined1 local_1c;
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined8 local_c;
  undefined4 local_4;
  
  local_18 = &PTR_FUN_00d76668;
  local_14 = 0;
  local_10 = 0;
  if ((param_1 != 0) && (param_1 + 0x48 != 0)) {
    local_10 = *(undefined4 *)(param_1 + 0x4c);
    *(int **)(param_1 + 0x4c) = &local_14;
    local_14 = param_1 + 0x48;
  }
  iVar1 = FUN_00471610();
  local_c = *(undefined8 *)(iVar1 + 0x30);
  local_4 = *(undefined4 *)(iVar1 + 0x38);
  local_20 = &local_18;
  local_24 = DAT_0112adb8;
  local_1c = 0;
  FUN_00408a00(&local_24,0);
  if (local_14 != 0) {
    FUN_004daf90(&local_14);
  }
  return;
}