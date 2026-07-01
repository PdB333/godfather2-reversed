// FUNC_NAME: UISelectionController::moveSelectionDown
// Function address: 0x00987f60
// Moves the selection down in a UI list. Handles wrap-around and disabled item skipping.
void __thiscall UISelectionController::moveSelectionDown(UISelectionController *this)
{
  char keyBuffer[4];
  int dummy;
  char soundBuffer; // placeholder for audio struct
  char disabledFlagBuffer[256]; // buffer for reading property

  if (!*(char *)((int)this + 0x50)) { // +0x50: mIsDropDown (if 0 = normal list, 1 = dropdown)
    if (*(int *)((int)this + 0x58) == 1) { // +0x58: mSelectionMode (1 = wrap around)
      int currentIndex = (*(int *)((int)this + 0x54) + 1 + *(int *)((int)this + 0x60)) %
                         *(int *)((int)this + 0x60); // +0x54: mCurrentIndex, +0x60: mMaxIndex
      // Build key path for the new index
      buildKeyPath(keyBuffer, &DAT_00e3266c, currentIndex); // DAT_00e3266c likely base path
      disabledFlagBuffer[0] = '\0';
      // Check if this item is disabled
      readProperty("IsSelectionDisabled", disabledFlagBuffer, &DAT_00d90fa8, 1, keyBuffer);
      while (disabledFlagBuffer[0] == '1') {
        // Advance to next index, skipping disabled items
        currentIndex = (*(uint *)((int)this + 0x60) + 1 + currentIndex) %
                       *(uint *)((int)this + 0x60);
        buildKeyPath(keyBuffer, &DAT_00e3266c, currentIndex);
        disabledFlagBuffer[0] = '\0';
        readProperty("IsSelectionDisabled", disabledFlagBuffer, &DAT_00d90fa8, 1, keyBuffer);
      }
      setSelection(currentIndex); // +0x54 update? or external call
      goto playSound;
    }
    // Non-wrapping mode: just send "MoveDown" command
    sendCommand("MoveDown", 0, &DAT_00d90fa8, 0);
  }
  else {
    // Dropdown mode
    sendCommand("MoveDropDown", 0, &DAT_00d90fa8, 0);
  }

playSound:
  // Play selection move sound (likely a UI click)
  dummy = DAT_011302b0;
  soundBuffer = 0;
  playUISound(&dummy, 0);
  return;
}