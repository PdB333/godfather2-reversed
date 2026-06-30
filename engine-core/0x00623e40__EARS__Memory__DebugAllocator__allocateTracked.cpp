// FUNC_NAME: EARS::Memory::DebugAllocator::allocateTracked
void __thiscall DebugAllocator::allocateTracked(uint param_2)
{
  uint32_t *buffer;
  uint32_t stackBuffer[3]; // fallback if member buffer is null

  buffer = (uint32_t *)this->fallbackBuffer; // offset +8
  if (buffer == (uint32_t *)0x0) {
    stackBuffer[0] = 0;
    stackBuffer[1] = 0;
    stackBuffer[2] = 0;
    buffer = stackBuffer;
  }
  // Call first virtual function (likely an allocation routine) with fixed size 24 and optional buffer
  buffer = (uint32_t *)this->vtable[0](0x18, buffer); // offset +4 yields vtable
  if (buffer != (uint32_t *)0x0) {
    // Store metadata in allocated block (24-byte allocation)
    buffer[0] = stackBuffer[2];               // +0x00: first metadata word
    buffer[1] = (uint32_t)_ReturnAddress();   // +0x04: return address of caller
    buffer[2] = param_2;                      // +0x08: second parameter
    buffer[3] = *unaff_ESI;                   // +0x0C: ESI[0]
    buffer[4] = unaff_ESI[1];                 // +0x10: ESI[1]
    // Null-terminate two char arrays embedded at end of block
    *(char *)(buffer + 5) = 0;                // +0x14
    *(char *)((int)buffer + 0x15) = 0;        // +0x15
  }
  return;
}