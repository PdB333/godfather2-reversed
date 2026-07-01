// FUNC_NAME: DialogTreeManager::executeDialogAction
void __thiscall DialogTreeManager::executeDialogAction(int this, int actionId)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  uint uVar7;
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
  
  uStack_4 = 0x978a9a;
  // +0xf0: pointer to current dialog state string buffer
  **(undefined1 **)(this + 0xf0) = 0;
  iVar2 = DAT_011299c0; // global dialog tree manager data
  piVar6 = (int *)(DAT_011299c0 + 8);
  uVar7 = 0;
  if (*(int *)(DAT_011299c0 + 0xc) != 0) {
    do {
      iVar1 = *(int *)(*piVar6 + uVar7 * 4);
      iVar4 = FUN_00891980(); // get action type from node
      uVar3 = DAT_012234a4; // global string table
      if (iVar4 == actionId) {
        FUN_00604be0(); // begin string formatting
        // Initialize string objects
        local_1034 = (undefined1 *)0x0;
        local_1030 = 0;
        local_102c = 0;
        local_1028 = (code *)0x0;
        local_1024 = (undefined1 *)0x0;
        local_1020 = 0;
        local_101c = 0;
        local_1018 = (code *)0x0;
        local_1044 = (undefined1 *)0x0;
        local_1040 = 0;
        local_103c = 0;
        local_1038 = (code *)0x0;
        // Get localized strings for action
        FUN_00603330(0xed2ccd25,&local_1034); // get action text
        FUN_00603330(*(undefined4 *)(iVar1 + 0x80),&local_1024); // get speaker name
        FUN_00603330(*(undefined4 *)(iVar1 + 0x84),&local_1044); // get subtitle text
        puVar5 = local_1024;
        if (local_1024 == (undefined1 *)0x0) {
          puVar5 = &DAT_0120546e; // empty string
        }
        FUN_00604c10(0x6e,puVar5); // set speaker name in format
        puVar5 = local_1044;
        if (local_1044 == (undefined1 *)0x0) {
          puVar5 = &DAT_0120546e;
        }
        FUN_00604c10(0x72,puVar5); // set subtitle text in format
        local_1054 = (undefined1 *)0x0;
        local_1050 = 0;
        local_104c = 0;
        local_1048 = (code *)0x0;
        puVar5 = local_1034;
        if (local_1034 == (undefined1 *)0x0) {
          puVar5 = &DAT_0120546e;
        }
        FUN_006038a0(uVar3,local_1014,&local_1054,puVar5); // format the dialog string
        puVar5 = local_1054;
        if (local_1054 == (undefined1 *)0x0) {
          puVar5 = &DAT_0120546e;
        }
        FUN_005c4660(*(undefined4 *)(this + 0xf0),puVar5,0x100,local_1050); // copy to dialog buffer
        // Cleanup string objects
        if (local_1054 != (undefined1 *)0x0) {
          (*local_1048)(local_1054);
        }
        if (local_1044 != (undefined1 *)0x0) {
          (*local_1038)(local_1044);
        }
        if (local_1024 != (undefined1 *)0x0) {
          (*local_1018)(local_1024);
        }
        if (local_1034 != (undefined1 *)0x0) {
          (*local_1028)(local_1034);
        }
        FUN_00604c00(); // end string formatting
        break;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < *(uint *)(iVar2 + 0xc));
  }
  if (**(char **)(this + 0xf0) == '\0') {
    FUN_00977f30(); // handle empty dialog (skip/continue)
    return;
  }
  FUN_00977ec0(); // display dialog
  return;
}