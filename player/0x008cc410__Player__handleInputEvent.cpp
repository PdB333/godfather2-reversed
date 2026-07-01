// FUNC_NAME: Player::handleInputEvent
void __thiscall Player::handleInputEvent(int thisPtr, int *inputEvent)
{
  // Call base class or input processing function
  FUN_004b6f20(inputEvent);
  
  // Check if this input event matches the global current event
  if (DAT_012069f4 == *inputEvent) {
    // Clear bit 3 (0x8) of flags at +0x24
    *(uint *)(thisPtr + 0x24) = *(uint *)(thisPtr + 0x24) & 0xfffffff7;
    
    // Process the global event
    FUN_004086d0(&DAT_012069f4);
    
    // Check if bit 2 (0x4) was set in flags
    if (((*(uint *)(thisPtr + 0x24) >> 2 & 1) != 0) &&
       // Clear bit 2 (0x4) of flags
       (*(uint *)(thisPtr + 0x24) = *(uint *)(thisPtr + 0x24) & 0xfffffffb,
       // Check if there's a valid target at +0x2c
       *(int *)(thisPtr + 0x2c) != 0)) {
      // Call some action function with parameters (target, 1, 0)
      FUN_009f4240(*(undefined4 *)(thisPtr + 0x28), 1, 0);
      
      // Set bit 4 (0x10) of flags
      *(uint *)(thisPtr + 0x24) = *(uint *)(thisPtr + 0x24) | 0x10;
      
      // Check if squared distance (from +0x34, +0x38, +0x3c) exceeds threshold
      if (_DAT_00d577a0 <
          *(float *)(thisPtr + 0x34) * *(float *)(thisPtr + 0x34) +
          *(float *)(thisPtr + 0x38) * *(float *)(thisPtr + 0x38) +
          *(float *)(thisPtr + 0x3c) * *(float *)(thisPtr + 0x3c)) {
        // Call some movement/position function
        FUN_005417a0(DAT_012067e8, thisPtr + 0x34);
      }
    }
  }
}