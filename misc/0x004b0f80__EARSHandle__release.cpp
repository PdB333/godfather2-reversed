// FUNC_NAME: EARSHandle::release
void __fastcall EARSHandle::release(EARSHandle *this)
{
  // param_1 is a pointer to an EARSHandle structure:
  // offset 0x00: handleID (int)
  // offset 0x04: unknown (int)
  // offset 0x08: resourceIndex (int)
  int resourceIndex = this->resourceIndex; // param_1[2]
  if (resourceIndex >= 0) {
    // Retrieve thread-local storage (side effect or debug hook)
    TlsGetValue(DAT_01139810);
    // Release resource: handleID, size = resourceIndex * 16, pool ID = 0x17
    FUN_00aa26e0(this->handleID, resourceIndex << 4, 0x17);
  }
}