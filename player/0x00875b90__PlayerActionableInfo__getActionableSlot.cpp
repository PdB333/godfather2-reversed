// FUNC_NAME: PlayerActionableInfo::getActionableSlot
int __thiscall PlayerActionableInfo::getActionableSlot(int thisPtr, uint *actionableIndex)
{
  uint index = *actionableIndex;
  
  // Actionable slots 6-9 (indices 0-3) at offset 0xbc0 + slot*0x30
  if ((5 < index) && (index < 10)) {
    return (index - 6) * 0x30 + 0xbc0 + thisPtr;
  }
  
  // Actionable slots 10-13 (indices 4-7) at same offset pattern
  if ((9 < index) && (index < 0xe)) {
    return (index - 10) * 0x30 + 0xbc0 + thisPtr;
  }
  
  // Default: slot 0 at offset 0xbc0
  return thisPtr + 0xbc0;
}