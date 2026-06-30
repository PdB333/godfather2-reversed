// FUNC_NAME: CircularBuffer::popFront
void __fastcall CircularBuffer::popFront(int this)
{
  undefined4 value;
  int newIndex;

  // Read value from circular buffer at current read index
  // Buffer pointer at +0x48, read index at +0x50
  value = *(undefined4 *)(*(int *)(this + 0x48) + *(int *)(this + 0x50) * 4);
  
  // Advance read index with wrap-around
  newIndex = *(int *)(this + 0x50) + 1;
  *(int *)(this + 0x50) = newIndex;
  
  // Wrap if past capacity (capacity at +0x4c)
  if (*(int *)(this + 0x4c) <= newIndex) {
    *(undefined4 *)(this + 0x50) = 0;
  }
  
  // Decrement element count (count at +0x54)
  *(int *)(this + 0x54) = *(int *)(this + 0x54) + -1;
  
  // Release the popped value (likely reference counting or cleanup)
  FUN_00603210(value);
  FUN_005e3c00(value);
  
  return;
}