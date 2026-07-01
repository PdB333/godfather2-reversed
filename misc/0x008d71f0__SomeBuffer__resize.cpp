// FUNC_NAME: SomeBuffer::resize
void __thiscall SomeBuffer::resize(int this, uint newSize)
{
  if (*(uint *)(this + 4) < newSize) {
    // Need to grow the buffer - allocate more memory
    FUN_008d6f40(newSize);
    *(uint *)(this + 4) = newSize;
    return;
  }
  if (newSize < *(uint *)(this + 4)) {
    // Shrinking the buffer - just update the size
    *(uint *)(this + 4) = newSize;
  }
  return;
}