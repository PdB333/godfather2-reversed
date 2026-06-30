// FUNC_NAME: InputManager::mapButtonIndexToValue
int InputManager::mapButtonIndexToValue(short buttonIndex)
{
  // If buttonIndex is non-zero, return buttonIndex - 1 (likely remapping to zero-based)
  if (buttonIndex != 0) {
    return buttonIndex - 1;
  }
  // Otherwise, return a value from an internal mapping table
  // offset +0x24: pointer to a mapping table structure
  // mapping table +0x26: short value representing the mapped output
  return *(short *)(*(int *)(this + 0x24) + 0x26);
}