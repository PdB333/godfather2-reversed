// FUNC_NAME: StreamBuffer::StreamBuffer(int bufferSize)
// Address: 0x0064f2d0
// Constructor: initializes a stream buffer with a given size, sets vtable, internal pointer, and default max capacity (0x2000)

void __fastcall StreamBuffer::StreamBuffer(int this, int bufferSize)
{
  // Offset +0x10: store buffer size
  *(int *)(this + 0x10) = bufferSize;

  // Offset +0x0C: pointer to self + 0x4E (probably internal data region)
  *(int *)(this + 0x0C) = (int)(this + 0x4E);

  // Offset +0x04: some counter or status (init to 0)
  *(int *)(this + 0x04) = 0;

  // Offset +0x08: another counter (init to 0)
  *(int *)(this + 0x08) = 0;

  // Offset +0x14: byte flag (init to 0)
  *(char *)(this + 0x14) = 0;

  // Offset +0x2C: total allocation (bufferSize * 8) – possibly per-frame or element size
  *(int *)(this + 0x2C) = bufferSize * 8;

  // Offset +0x30: maximum capacity / max packet size (0x2000 = 8192)
  *(int *)(this + 0x30) = 0x2000;

  // Offset +0x18: unknown (init to 0)
  *(int *)(this + 0x18) = 0;

  // Offset +0x1C: byte flag (init to 0)
  *(char *)(this + 0x1C) = 0;

  // Offset +0x1D: byte flag (init to 0)
  *(char *)(this + 0x1D) = 0;

  // Offset +0x38: byte flag (init to 0)
  *(char *)(this + 0x38) = 0;

  // Offset +0x34: unknown (init to 0)
  *(int *)(this + 0x34) = 0;

  // Offset +0x00: vtable pointer (EARS engine base)
  *(int *)this = (int)&PTR_LAB_00e42f38;
}