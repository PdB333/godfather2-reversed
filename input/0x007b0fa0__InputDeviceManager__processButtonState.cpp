// FUNC_NAME: InputDeviceManager::processButtonState

// Function address: 0x007b0fa0
// Handles button press/release events, updating flags and a pending queue.
// param2: button identifier (e.g., button index or code)
// param3: bitmask for the specific button state (press/release)
// Returns 1 if the event was processed and a previous pending event matched, else 0.

undefined4 __thiscall InputDeviceManager::processButtonState(int thisPtr, undefined4 buttonId, int buttonMask)
{
  int iVar1;
  byte pressCheck;
  byte maskByte;
  
  // Check if current time threshold (global float) is below the stored threshold for this object
  if (_DAT_00d577a0 < *(float *)(thisPtr + 0x1e4)) {
    return 0;
  }
  
  pressCheck = FUN_0079e920(buttonId);  // returns 0 if not pressed, non-zero if pressed
  iVar1 = buttonMask;
  maskByte = (byte)buttonMask;
  
  if (pressCheck == '\0') {
    // Button is not pressed -> set the corresponding flag bits
    *(byte *)(thisPtr + 0x198) = *(byte *)(thisPtr + 0x198) | maskByte;
  }
  else if ((*(byte *)(thisPtr + 0x198) & maskByte) != 0) {
    // Button was previously pressed (flag set) and now pressCheck is non-zero (still pressed?)
    if (*(int *)(thisPtr + 0x1a8) < *(int *)(thisPtr + 0x1a0)) {
      FUN_007afed0(&buttonMask);  // push the mask into a queue/buffer
    }
    // Clear the flag bits
    *(byte *)(thisPtr + 0x198) = *(byte *)(thisPtr + 0x198) & ~maskByte;
  }
  
  // Check if there is a pending event to process
  pressCheck = FUN_007afb20();  // returns non-zero if pending data available
  if (((pressCheck != '\0') && (*(int *)(thisPtr + 0x1a8) != 0)) &&
      (*(int *)(*(int *)(thisPtr + 0x19c) + *(int *)(thisPtr + 0x1a4) * 4) == iVar1)) {
    // The button identifier from the pending queue matches the current buttonMask
    FUN_007aff00(&buttonMask);  // consume/remove the pending event
    return 1;
  }
  
  return 0;
}