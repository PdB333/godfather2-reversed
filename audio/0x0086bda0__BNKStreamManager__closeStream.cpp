// FUNC_NAME: BNKStreamManager::closeStream
void __thiscall BNKStreamManager::closeStream(int *this) {
  // +0x6C: m_pStreamState (pointer to a stream state object)
  // +0x50: m_streamType (integer, likely an enum; 0 = invalid, 0x48 = already closed)
  if (this[0x1b] != 0) {
    // Only stop if the stream type is valid and not already closed
    if (this[0x14] != 0 && this[0x14] != 0x48) {
      // Call virtual function at vtable offset 0x1c (likely stop or cleanup with arg 0)
      (**(code **)(*this + 0x1c))(0);
    }
    // Release the stream state object via its first virtual function (arg 1 = release mode)
    if ((void *)this[0x1b] != (void *)0x0) {
      (*(code *)**(void **)this[0x1b])(1);
    }
    // Clear the pointer to avoid dangling reference
    this[0x1b] = 0;
  }
}