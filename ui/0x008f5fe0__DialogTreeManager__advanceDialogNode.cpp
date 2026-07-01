// FUNC_NAME: DialogTreeManager::advanceDialogNode
void __thiscall DialogTreeManager::advanceDialogNode(int this, int nodeIndex)
{
  char cVar1;
  char *pcVar2;
  undefined2 *puVar3;
  undefined4 *puVar4;
  undefined1 *puVar5;
  undefined2 *local_578 [3];
  code *local_56c;
  int iStack_568;
  code *pcStack_55c;
  char local_558 [64];
  char local_518 [256];
  undefined4 uStack_418;
  
  if (nodeIndex == -1) {
    // End of dialog tree - close dialog
    DialogTreeManager::closeDialog();
    DialogTreeManager::setDialogState(2); // State: Closed
    return;
  }
  
  // Get dialog node data at offset (nodeIndex * 0x558 + 0x38) from this
  DialogTreeManager::getNodeData(nodeIndex * 0x558 + 0x38 + this);
  DialogTreeManager::closeDialog();
  
  // Calculate length of dialog text string (local_518)
  pcVar2 = local_518;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_004dba80(local_518,(int)pcVar2 - (int)(local_518 + 1)); // Likely string copy/format
  
  puVar3 = local_578[0];
  if (local_578[0] == (undefined2 *)0x0) {
    puVar3 = &DAT_00e2df14; // Default speaker name
  }
  FUN_00acc6d0(puVar3); // Set speaker name
  
  if (local_578[0] != (undefined2 *)0x0) {
    (*local_56c)(local_578[0]); // Free speaker name string
  }
  
  // Play dialog audio (param_1 + 0x30 = audio ID, param_1 + 0x34 = audio bank)
  FUN_008f1e20(3,*(undefined4 *)(this + 0x30),*(undefined4 *)(this + 0x34));
  FUN_008f2000(uStack_418); // Start dialog playback
  
  // Calculate length of subtitle text (local_558)
  pcVar2 = local_558;
  do {
    cVar1 = *pcVar2;
    pcVar2 = pcVar2 + 1;
  } while (cVar1 != '\0');
  FUN_004dba80(local_558,(int)pcVar2 - (int)(local_558 + 1)); // Copy subtitle
  
  puVar4 = (undefined4 *)FUN_008f3600(local_578); // Get response options
  puVar5 = (undefined1 *)*puVar4;
  if (puVar5 == (undefined1 *)0x0) {
    puVar5 = &DAT_0120546e; // Default response text
  }
  FUN_008f5d30(puVar5,0); // Set response options
  
  if (iStack_568 != 0) {
    (*pcStack_55c)(iStack_568); // Free response data
  }
  
  if (local_578[0] != (undefined2 *)0x0) {
    (*local_56c)(local_578[0]); // Free speaker name
  }
  
  FUN_008f2020(); // Finalize dialog display
  return;
}