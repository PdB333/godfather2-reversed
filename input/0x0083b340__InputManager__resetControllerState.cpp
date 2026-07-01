// FUNC_NAME: InputManager::resetControllerState
void InputManager::resetControllerState(void)
{
  // Controller state structure (0x44 bytes per slot, 16 slots)
  // +0x00: state flags
  // +0x04: button states
  // +0x08: analog values
  // +0x0C: trigger values
  // +0x10: thumbstick values
  // +0x14: vibration state
  // +0x18: connection state
  // +0x1C: device type
  // +0x20: player index
  // +0x24: battery level
  // +0x28: reserved
  // +0x2C: reserved
  // +0x30: reserved
  // +0x34: reserved
  // +0x38: reserved
  // +0x3C: reserved
  // +0x40: reserved
  
  // Initialize controller state structure on stack
  undefined4 local_c = DAT_0112dc60;  // Default controller state template
  undefined4 local_8 = 0;             // Clear additional state fields
  undefined1 local_4 = 0;            // Clear final state byte
  
  // Call reset function with pointer to state and reset flag
  FUN_00408a00(&local_c, 0);
  return;
}