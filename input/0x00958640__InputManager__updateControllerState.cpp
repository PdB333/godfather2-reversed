// FUNC_NAME: InputManager::updateControllerState
undefined4 __fastcall InputManager::updateControllerState(void* thisPtr)
{
  float leftX, leftY, rightX, rightY;
  byte controllerIndex;
  int stickMode;
  
  // Clear first trigger state if active
  if (*(char*)((int)thisPtr + 0x2c0) != '\0') {
    FUN_009bd900(); // Trigger cleanup function
    *(char*)((int)thisPtr + 0x2c0) = 0;
  }
  
  // Clear second trigger state if active
  if (*(char*)((int)thisPtr + 0x2c1) != '\0') {
    FUN_009bd940(); // Trigger cleanup function
    *(char*)((int)thisPtr + 0x2c1) = 0;
  }
  
  controllerIndex = *(byte*)(DAT_01129814 + 0x14); // Active controller index
  // Check if controller is valid (index < 16) and not in a special mode
  if ((controllerIndex < 0x10) && (*(int*)(DAT_01129814 + 0x10) != 3)) {
    stickMode = *(int*)((int)thisPtr + 0x2b4); // Current stick mode (0=analog, 1=left stick, 2=right stick)
    
    if (stickMode == 0) {
      // Analog stick mode - read from digital/analog input
      FUN_00465e30(controllerIndex, 0, (float*)((int)thisPtr + 0x50), (float*)((int)thisPtr + 0x54), 1, 0,
                   DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8); // Read left stick X/Y
      FUN_00465e30(controllerIndex, 1, (float*)((int)thisPtr + 0x58), (float*)((int)thisPtr + 0x5c), 1, 0,
                   DAT_00d5ccf8, DAT_00d5ccf8, DAT_00d5ccf8); // Read right stick X/Y
      
      // Check if any stick axis is non-zero
      if ((((*(float*)((int)thisPtr + 0x50) != 0.0f) || (*(float*)((int)thisPtr + 0x54) != 0.0f)) ||
          (*(float*)((int)thisPtr + 0x58) != 0.0f)) || (*(float*)((int)thisPtr + 0x5c) != 0.0f)) {
        FUN_005a04a0("UpdateSticks", 0, &DAT_00d8c478, 0); // Log stick update event
      }
    }
    else {
      // Direct stick mode - copy values directly
      float value1 = *(float*)((int)thisPtr + 0x2b8); // Source value 1
      float value2 = *(float*)((int)thisPtr + 700); // Source value 2 at offset 0x2BC
      
      if ((value1 != 0.0f) && (value2 != 0.0f)) {
        if (stickMode == 1) {
          *(float*)((int)thisPtr + 0x50) = value1; // Left stick X
          *(float*)((int)thisPtr + 0x54) = value2; // Left stick Y
          FUN_005a04a0("UpdateLeftBox", 0, &DAT_00d8c478, 0); // Log left stick update
        }
        else if (stickMode == 2) {
          *(float*)((int)thisPtr + 0x58) = value1; // Right stick X
          *(float*)((int)thisPtr + 0x5c) = value2; // Right stick Y
          FUN_005a04a0("UpdateRightBox", 0, &DAT_00d8c478, 0); // Log right stick update
        }
      }
    }
    
    // Reset stick mode back to analog
    *(int*)((int)thisPtr + 0x2b4) = 0;
    FUN_009bd2f0(); // Post-update cleanup
  }
  
  return 0;
}