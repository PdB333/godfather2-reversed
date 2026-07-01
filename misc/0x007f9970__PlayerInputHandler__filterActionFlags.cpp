// FUNC_NAME: PlayerInputHandler::filterActionFlags
// Address: 0x007f9970
// Role: Filters input action flags based on current game state and player context.
//       Checks if input is allowed, then modifies the action bitmask accordingly.
//       Bit 6 (0x40) is cleared if a certain state flag (bit 10 at +0x888) is not set.
//       Bit 4 (0x10) is cleared if an active action controller (at +0x59c) reports the action is not allowed.
//       Then forwards the resulting flags to sub_4816c0 for further processing.
void __thiscall PlayerInputHandler::filterActionFlags(uint actionFlags)
{
  char isInputEnabled = sub_481660(); // Likely checks if input processing is globally enabled
  if (isInputEnabled != '\0') {
    // If bit 10 at offset 0x888 (some state flag) is not set, clear bit 6 (0x40)
    // Bit 6 may represent an action like "aim" or "sprint"
    if ((*(uint *)(this + 0x888) >> 10 & 1) == 0) {
      actionFlags = actionFlags & 0xffffffbf; // Clear bit 6
    }
    // If bit 4 (0x10) is set and there is a valid action controller (+0x59c)
    if (((actionFlags & 0x10) != 0) && (*(int *)(this + 0x59c) != 0)) {
      // Call virtual function at offset 0x38 on the controller; returns nonzero if action is allowed
      char isActionAllowed = (**(code **)(**(int **)(this + 0x59c) + 0x38))();
      if (isActionAllowed != '\0') {
        actionFlags = actionFlags & 0xffffffef; // Clear bit 4 (0x10)
      }
    }
    if (actionFlags != 0) {
      sub_4816c0(actionFlags); // Forward filtered flags to further processing
    }
  }
}