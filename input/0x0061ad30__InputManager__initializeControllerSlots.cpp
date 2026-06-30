// FUNC_NAME: InputManager::initializeControllerSlots
void InputManager::initializeControllerSlots(void)
{
  void *controllerBuffer;
  int iVar1;
  
  DAT_01205964 = DAT_01205868;
  controllerBuffer = (void *)FUN_009c8e50(0x404); // allocate 0x404 bytes for controller slots (16 slots * 0x44 bytes each = 0x440, but here 0x400 + 4 extra)
  if (controllerBuffer == (void *)0x0) {
    DAT_01205960 = (void *)0x0; // +0x0: controller buffer pointer
  }
  else {
    *(undefined4 *)((int)controllerBuffer + 0x400) = 0; // +0x400: slot count or flags
    _memset(controllerBuffer,0,0x400); // zero out first 0x400 bytes (16 slots * 0x40 bytes each)
    DAT_01205960 = controllerBuffer; // +0x0: store buffer pointer
  }
  iVar1 = FUN_009c8e50(0x81c); // allocate 0x81c bytes for something else (maybe input device list)
  if (iVar1 != 0) {
    DAT_01205968 = FUN_0061ac90(); // +0x8: initialize input devices
    FUN_00610c40(); // initialize XInput or controller manager
    return;
  }
  DAT_01205968 = 0; // +0x8: null if allocation failed
  FUN_00610c40(); // still try to initialize
  return;
}