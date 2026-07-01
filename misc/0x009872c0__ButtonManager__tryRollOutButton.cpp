// FUNC_NAME: ButtonManager::tryRollOutButton

char __thiscall ButtonManager::tryRollOutButton(int this, byte *buttonName)
{
  byte formattedPath[64];
  char result = '\0';
  
  // Check if button processing is disabled (offset +0x50 indicates enabled flag)
  if (*(char *)(this + 0x50) != '\0') {
    return '\0'; // disabled, return false
  }
  
  // Try up to 3 button indices (0, 1, 2) – likely A, B, X or similar
  for (uint index = 0; index < 3; index++) {
    // Build the path string: "/syss/buttons/button_%d/button" with index
    FUN_00910160(formattedPath, "/syss/buttons/button_%d/button", index);
    
    // Compare the built path with the passed buttonName
    if (stringCompare(formattedPath, buttonName) == 0) {
      // Match found – build rollout path (likely "/syss/buttons/button_%d/rollout")
      FUN_00910160(formattedPath, &DAT_00e3266c, index);
      // Trigger the "RollOutButton" animation/action (0 = no player index? &DAT_00d90fa8 is some object)
      FUN_005a04a0("RollOutButton", 0, &DAT_00d90fa8, 1, formattedPath);
      result = '\x01'; // success
      if (result != '\0') {
        return result;
      }
    }
  }
  return result;
}