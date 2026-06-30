// FUNC_NAME: InputManager::setControllerVibration
undefined1 InputManager::setControllerVibration(uint controllerIndex, undefined4 vibrationValue)

{
  int controllerSlot;
  undefined1 result;
  
  result = 0;
  if ((controllerIndex & 0xffff) < 0x200) {
    controllerSlot = (controllerIndex & 0xffff) * 0x30 + 0x10 + DAT_012234bc;
    if ((((controllerSlot != 0) && (*(uint *)(controllerSlot + 0x2c) == controllerIndex)) && (controllerSlot != 0)) &&
       (*(int *)(controllerSlot + 0x10) != 0)) {
      *(undefined4 *)(*(int *)(controllerSlot + 0x10) + 0x5c) = vibrationValue;
      result = 1;
    }
  }
  return result;
}