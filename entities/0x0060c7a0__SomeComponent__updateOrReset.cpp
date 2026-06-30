// FUNC_NAME: SomeComponent::updateOrReset
void SomeComponent::updateOrReset(undefined4 *param_1)
{
  // Check if the byte at offset +0x28 (param_1 + 10 since int is 4 bytes) is non-zero
  // This likely indicates some condition or flag
  if (*(char *)(param_1 + 10) != '\0') {
    // Call a function (likely a reset or cleanup routine)
    FUN_0060be40();
    // Call a virtual function at offset 0x30 in the vtable (likely an update or execute method)
    (**(code **)(*(int *)*param_1 + 0x30))((int *)*param_1);
    return;
  }
  // If the condition is false, set byte at offset +0x29 to 0 (likely a different flag or state)
  *(undefined1 *)((int)param_1 + 0x29) = 0;
  return;
}