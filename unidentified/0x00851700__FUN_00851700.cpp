// FUNC_NAME: SomeClass::handleQueryInterface
undefined4 __thiscall handleQueryInterface(undefined4 this, int interfaceId, undefined4 *outInterface)
{
  // +0x0: this pointer (object instance)
  // interfaceId: 0x1b91f4f = some known interface ID
  // interfaceId: -0x2d1a4f = 0xFFD2E5B1 = another known interface ID
  
  if (interfaceId == 0x1b91f4f) {
    if (outInterface != (undefined4 *)0x0) {
      *outInterface = this;
      return 1; // success
    }
  }
  else {
    if (outInterface != (undefined4 *)0x0) {
      *outInterface = 0; // clear output
    }
    if (interfaceId != -0x2d1a4f) {
      return 0; // unknown interface
    }
    if (outInterface != (undefined4 *)0x0) {
      *outInterface = this;
    }
  }
  return 1; // success for known interfaces
}