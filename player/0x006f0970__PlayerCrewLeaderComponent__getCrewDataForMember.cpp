// FUNC_NAME: PlayerCrewLeaderComponent::getCrewDataForMember
undefined4 __thiscall PlayerCrewLeaderComponent::getCrewDataForMember(int thisPtr, int *memberPtr)
{
  undefined4 result;
  uint index;
  undefined4 *slotPtr;
  
  result = 0;
  if ((memberPtr != (int *)0x0) && (*memberPtr != 0)) {
    index = 0;
    // Array at this+0x2c: two slots of 8 bytes each; compare first 4 bytes to memberPtr
    slotPtr = (undefined4 *)(thisPtr + 0x2c);
    while ((int *)*slotPtr != memberPtr) {
      index = index + 1;
      slotPtr = slotPtr + 8; // skip 8 bytes per slot
      if (1 < index) {
        return result;
      }
    }
    // Array at this+0x34: two slots of 0x20 bytes each; get value at offset +0x20 from match
    result = *(undefined4 *)(*(int *)(index * 0x20 + 0x34 + thisPtr) + 0x20);
  }
  return result;
}