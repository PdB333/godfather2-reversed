// FUNC_NAME: AudioManager::releaseStreamHandle
void __fastcall AudioManager::releaseStreamHandle(undefined4 *this)
{
  int streamIndex;
  
  streamIndex = this[2]; // +0x08: stream index
  if (-1 < streamIndex) {
    TlsGetValue(DAT_01139810); // Get thread-local storage for audio system
    FUN_00aa26e0(this[0], streamIndex << 4, 0x17); // Release stream buffer at offset streamIndex*16, size 0x17
  }
  return;
}