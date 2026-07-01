// FUNC_NAME: SomeClass::findSlotByParam
int __thiscall SomeClass::findSlotByParam(int thisPtr, int param2)
{
  int slotIndex;
  
  slotIndex = FUN_0090b0a0(param2); // likely a hash lookup or ID-to-index conversion
  if (slotIndex != -1) {
    // Return pointer to slot data at offset 0x18 + slotIndex * 0x24 (36 bytes per slot)
    return thisPtr + 0x18 + slotIndex * 0x24;
  }
  return 0; // null if not found
}