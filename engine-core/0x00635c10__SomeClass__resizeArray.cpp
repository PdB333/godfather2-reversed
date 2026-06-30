// FUNC_NAME: SomeClass::resizeArray
void SomeClass::resizeArray(void)
{
  int oldCapacity; // eax
  int newCapacity; // eax
  int newData; // eax
  
  // Get current capacity (stored as number of elements * 0x18)
  oldCapacity = *(int *)(this + 0x28);
  
  // Allocate new memory: new size = requested count * 0x18
  newData = FUN_006279a0((uint)*(ushort *)(this + 0x2c) * 0x18, unaff_EDI * 0x18);
  
  // Adjust the data pointer to maintain correct offset within the new allocation
  // (old data pointer minus old capacity) / 0x18 * 0x18 = preserve relative position
  *(int *)(this + 0x14) = newData + ((*(int *)(this + 0x14) - oldCapacity) / 0x18) * 0x18;
  
  // Store new capacity (as byte offset)
  *(int *)(this + 0x28) = newData;
  
  // Store new element count
  *(short *)(this + 0x2c) = (short)unaff_EDI;
  
  // Store end pointer = newData + count * 0x18
  *(uint *)(this + 0x24) = newData + (unaff_EDI & 0xffff) * 0x18;
  
  return;
}