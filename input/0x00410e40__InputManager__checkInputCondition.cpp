// FUNC_NAME: InputManager::checkInputCondition
uint __thiscall InputManager::checkInputCondition(bool param_2, uint param_3)
{
  char cVar1;
  uint in_EAX;
  int iVar2;
  
  if (*(char *)(this + 0x52c) != '\0') { // +0x52c: m_bInputEnabled
    in_EAX = getGameTickCount(); // FUN_00b92e50 - some global time function
    if (param_2 == 0) {
      cVar1 = *(char *)(this + 0x566); // +0x566: m_byteState1
    }
    else {
      if (param_2 != 1) goto LAB_00410ea0;
      cVar1 = *(char *)(this + 0x567); // +0x567: m_byteState2
    }
    if (cVar1 != 0x12) { // 0x12 likely means "not assigned" or "none"
      iVar2 = getMappingForByte(cVar1); // FUN_00b94a20 - returns a pointer to some mapping
      if (iVar2 == 0) {
        in_EAX = 4;
      }
      else {
        in_EAX = *(uint *)(iVar2 + 4); // +4: mapped value
      }
      if (in_EAX == param_3) {
        return (in_EAX & 0xffffff00) | 1; // success: return mapped value with low byte set to 1
      }
    }
  }
LAB_00410ea0:
  return in_EAX & 0xffffff00; // failure: return only the high 24 bits, low byte zero
}