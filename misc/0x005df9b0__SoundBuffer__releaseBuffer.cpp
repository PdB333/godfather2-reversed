// FUNC_NAME: SoundBuffer::releaseBuffer
void SoundBuffer::releaseBuffer(void)
{
  // local array used as temporary buffer for deallocation
  byte tmpBuf[12];

  // Call helper to deallocate the audio data buffer.
  // Parameters: tmpBuf output, this pointer, value of the audio data pointer,
  // this pointer again, and the audio data pointer.
  FUN_005dffe0(tmpBuf, this, *reinterpret_cast<void**>(this + 0x1c), this,
               reinterpret_cast<void**>(this + 0x1c));

  // Call virtual function at vtable index 1 (offset 4) to release the data.
  // This usually corresponds to a delete/Free() with size 24 (0x18).
  void** vtable = reinterpret_cast<void***>(*(int**)(this + 4))[0];
  reinterpret_cast<void (*)(void*, int)>(vtable[1])(*reinterpret_cast<void**>(this + 0x1c), 0x18);

  // Reset data pointers to null.
  *(reinterpret_cast<int*>(this + 0x1c)) = 0;
  *(reinterpret_cast<int*>(this + 0x20)) = 0;
}