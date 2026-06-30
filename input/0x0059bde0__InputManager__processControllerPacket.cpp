// FUNC_NAME: InputManager::processControllerPacket
void __thiscall InputManager::processControllerPacket(uint *thisPtr, undefined4 param_2)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  undefined1 auStack_64 [4];
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  
  // Check if the controller is not connected (bit 0 of flags)
  if ((*thisPtr & 1) == 0) {
    // Controller is disconnected - read from the default input state
    bVar3 = InputManager::readDefaultInput(&local_60);
    // Call the virtual function at vtable+100 (likely processInput)
    (**(code **)(*DAT_012055a8 + 100))(&local_60,param_2);
  }
  else {
    // Controller is connected - read from three separate input sources
    bVar1 = InputManager::readInputSource(); // +0x14 offset
    bVar2 = InputManager::readInputSource(); // +0x18 offset
    bVar3 = InputManager::readInputSource(); // +0x1c offset
    // Combine the three input sources with AND logic
    bVar3 = bVar1 & bVar2 & bVar3;
    // Call virtual function at vtable+0x54 (likely processInputCombined)
    (**(code **)(*DAT_012055a8 + 0x54))(local_5c,local_60,local_58,param_2);
  }
  // Check if there's a rumble motor state and it's active (bit 2 of rumble flags)
  if (((byte *)thisPtr[1] != (byte *)0x0) && ((*(byte *)thisPtr[1] & 4) != 0)) {
    // Process rumble/force feedback
    (**(code **)(*DAT_012055a8 + 0x40))(&local_60); // readRumbleState
    (**(code **)(*DAT_012055a8 + 0x50))(param_2,thisPtr[1] + 0x10,auStack_64); // setRumbleTarget
    (**(code **)(*DAT_012055a8 + 0x5c))(&stack0xffffff90,param_2); // applyRumble
  }
  // If input was activated, set bit 2 in flags (button pressed flag)
  if (bVar3 != 0) {
    *thisPtr = *thisPtr | 4;
  }
  return;
}