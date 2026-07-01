// FUNC_NAME: EARSObject::QueryInterface
bool __thiscall EARSObject::QueryInterface(uint interfaceId, void** outPtr)
{
  // This function checks if the object supports a given interface.
  // interfaceId is a 32-bit hash (unknown constants: 0xD3D3461A and 0xFFD2E5B1).
  // If supported, *outPtr is set to this and returns true; otherwise sets *outPtr to NULL and returns false.
  if (interfaceId == 0xD3D3461A) {
    if (outPtr != NULL) {
      *outPtr = this;
    }
    return true;
  }
  else {
    if (outPtr != NULL) {
      *outPtr = NULL;
    }
    if (interfaceId != 0xFFD2E5B1) {
      return false;
    }
    if (outPtr != NULL) {
      *outPtr = this;
    }
    return true;
  }
}