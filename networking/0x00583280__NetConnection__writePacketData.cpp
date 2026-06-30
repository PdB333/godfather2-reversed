// FUNC_NAME: NetConnection::writePacketData
void __thiscall NetConnection::writePacketData(int this, undefined4 param_2, undefined4 param_3, uint flags)
{
  // +0x00: byte state flag (set to 2 when copying)
  // +0x04: pointer to data buffer (source/destination)
  if ((flags & 0x100) == 0) {
    // Alternate path: likely a different serialization method
    FUN_00584860(this, param_3);
    return;
  }
  // Copy 32 bytes (8 dwords) from source buffer to destination buffer
  uint* src = *(uint**)(this + 4);
  uint* dst = (uint*)*(int*)(this + 4); // Same pointer as src? Possibly a self-copy or misread
  *(byte*)this = 2; // Mark state as "copying"
  dst[0] = src[0];
  dst[1] = src[1];
  dst[2] = src[2];
  dst[3] = src[3];
  dst[4] = src[4];
  dst[5] = src[5];
  dst[6] = src[6];
  dst[7] = src[7];
}