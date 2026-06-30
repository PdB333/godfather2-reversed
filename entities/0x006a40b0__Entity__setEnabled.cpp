// FUNC_NAME: Entity::setEnabled
// Function address: 0x006a40b0
// Sets the enabled flag (+0x51). If the flag transitions from disabled to enabled,
// also sets the update flag (+0x50) to 1 to trigger a state refresh.

void __thiscall Entity::setEnabled(int thisPtr, char enabled)
{
  char oldEnabled = *(char *)(thisPtr + 0x51);  // +0x51: enabled flag
  *(char *)(thisPtr + 0x51) = enabled;
  if ((oldEnabled == '\0') && (enabled != '\0')) {
    *(char *)(thisPtr + 0x50) = 1;  // +0x50: update pending flag
  }
}