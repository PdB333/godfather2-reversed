// FUNC_NAME: GenericArray::init
void __fastcall GenericArray::init(int *this, int elementCount, int *dataBuffer, int initialValue)
{
  this[2] = dataBuffer;       // +0x08: pointer to buffer
  this[3] = initialValue;     // +0x0C: initial value (per-element)
  *this = 0xffffffff;         // +0x00: capacity (sentinel -1 means unknown/pre-allocated?)
  this[1] = elementCount;     // +0x04: current count / size

  if (0 < elementCount) {
    for (int i = 0; i < elementCount; i++) {
      *(int *)(dataBuffer + i) = 0;  // zero-initialize each element
    }
  }
}