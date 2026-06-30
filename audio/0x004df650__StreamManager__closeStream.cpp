// FUNC_NAME: StreamManager::closeStream
void __fastcall StreamManager::closeStream(int *streamPtr)
{
  int streamObj;
  
  streamObj = *streamPtr;
  if (streamObj != 0) {
    // Clear bits: bit0 (active) and bit1 (eof?) from flags at +0x0C
    *(uint *)(streamObj + 0xc) = *(uint *)(streamObj + 0xc) & 0x7ffffffe;
    // If "closing" bit (0x20000) is not set, set it and call cleanup
    if ((*(uint *)(streamObj + 0xc) & 0x20000) == 0) {
      *(uint *)(streamObj + 0xc) = *(uint *)(streamObj + 0xc) | 0x20000;
      FUN_0051b120(); // likely stream cleanup/deletion
    }
    // Clear "write pending" bit (0x40000) at +0x0C
    *(uint *)(streamObj + 0xc) = *(uint *)(streamObj + 0xc) & 0xfffbffff;
    // If there's a callback pointer at +0x08, null it out
    if (*(void **)(streamObj + 8) != (void *)0x0) {
      **(void ***)(streamObj + 8) = 0;  // null the callback's target
      *(void **)(streamObj + 8) = 0;    // null the callback pointer
    }
  }
  return;
}