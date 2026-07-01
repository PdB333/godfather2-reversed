// FUNC_NAME: UIListMenu::moveSelectionUp
void __fastcall UIListMenu::moveSelectionUp(int this)
{
  uint uVar1;
  char *actionName;
  undefined1 buffer [4];            // for string formatting
  undefined4 local_10c;
  undefined4 local_108;
  undefined1 local_104;
  char selectionDisabledFlag [256];  // flag buffer

  // +0x50: mIsDrop? (bool)
  if (*(char *)(this + 0x50) == '\0') {
    // Normal move up - check if list wrapping and if next item is disabled
    if (*(int *)(this + 0x58) == 1) {
      // +0x54: mCurrentIndex
      // +0x60: mItemCount
      uVar1 = (*(int *)(this + 0x54) + -1 + *(uint *)(this + 0x60)) %
              *(uint *)(this + 0x60);
      // Format item ID into buffer
      FUN_00910180(buffer, &DAT_00e3266c, uVar1);
      selectionDisabledFlag[0] = '\0';
      // Check if this item is disabled
      FUN_005a04a0("IsSelectionDisabled", selectionDisabledFlag, &DAT_00d90fa8, 1, buffer);
      // Skip disabled items
      while (selectionDisabledFlag[0] == '1') {
        uVar1 = ((*(uint *)(this + 0x60) - 1) + uVar1) % *(uint *)(this + 0x60);
        FUN_00910180(buffer, &DAT_00e3266c, uVar1);
        selectionDisabledFlag[0] = '\0';
        FUN_005a04a0("IsSelectionDisabled", selectionDisabledFlag, &DAT_00d90fa8, 1, buffer);
      }
      // Set new selected index
      FUN_00986bd0(uVar1);
      goto LAB_00987f2f;
    }
    actionName = "MoveUp";
  }
  else {
    // Drop-down mode - move selection up within dropdown
    actionName = "MoveDropUp";
  }
  // Fire the generic move event
  FUN_005a04a0(actionName, 0, &DAT_00d90fa8, 0);
  
LAB_00987f2f:
  // Sound effect - play menu move sound
  local_10c = DAT_011302b0;
  local_108 = 0;
  local_104 = 0;
  FUN_00408a00(&local_10c, 0);
  return;
}