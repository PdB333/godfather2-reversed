// FUNC_NAME: setSkipIntroFlag
void setSkipIntroFlag(int param_1)
{
  int iVar1;
  int *piVar2;
  int local_4;
  
  iVar1 = isDebugMode(); // FUN_00483a50
  if (iVar1 == 1) {
    g_skipIntroFlag = (param_1 == 0); // DAT_0120535b
    applySkipIntroSetting(); // FUN_00433fa0
    return;
  }
  // Else: store the flag via config manager vtable
  piVar2 = (int *)(g_configManager + 0x14); // DAT_01206880 + 0x14
  **(undefined4 **)(g_configManager + 0x14) = &PTR_FUN_00e50c48; // set vtable pointer
  *piVar2 = *piVar2 + 4; // advance to next vtable entry
  local_4 = param_1;
  writeConfigValue(&local_4, 4, 4); // FUN_0049c430 (source, size, count)
  return;
}