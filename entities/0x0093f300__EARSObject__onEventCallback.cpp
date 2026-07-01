// FUNC_NAME: EARSObject::onEventCallback
void EARSObject::onEventCallback(int param_1)
{
  // Check if there's a registered callback function at offset +0x28
  if (*(code **)(param_1 + 0x28) != (code *)0x0) {
    // Call the callback with the user data stored at +0x30
    (**(code **)(param_1 + 0x28))(*(undefined4 *)(param_1 + 0x30));
  }
  return;
}