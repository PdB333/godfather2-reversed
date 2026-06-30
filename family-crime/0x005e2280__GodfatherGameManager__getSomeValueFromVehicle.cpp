// FUNC_NAME: GodfatherGameManager::getSomeValueFromVehicle

uint GodfatherGameManager::getSomeValueFromVehicle(uint param_1)
{
  uint in_EAX;
  uint uVar1;
  
  if (*(char *)(in_EAX + 0x1744) != '\0') {  // +0x1744: some flag indicating vehicle availability
    in_EAX = FUN_005e2150();  // likely returns a vehicle object pointer
    if (in_EAX != 0) {
      uVar1 = (**(code **)(*DAT_01223510 + 0x98))(*(undefined4 *)(in_EAX + 0x1cc), param_1);  // +0x1cc: some member in vehicle object
      return uVar1;
    }
  }
  return in_EAX & 0xffffff00;
}