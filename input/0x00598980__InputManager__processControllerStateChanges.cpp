// FUNC_NAME: InputManager::processControllerStateChanges
void InputManager::processControllerStateChanges(void *this)
{
  char cVar1;
  int *unaff_ESI;
  undefined4 local_10;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  // Check if controller 0 has pending state change (bit 0)
  if ((*(byte *)(unaff_ESI + 1) & 1) != 0) {
    FUN_00595490(this); // likely readControllerState
    cVar1 = FUN_00595610(); // likely isControllerConnected
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xfffffffe; // clear pending flag
    }
    (**(code **)(*unaff_ESI + 0x1c))(local_10); // vtable call: handleControllerStateChange
  }
  // Check if controller 1 has pending state change (bit 1)
  if ((*(byte *)(unaff_ESI + 1) & 2) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595950(&uStack_c); // likely isControllerConnected with extra params
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xfffffffd; // clear pending flag
    }
    (**(code **)(*unaff_ESI + 0x20))(uStack_c,uStack_8,uStack_4); // vtable call
  }
  // Check if controller 2 has pending state change (bit 2)
  if ((*(byte *)(unaff_ESI + 1) & 4) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595610();
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xfffffffb;
    }
    (**(code **)(*unaff_ESI + 0x2c))(local_10);
  }
  // Check if controller 3 has pending state change (bit 3)
  if ((*(byte *)(unaff_ESI + 1) & 8) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595950(&uStack_c);
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xfffffff7;
    }
    (**(code **)(*unaff_ESI + 0x30))(uStack_c,uStack_8,uStack_4);
  }
  // Check if controller 4 has pending state change (bit 4)
  if ((*(byte *)(unaff_ESI + 1) & 0x10) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595610();
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xffffffef;
    }
    (**(code **)(*unaff_ESI + 0x3c))(local_10);
  }
  // Check if controller 5 has pending state change (bit 5)
  if ((*(byte *)(unaff_ESI + 1) & 0x20) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595610();
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xffffffdf;
    }
    (**(code **)(*unaff_ESI + 0x40))(local_10);
  }
  // Check if controller 6 has pending state change (bit 6)
  if ((*(byte *)(unaff_ESI + 1) & 0x40) != 0) {
    FUN_00595490(this);
    cVar1 = FUN_00595950(&uStack_c);
    if (cVar1 != '\0') {
      unaff_ESI[1] = unaff_ESI[1] & 0xffffffbf;
    }
    (**(code **)(*unaff_ESI + 0x44))(uStack_c,uStack_8,uStack_4);
  }
  return;
}