// FUNC_NAME: PacketAllocator::allocatePacket
void __thiscall PacketAllocator::allocatePacket()
{
  // this+0x04: pointer to vtable/function table (first entry is a placement new/alloc function)
  // this+0x08: pointer to pre-allocated buffer, or NULL
  void *buffer = *(void **)(this + 8);
  void *ptr;

  // Use stack fallback if no pre-allocated buffer (likely just to pass a non-null pointer)
  if (buffer == NULL) {
    uint32_t stackBuffer[3] = {0, 0, 0}; // 12 bytes
    ptr = stackBuffer;
  } else {
    ptr = buffer;
  }

  // Call allocator function: returns a pointer to a 0x18-byte block (packet data)
  // The function signature: void* (__thiscall?)(int size, void* hintOrPlacement)
  ptr = (*(void *(*)(int, void *)) ( **(int **)(this + 4) ))(0x18, ptr);

  // Initialize the allocated packet structure (first 12 bytes zeroed)
  if (ptr != NULL) {
    *(uint32_t *)ptr = 0;              // +0x00: dword
    *((uint32_t *)ptr + 1) = 0;        // +0x04: dword
    *((uint32_t *)ptr + 2) = 0;        // +0x08: dword
    *((uint8_t *)ptr + 0x15) = 0;      // +0x15: byte (flag)
    *((uint8_t *)ptr + 0x14) = 1;      // +0x14: byte (used flag)
  }
}