// FUNC_NAME: SomeClass::handleQueryInterface
undefined4 __thiscall handleQueryInterface(undefined4 this, int queryId, undefined4 *outPtr)
{
  // +0x00: this pointer (implicit)
  // param_2: query identifier (e.g., interface GUID hash)
  // param_3: output pointer for interface pointer

  if (queryId == 0x63931d0e) {
    // First known interface ID
    if (outPtr != (undefined4 *)0x0) {
      *outPtr = this;
      return 1; // S_OK
    }
  }
  else {
    // Unknown interface ID
    if (outPtr != (undefined4 *)0x0) {
      *outPtr = 0; // NULL
    }
    if (queryId != -0x2d1a4f) { // 0xD2E5B1 (another interface ID)
      return 0; // E_NOINTERFACE
    }
    // Second known interface ID
    if (outPtr != (undefined4 *)0x0) {
      *outPtr = this;
    }
  }
  return 1; // S_OK
}