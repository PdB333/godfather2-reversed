// FUNC_NAME: DebugManager::printDebugMessage
void DebugManager::printDebugMessage(int param_1, char param_2, int param_3)
{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 *puStack_40;
  int iStack_3c;
  code *pcStack_34;
  undefined **local_30;
  int local_2c;
  undefined4 local_28;
  undefined4 local_24;
  char local_20;
  undefined4 local_1c;
  int local_18;
  undefined4 local_14;
  undefined4 local_10;
  code *local_c;
  
  local_28 = 7;
  // Check if debug mode is active (0x12 = 18, likely a debug flag)
  if (*(char *)(DAT_012233b4 + 0x568) == '\x12') {
    local_28 = 3;
  }
  local_2c = 0;
  local_30 = &PTR_FUN_00d5c878;
  local_24 = param_1;
  local_20 = '\0';
  local_1c = 0xffffffff;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = (code *)0x0;
  
  // Begin debug output iteration
  FUN_00495960();
  cVar1 = FUN_00495980();
  while (cVar1 != '\0') {
    piVar2 = (int *)FUN_004959c0();
    (**(code **)(*piVar2 + 0x14))(&local_30);
    cVar1 = FUN_00495980();
  }
  
  // Check if we should print the message
  if (local_2c != 4) {
    iVar3 = FUN_0068f680(param_1);
    if ((iVar3 == 0) || (*(int *)(iVar3 + 8) == 0)) {
      if (local_20 != '\0') {
        if (param_2 != '\0') {
          FUN_00401060(); // Likely flush or newline
        }
        FUN_004d3b50(&local_18); // Format string
        if (puStack_40 != (undefined1 *)0x0) {
          (*pcStack_34)(puStack_40);
        }
        if (iStack_3c != 0) {
          FUN_004d3b50(&local_18);
          puVar4 = puStack_40;
          if (puStack_40 == (undefined1 *)0x0) {
            puVar4 = &DAT_0120546e;
          }
          FUN_004d4b00(param_3, "[c=CUSTOM1]%s[c=RESET] ", puVar4); // Color-coded debug output
          if (puStack_40 != (undefined1 *)0x0) {
            (*pcStack_34)(puStack_40);
          }
        }
      }
    }
    else {
      if (param_2 != '\0') {
        FUN_00401060();
      }
      FUN_004d4300(*(undefined4 *)(iVar3 + 8)); // Print debug string
    }
  }
  
  if (local_18 != 0) {
    (*local_c)(local_18);
  }
  return;
}