// FUNC_NAME: Unknown::isSlotIndexOrCheck4Mapped
bool __thiscall isSlotIndexOrCheck4Mapped(int thisPtr, undefined4 param_2, int param_3)
{
  // Checks if param_3 is either 4 or matches the slot index stored at +0x50
  // Likely a validation if a given index (param_3) is valid for this object
  // +0x50 appears to be a slot index field (e.g., controller slot, network slot, etc.)
  
  if (param_3 == 4) {
    return true;
  }
  return param_3 == *(int *)(thisPtr + 0x50);
}