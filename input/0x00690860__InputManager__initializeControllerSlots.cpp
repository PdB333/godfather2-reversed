// FUNC_NAME: InputManager::initializeControllerSlots
undefined4 * __fastcall InputManager::initializeControllerSlots(undefined4 *this)
{
  int controllerData;
  int iVar1;
  uint controllerIndex;
  
  controllerIndex = 0;
  this[1] = 1; // +0x04: initialized flag
  this[2] = 0; // +0x08: some counter
  *this = &PTR_FUN_00d5c958; // vtable pointer
  
  // Initialize various global controller data buffers (0x8000 bytes each)
  if (DAT_01130470 != 0) {
    FUN_00408900(this, &DAT_01130470, 0x8000); // controller buffer 1
  }
  if (DAT_01130368 != 0) {
    FUN_00408900(this, &DAT_01130368, 0x8000); // controller buffer 2
  }
  if (DAT_01130370 != 0) {
    FUN_00408900(this, &DAT_01130370, 0x8000); // controller buffer 3
  }
  if (DAT_01130248 != 0) {
    FUN_00408900(this, &DAT_01130248, 0x8000); // controller buffer 4
  }
  if (DAT_01130378 != 0) {
    FUN_00408900(this, &DAT_01130378, 0x8000); // controller buffer 5
  }
  if (DAT_01130218 != 0) {
    FUN_00408900(this, &DAT_01130218, 0x8000); // controller buffer 6
  }
  if (DAT_011303c8 != 0) {
    FUN_00408900(this, &DAT_011303c8, 0x8000); // controller buffer 7
  }
  if (DAT_011304c8 != 0) {
    FUN_00408900(this, &DAT_011304c8, 0x8000); // controller buffer 8
  }
  if (DAT_01130360 != 0) {
    FUN_00408900(this, &DAT_01130360, 0x8000); // controller buffer 9
  }
  if (DAT_011301b0 != 0) {
    FUN_00408900(this, &DAT_011301b0, 0x8000); // controller buffer 10
  }
  if (DAT_012069fc != 0) {
    FUN_00408900(this, &DAT_012069fc, 0x8000); // controller buffer 11
  }
  if (DAT_01206a10 != 0) {
    FUN_00408900(this, &DAT_01206a10, 0x8000); // controller buffer 12
  }
  
  iVar1 = DAT_012233b4; // global controller state pointer
  *(undefined1 *)(DAT_012233b4 + 0x52c) = 1; // +0x52c: some flag
  
  // Iterate through 16 controller slots
  do {
    controllerData = FUN_00410540(controllerIndex); // get controller data by index
    if (((*(char *)(controllerData + 0x3e) != '\0') && ((byte)controllerIndex < 0x10)) &&
       ((byte)controllerIndex != *(byte *)(iVar1 + 0x53d))) {
      *(undefined1 *)((controllerIndex & 0xff) + 0x52d + iVar1) = 1; // mark slot as active
    }
    controllerIndex = controllerIndex + 1;
  } while (controllerIndex != 0x10);
  
  return this;
}