// FUNC_NAME: ResourceManager::pushResource

void ResourceManager::pushResource(void)
{
  int dx, dy, dz; // unused?
  int newCapacity;
  int *newBuffer;
  int size;
  int *inlineBuffer = (int *)(this + 0x2174);
  int *poolHead = (int *)(this + 0x174); // +0x174

  if (*(int *)(this + 0x21f8) != 0) {
    // Allocate another resource
    int x1 = *(int *)(this + 0x44);
    int x2 = *(int *)(this + 0x40);
    int y1 = *(int *)(this + 0x38);
    int y2 = *(int *)(this + 0x3c);
    *(int *)(this + 0x21fc) += 1; // increment count
    int count = *(int *)(this + 0x21fc);
    int capacity = *(int *)(this + 0x21f8);
    if (capacity <= count) {
      newCapacity = count * 2;
      *(int *)(this + 0x21f8) = newCapacity;
      if (*(int **)(this + 0x21f4) == inlineBuffer) {
        // Still using inline buffer, allocate new bigger buffer
        newBuffer = (int *)allocateMemory();
        *(int **)(this + 0x21f4) = newBuffer;
        // Copy the 32 inline entries (128 bytes) to new buffer
        int *src = (int *)(this + 0x2178);
        int *dst = newBuffer;
        for (int i = 0; i < 8; i++) {
          *dst = src[-1];
          dst[1] = src[0];
          dst[2] = src[1];
          dst[3] = src[2];
          dst += 4;
          src += 4;
        }
      } else {
        // Already using dynamic buffer, reallocate
        int *oldBuffer = *(int **)(this + 0x21f4);
        newBuffer = (int *)reallocateMemory(oldBuffer, newCapacity * 4);
        *(int **)(this + 0x21f4) = newBuffer;
      }
    }
    // Allocate a new resource block (size computed from bounding box dimensions)
    int newBlock = allocateMemory();
    *(int *)(*(int *)(this + 0x21f4) + count * 4) = newBlock;
    *(int *)(this + 0x16c) = newBlock;
    // Compute end pointer: newBlock + ( (( (x1 - x2) - y1 + y2 ) >> 6) + 256 ) * 8
    int delta = ( ( (x1 - x2) - y1 + y2 ) >> 6 ) + 0x100;
    *(int *)(this + 0x170) = newBlock + delta * 8;
    return;
  }

  // First time initialization
  *(int **)(this + 0x21f4) = inlineBuffer;
  *(int *)(this + 0x21f8) = 0x20; // capacity 32
  *(int *)(this + 0x21fc) = 0;    // count 0
  inlineBuffer[0] = (int)(this + 0x174); // inline buffer first entry points to home?
  *(int *)(this + 0x16c) = (int)(this + 0x174);
  *(int *)(this + 0x170) = (int)(this + 0x2174);
  return;
}