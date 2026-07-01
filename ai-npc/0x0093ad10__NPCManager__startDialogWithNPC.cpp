// FUNC_NAME: NPCManager::startDialogWithNPC
void __thiscall NPCManager::startDialogWithNPC(int param_1, int param_2)
{
  char cVar1;
  int dialogObj;
  undefined1 *local_10;
  code *local_4;
  
  // +0x10c: pointer to current dialog state/active dialog
  **(undefined1 **)(param_1 + 0x10c) = 0;
  
  // +0x1f54: NPC flags - check bit 5 (maybe "isBusy" or "isInDialog")
  if ((*(uint *)(param_2 + 0x1f54) >> 5 & 1) == 0) {
    // +0x1ed4: NPC dialog data index/handle
    dialogObj = FUN_008c74d0(*(undefined4 *)(param_2 + 0x1ed4));
    if (dialogObj != 0) {
      // +0x8c: some dialog-related offset in the dialog object
      FUN_004d3b50(dialogObj + 0x8c);
      puVar3 = local_10;
      if (local_10 == (undefined1 *)0x0) {
        puVar3 = &DAT_0120546e;  // Empty string or null marker
      }
      cVar1 = FUN_005bd670(puVar3);  // Check if dialog is valid/available
      if (cVar1 != '\0') {
        puVar3 = local_10;
        if (local_10 == (undefined1 *)0x0) {
          puVar3 = &DAT_0120546e;
        }
        // Start dialog playback with this NPC
        // param_1+0x10c = dialog manager, param_2 = NPC handle, 0x80 = flags, 0 = unknown
        FUN_005c4660(*(undefined4 *)(param_1 + 0x10c), puVar3, 0x80, 0);
      }
      if (local_10 != (undefined1 *)0x0) {
        (*local_4)(local_10);  // Free temporary string
      }
    }
  }
  return;
}