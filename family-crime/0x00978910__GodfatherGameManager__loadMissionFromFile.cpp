// FUNC_NAME: GodfatherGameManager::loadMissionFromFile
void __thiscall GodfatherGameManager::loadMissionFromFile(int this, int missionData)
{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined1 *local_1054;
  undefined4 local_1050;
  undefined4 local_104c;
  code *local_1048;
  undefined1 *local_1044;
  undefined4 local_1040;
  undefined4 local_103c;
  code *local_1038;
  undefined1 *local_1034;
  undefined4 local_1030;
  undefined4 local_102c;
  code *local_1028;
  undefined1 *local_1024;
  undefined4 local_1020;
  undefined4 local_101c;
  code *local_1018;
  undefined1 local_1014 [4112];
  undefined4 uStack_4;
  
  uVar1 = DAT_012234a4;
  uStack_4 = 0x97891a;
  FUN_00604be0(); // push/pop context
  local_1034 = (undefined1 *)0x0;
  local_1030 = 0;
  local_102c = 0;
  local_1028 = (code *)0x0;
  local_1044 = (undefined1 *)0x0;
  local_1040 = 0;
  local_103c = 0;
  local_1038 = (code *)0x0;
  local_1024 = (undefined1 *)0x0;
  local_1020 = 0;
  local_101c = 0;
  local_1018 = (code *)0x0;
  // Get mission name hash (0x3808126b is likely "mission" or similar)
  FUN_00603330(0x3808126b, &local_1034);
  // Get mission file path from missionData +0xB4
  FUN_00603330(*(undefined4 *)(missionData + 0xb4), &local_1044);
  iVar2 = *(int *)(missionData + 0x204);
  if (iVar2 == 0) {
    iVar2 = *(int *)(missionData + 0x100);
  }
  // Get mission type/ID
  FUN_00603330(iVar2, &local_1024);
  puVar3 = local_1044;
  if (local_1044 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e; // empty string
  }
  FUN_00604c10(0x6e, puVar3); // log mission file path
  puVar3 = local_1024;
  if (local_1024 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;
  }
  FUN_00604c10(0x72, puVar3); // log mission type
  local_1054 = (undefined1 *)0x0;
  local_1050 = 0;
  local_104c = 0;
  local_1048 = (code *)0x0;
  puVar3 = local_1034;
  if (local_1034 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;
  }
  // Load mission file into buffer
  FUN_006038a0(uVar1, local_1014, &local_1054, puVar3);
  puVar3 = local_1054;
  if (local_1054 == (undefined1 *)0x0) {
    puVar3 = &DAT_0120546e;
  }
  // Parse mission data into this+0xF0 (likely mission manager)
  FUN_005c4660(*(undefined4 *)(this + 0xf0), puVar3, 0x100, local_1050);
  FUN_00977ec0(); // cleanup/notify
  if (local_1054 != (undefined1 *)0x0) {
    (*local_1048)(local_1054); // free buffer
  }
  if (local_1024 != (undefined1 *)0x0) {
    (*local_1018)(local_1024); // free string
  }
  if (local_1044 != (undefined1 *)0x0) {
    (*local_1038)(local_1044); // free string
  }
  if (local_1034 != (undefined1 *)0x0) {
    (*local_1028)(local_1034); // free string
  }
  FUN_00604c00(); // pop context
  return;
}