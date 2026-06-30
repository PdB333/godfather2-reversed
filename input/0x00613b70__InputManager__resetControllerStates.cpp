// FUNC_NAME: InputManager::resetControllerStates
void InputManager::resetControllerStates(void)
{
  // +0x00: controller state array (16 slots, 0x44 bytes each)
  // +0x00: slot 0 state (0 = disconnected, 1 = connected)
  // +0x04: slot 0 buttons
  // +0x08: slot 0 left stick X
  // +0x0c: slot 0 left stick Y
  // +0x10: slot 0 right stick X
  // +0x14: slot 0 right stick Y
  // +0x18: slot 0 left trigger
  // +0x1c: slot 0 right trigger
  // +0x20: slot 0 packet number
  // +0x24: slot 0 last packet number
  // +0x28: slot 0 connected flag
  // +0x2c: slot 0 battery level
  // +0x30: slot 0 vibration left motor
  // +0x34: slot 0 vibration right motor
  // +0x38: slot 0 user index
  // +0x3c: slot 0 submersion flag
  // +0x40: slot 0 reserved

  // Reset controller slot 0
  _DAT_011f69b0 = DAT_00e2b1a4;  // Set to default state (0xFFFFFFFF or similar)
  _DAT_011f69b4 = 0;             // Clear buttons
  _DAT_011f69b8 = 0;             // Clear left stick X
  uRam011f69bc = 0;              // Clear left stick Y
  _DAT_011f69c0 = 0;             // Clear right stick X
  _DAT_011f69c4 = DAT_00e2b1a4;  // Set right stick Y to default
  _DAT_011f69c8 = 0;             // Clear left trigger
  uRam011f69cc = 0;              // Clear right trigger
  _DAT_011f69d0 = 0;             // Clear packet number
  _DAT_011f69d4 = 0;             // Clear last packet number
  _DAT_011f69d8 = DAT_00e2b1a4;  // Set connected flag to default
  uRam011f69dc = 0;              // Clear battery level
  _DAT_011f69e0 = 0;             // Clear vibration left
  uRam011f69e4 = 0;              // Clear vibration right
  uRam011f69e8 = 0;              // Clear user index
  uRam011f69ec = DAT_00e2b1a4;   // Set submersion flag to default

  // Check if controller manager is initialized (bit 0 of flag)
  if ((DAT_011f7430 & 1) != 0) {
    // Call controller update function to apply changes
    FUN_00614a50();
  }
  return;
}