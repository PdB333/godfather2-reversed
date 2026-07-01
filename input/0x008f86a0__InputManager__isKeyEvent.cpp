// FUNC_NAME: InputManager::isKeyEvent
bool __thiscall isKeyEvent(int eventType, undefined4 param_2, undefined4 param_3, undefined4 param_4) {
  // Compare event type against "key event" identifier (0x48FC0841 = B743F9BF little-endian)
  // This appears to be a type-check for input events
  if (eventType == -0x48fc0841) {
    // Call a function pointer stored in global data at DAT_0112af68
    // The function pointer at offset +4 likely handles key event processing
    (**(code **)(*DAT_0112af68 + 4))(param_4);
  }
  return eventType == -0x48fc0841;
}