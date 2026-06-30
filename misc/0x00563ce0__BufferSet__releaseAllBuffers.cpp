// FUNC_NAME: BufferSet::releaseAllBuffers
void __thiscall BufferSet::releaseAllBuffers(void)
{
  int index;
  
  // Release first buffer (index at +0x64, pointer at +0x5c)
  index = *(int *)(this + 100); // +0x64
  if (index >= 0) {
    TlsGetValue(DAT_01139810); // thread-local storage handle
    releaseBuffer(*(void **)(this + 0x5c), index * 4, 0x17); // FUN_00aa26e0
  }
  
  // Release second buffer (index at +0x58, pointer at +0x50)
  index = *(int *)(this + 0x58);
  if (index >= 0) {
    TlsGetValue(DAT_01139810);
    releaseBuffer(*(void **)(this + 0x50), index * 4, 0x17);
  }
  
  // Release third buffer (index at +0x4c, pointer at +0x44)
  index = *(int *)(this + 0x4c);
  if (index >= 0) {
    TlsGetValue(DAT_01139810);
    releaseBuffer(*(void **)(this + 0x44), index * 4, 0x17);
  }
  
  resetState(); // FUN_009fd9b0
}