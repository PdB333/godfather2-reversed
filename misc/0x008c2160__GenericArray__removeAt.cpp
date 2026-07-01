// FUNC_NAME: GenericArray::removeAt
void __thiscall GenericArray::removeAt(int *this, int index)
{
  int count;
  int lastIndex;
  int lastElementPtr;
  
  count = this[1]; // +0x04: element count
  if (index != count - 1) {
    // Move last element into the removed slot
    lastIndex = count - 1;
    lastElementPtr = *this + -0x1c + lastIndex * 0x1c; // +0x00: data pointer, each element is 0x1c bytes
    *(undefined4 *)(*this + index * 0x1c) = *(undefined4 *)lastElementPtr;
    *(undefined4 *)(*this + index * 0x1c + 4) = *(undefined4 *)(lastElementPtr + 4);
    *(undefined4 *)(*this + index * 0x1c + 8) = *(undefined4 *)(lastElementPtr + 8);
    FUN_00792320(lastElementPtr + 0x10); // Destructor call for element at offset +0x10
    *(undefined1 *)(*this + index * 0x1c + 0xc) = *(undefined1 *)(lastElementPtr + 0xc); // Copy byte at +0x0c
  }
  this[1] = count - 1; // Decrement count
  
  // Clean up the last element's pointer (if any)
  int lastElemPtr = *(int *)(*this + 0x10 + this[1] * 0x1c); // +0x10 offset within element
  if (lastElemPtr != 0) {
    FUN_009c8f10(lastElemPtr); // Free memory
  }
}