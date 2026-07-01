// FUNC_NAME: InputManager::shutdown
void InputManager::shutdown(void)
{
  // Free controller slot memory blocks (0x44 bytes each, 16 slots)
  // DAT_0112afa0, DAT_0112afb0, DAT_0112afa8 are likely the three input device arrays
  // (e.g., keyboard, mouse, gamepad) stored as pointers in the InputManager singleton
  FUN_00408310(&DAT_0112afa0);  // Free first device array
  FUN_00408310(&DAT_0112afb0);  // Free second device array
  FUN_00408310(&DAT_0112afa8);  // Free third device array
  return;
}