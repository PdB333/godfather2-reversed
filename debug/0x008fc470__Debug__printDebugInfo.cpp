// FUNC_NAME: Debug::printDebugInfo
void __fastcall Debug::printDebugInfo(int this)
{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  char **ppcVar4;
  char *local_30;
  int local_2c;
  undefined4 local_28;
  code *local_24;
  char *local_20;
  undefined4 local_1c;
  undefined4 local_18;
  code *local_14;
  char *local_10;
  int local_c;
  undefined4 local_8;
  code *local_4;
  
  // Check if any of the debug flags are set (offsets +0x58, +0x5c, +0x60, +0x64)
  if (((((*(int *)(this + 0x58) != 0) || (*(int *)(this + 0x5c) != 0)) ||
       (*(int *)(this + 0x60) != 0)) || (*(int *)(this + 100) != 0)) &&
     // Check if global debug state matches
     (iVar1 = *(int *)(DAT_011299c4 + 0x1c), iVar1 != 0)) {
    // Verify all debug flags match the global state
    if (*(int *)(this + 0x58) != *(int *)(iVar1 + 0x20)) {
      return;
    }
    if (*(int *)(this + 0x5c) != *(int *)(iVar1 + 0x24)) {
      return;
    }
    if (*(int *)(this + 0x60) != *(int *)(iVar1 + 0x28)) {
      return;
    }
    if (*(int *)(this + 100) != *(int *)(iVar1 + 0x2c)) {
      return;
    }
  }
  
  // Initialize string buffers
  local_10 = (char *)0x0;
  local_c = 0;
  local_8 = 0;
  local_4 = (code *)0x0;
  local_30 = (char *)0x0;
  local_2c = 0;
  local_28 = 0;
  local_24 = (code *)0x0;
  local_20 = (char *)0x0;
  local_1c = 0;
  local_18 = 0;
  local_14 = (code *)0x0;
  
  // Get debug strings from object (offsets +0x50 and +0x54)
  if (*(int *)(this + 0x50) != 0) {
    FUN_00603330(*(int *)(this + 0x50), &local_10);
  }
  if (*(int *)(this + 0x54) != 0) {
    FUN_00603330(*(int *)(this + 0x54), &local_30);
  }
  
  // Combine strings if both exist
  if (local_c == 0) {
    if (local_2c == 0) goto LAB_008fc582;
    ppcVar4 = &local_30;
  }
  else {
    if (local_2c != 0) {
      pcVar3 = local_30;
      if (local_30 == (char *)0x0) {
        pcVar3 = &DAT_0120546e;  // Empty string
      }
      pcVar2 = local_10;
      if (local_10 == (char *)0x0) {
        pcVar2 = &DAT_0120546e;  // Empty string
      }
      FUN_004d4ad0(&local_20, "%s\n%s", pcVar2, pcVar3);
      goto LAB_008fc582;
    }
    ppcVar4 = &local_10;
  }
  FUN_004d3e20(ppcVar4);
  
LAB_008fc582:
  pcVar3 = local_20;
  if (local_20 == (char *)0x0) {
    pcVar3 = &DAT_0120546e;  // Empty string
  }
  FUN_008fce70(0, pcVar3);  // Output debug string
  
  // Clean up allocated strings
  if (local_20 != (char *)0x0) {
    (*local_14)(local_20);
  }
  if (local_30 != (char *)0x0) {
    (*local_24)(local_30);
  }
  if (local_10 != (char *)0x0) {
    (*local_4)(local_10);
  }
  return;
}