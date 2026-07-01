// FUNC_NAME: InputManager::setControllerFlags
void InputManager::setControllerFlags(ushort flags)
{
  char cVar1;
  undefined4 uVar2;
  int local_10 [3];
  code *local_4;
  
  if (DAT_0113056c != 0) {
    *(ushort *)(DAT_0113056c + 6) = *(ushort *)(DAT_0113056c + 6) | flags; // +0x6: controllerFlags
  }
  local_10[0] = 0;
  local_10[2] = 0;
  local_10[1] = 0;
  uVar2 = FUN_00699280(local_10); // getCurrentController
  cVar1 = FUN_009341d0(uVar2); // isControllerActive
  if (cVar1 != '\0') {
    uVar2 = FUN_006987c0(local_10); // getControllerDevice
    FUN_009341d0(uVar2); // setControllerRumble
  }
  if (local_10[0] != 0) {
    (*local_4)(local_10[0]); // release controller
  }
  return;
}