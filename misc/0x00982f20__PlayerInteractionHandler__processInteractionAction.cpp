// FUNC_NAME: PlayerInteractionHandler::processInteractionAction

undefined4 __thiscall PlayerInteractionHandler::processInteractionAction(int thisPtr, int actionId)
{
  uint *puVar1;
  int iVar2;
  undefined4 local_c;
  undefined4 local_8;
  undefined1 local_4;
  
  iVar2 = getPrimaryInteractActionID(); // FUN_00466840
  if (actionId == iVar2) {
    local_c = gStrInteractDenied; // DAT_01130410
    if (((*(int *)(thisPtr + 0x7c) == 0) && (*(int *)(thisPtr + 0x6c) != 0)) &&
       (iVar2 = *(int *)(thisPtr + 0x4c + *(int *)(thisPtr + 0x6c) * 4),
       *(int *)(iVar2 + 0xc) != 0xd)) {
      playSound(*(undefined4 *)(iVar2 + 8), 0); // FUN_00982c00
      local_c = gStrInteractionUnavailable; // DAT_01130380
      local_8 = 0;
      local_4 = 0;
      showTextPrompt(&local_c, 0); // FUN_00408a00
      return 0;
    }
    goto LAB_00982fa2;
  }
  iVar2 = getSecondaryInteractActionID(); // FUN_00466860
  if (actionId == iVar2) {
    if (*(int *)(thisPtr + 0x7c) == 0) {
      if (((*(int *)(thisPtr + 0x6c) != 0) &&
          (puVar1 = *(uint **)(thisPtr + 0x4c + *(int *)(thisPtr + 0x6c) * 4),
          (*puVar1 >> 2 & 1) == 0)) && (puVar1[3] != 0xd)) {
        playSound(0xffffffff, 0);
        local_c = gStrInteractionSecondaryDenied; // DAT_01130190
        goto LAB_00982fa2;
      }
    }
    else if (*(code **)(thisPtr + 0x8c) != (code *)0x0) {
      (**(code **)(thisPtr + 0x8c))(); // call callback
      local_c = gStrInteractionSecondaryDenied; // DAT_01130190
      goto LAB_00982fa2;
    }
    local_c = gStrInteractDenied; // DAT_01130410
LAB_00982fa2:
    local_4 = 0;
    local_8 = 0;
    showTextPrompt(&local_c, 0); // FUN_00408a00
    return 0;
  }
  switch(actionId) {
  case 8: // likely "select" button
    if ((*(int *)(thisPtr + 0x7c) == 0) && (*(int *)(thisPtr + 0x6c) != 0)) {
      selectOption(0xffffffff); // FUN_00982100 with -1 (cancel?)
      return 0;
    }
    break;
  case 9: // likely "back" button
    if ((*(int *)(thisPtr + 0x7c) == 0) && (*(int *)(thisPtr + 0x6c) != 0)) {
      selectOption(1); // FUN_00982100 with 1 (confirm?)
      return 0;
    }
    break;
  case 10: // specific interaction action
    iVar2 = *(int *)(thisPtr + 0x4c + *(int *)(thisPtr + 0x6c) * 4);
    if (*(int *)(iVar2 + 0xc) != 0xe) {
      return 0;
    }
    if (*(char *)(iVar2 + 0xec) != '\0') {
      *(undefined1 *)(iVar2 + 0xee) = 1; // set flag
LAB_009830ac:
      playSound(0xffffffff, 0);
      showTextImmediate(&gStrInteractionUnavailable, 0); // FUN_00402050
      return 0;
    }
    goto LAB_009830ef;
  case 0xc: // another interaction action
    iVar2 = *(int *)(thisPtr + 0x4c + *(int *)(thisPtr + 0x6c) * 4);
    if (*(int *)(iVar2 + 0xc) != 0xe) {
      return 0;
    }
    if (*(char *)(iVar2 + 0xed) != '\0') {
      *(undefined1 *)(iVar2 + 0xef) = 1; // set flag
      goto LAB_009830ac;
    }
LAB_009830ef:
    showTextImmediate(&gStrInteractDenied, 0); // FUN_00402050
  }
  return 0;
}