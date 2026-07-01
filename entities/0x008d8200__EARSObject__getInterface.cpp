// FUNC_NAME: EARSObject::getInterface
bool __thiscall EARSObject::getInterface(int thisPtr, int interfaceId, int *outInterface)
{
  if (interfaceId == 0x84ecd042) { // IID_SimObject
    *outInterface = thisPtr;
    return true;
  }
  *outInterface = 0;
  if (interfaceId == 0x38523fc3) { // IID_NetObject
    *outInterface = thisPtr;
  }
  return *outInterface != 0;
}