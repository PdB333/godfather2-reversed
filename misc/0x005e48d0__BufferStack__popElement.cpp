// FUNC_NAME: BufferStack::popElement
uint __fastcall BufferStack::popElement(int this) {
  int count;
  uint originalEax;
  uint result;
  uint32_t* bufferPtr;

  result = originalEax & 0xffffff00;
  count = *(int*)(this + 0x6030);
  if (count != 0) {
    // If more than one element exists, copy the last pair to the front
    if (count != 1) {
      bufferPtr = *(uint32_t**)(this + 0x602c);  // Base of the pair buffer (each pair = 2 uint32)
      // Overwrite the first pair with the last pair
      bufferPtr[0] = bufferPtr[count * 2 - 2];   // First element of last pair
      bufferPtr[1] = bufferPtr[count * 2 - 1];   // Second element of last pair
    }
    // Decrement the count
    *(int*)(this + 0x6030) = count - 1;
    // Return a compressed handle: high byte = 1, low 24 bits = (bufferPtr >> 8)
    bufferPtr = *(uint32_t**)(this + 0x602c);
    result = (reinterpret_cast<uintptr_t>(bufferPtr) >> 8) | 0x01000000;
  }
  return result;
}