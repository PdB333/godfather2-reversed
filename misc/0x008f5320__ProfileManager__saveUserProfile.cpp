// FUNC_NAME: ProfileManager::saveUserProfile
void ProfileManager::saveUserProfile(undefined2 **param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  undefined1 *puVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined1 *puVar8;
  char *pcVar9;
  undefined1 *local_1074; // +0x00: userProfileNumber string
  undefined4 local_1070; // +0x04: allocator
  undefined4 local_106c; // +0x08: allocator
  code *local_1068; // +0x0C: deallocator
  char *local_1064; // +0x10: full path string
  undefined4 local_1060; // +0x14: allocator
  undefined4 local_105c; // +0x18: allocator
  code *local_1058; // +0x1C: deallocator
  undefined1 *local_1054; // +0x20: profile directory string
  undefined4 local_1050; // +0x24: allocator
  undefined4 local_104c; // +0x28: allocator
  code *local_1048; // +0x2C: deallocator
  undefined1 *local_1044; // +0x30: save directory string
  undefined4 local_1040; // +0x34: allocator
  undefined4 local_103c; // +0x38: allocator
  code *local_1038; // +0x3C: deallocator
  undefined2 *local_1034; // +0x40: profile number string
  undefined4 local_1030; // +0x44: allocator
  undefined4 local_102c; // +0x48: allocator
  code *pcStack_1028; // +0x4C: deallocator
  undefined2 *local_1024; // +0x50: save file name
  undefined4 local_1020; // +0x54: save file size
  code *local_1018; // +0x58: deallocator
  undefined1 local_1014 [4112]; // +0x5C: buffer for profile number string
  undefined4 uStack_4; // +0x105C: return address
  // Total stack frame: 0x1060 bytes
  
  uVar2 = DAT_012234a4; // global config data
  uStack_4 = 0x8f532a;
  local_1074 = (undefined1 *)0x0;
  local_1070 = 0;
  local_106c = 0;
  local_1068 = (code *)0x0;
  FUN_00604be0(); // beginMemoryScope
  uVar3 = FUN_008f2010(); // getCurrentUserProfileNumber
  FUN_00604c80(0x6e,uVar3); // setMemoryScopeTag(0x6e, profileNumber)
  FUN_006038a0(uVar2,local_1014,&local_1074,"$user_profile_number"); // getConfigString
  local_1034 = (undefined2 *)0x0;
  local_102c = 0;
  local_1030 = 0;
  FUN_008f4aa0(&local_1034); // getSaveDirectory
  local_1054 = (undefined1 *)0x0;
  local_1050 = 0;
  local_104c = 0;
  local_1048 = (code *)0x0;
  puVar4 = local_1034;
  if (local_1034 == (undefined2 *)0x0) {
    puVar4 = &DAT_00e2df14; // empty string
  }
  FUN_004d4570(puVar4); // stringLength
  local_1044 = (undefined1 *)0x0;
  local_1040 = 0;
  local_103c = 0;
  local_1038 = (code *)0x0;
  FUN_008f2280(&local_1044); // getProfileDirectory
  local_1064 = (char *)0x0;
  local_1060 = 0;
  local_105c = 0;
  local_1058 = (code *)0x0;
  puVar8 = local_1044;
  if (local_1044 == (undefined1 *)0x0) {
    puVar8 = &DAT_0120546e; // empty string
  }
  puVar7 = local_1054;
  if (local_1054 == (undefined1 *)0x0) {
    puVar7 = &DAT_0120546e; // empty string
  }
  puVar5 = local_1074;
  if (local_1074 == (undefined1 *)0x0) {
    puVar5 = &DAT_0120546e; // empty string
  }
  FUN_004d4ad0(&local_1064,"%s%s%s%s%s",puVar5,&DAT_00d8107c,puVar7,&DAT_00d8107c,puVar8); // stringFormat
  pcVar9 = local_1064;
  if (local_1064 == (char *)0x0) {
    pcVar9 = &DAT_0120546e; // empty string
  }
  pcVar6 = pcVar9;
  do {
    cVar1 = *pcVar6;
    pcVar6 = pcVar6 + 1;
  } while (cVar1 != '\0');
  FUN_004dba80(pcVar9,(int)pcVar6 - (int)(pcVar9 + 1)); // writeFile
  if (param_1 != &local_1024) {
    puVar4 = local_1024;
    if (local_1024 == (undefined2 *)0x0) {
      puVar4 = &DAT_00e2df14; // empty string
    }
    FUN_004dbb10(puVar4,0,local_1020); // freeString
  }
  if (local_1024 != (undefined2 *)0x0) {
    (*local_1018)(local_1024); // deallocate
  }
  if (local_1064 != (char *)0x0) {
    (*local_1058)(local_1064); // deallocate
  }
  if (local_1044 != (undefined1 *)0x0) {
    (*local_1038)(local_1044); // deallocate
  }
  if (local_1054 != (undefined1 *)0x0) {
    (*local_1048)(local_1054); // deallocate
  }
  if (local_1034 != (undefined2 *)0x0) {
    (*pcStack_1028)(local_1034); // deallocate
  }
  FUN_00604c00(); // endMemoryScope
  if (local_1074 != (undefined1 *)0x0) {
    (*local_1068)(local_1074); // deallocate
  }
  return;
}