// FUNC_NAME: Player::requestCrewMember
void __thiscall Player::requestCrewMember(int thisPtr, char *outFlag, int crewSlotIndex)
{
  char cVar1;
  undefined8 local_c;
  undefined4 local_4;
  
  if (*outFlag != '\0') {
    // If the flag is already set, call some function (likely logging or callback)
    FUN_0079fb90(crewSlotIndex, 1, 0, local_c, local_4);
    return;
  }
  cVar1 = FUN_00481640(); // Probably checks if player is in a state that allows crew requests
  if ((cVar1 != '\0') && 
      (*(char *)(*(int *)(thisPtr + 0x58) + 0x2198 + crewSlotIndex * 0x1c) == '\0')) {
    // Mark the crew slot as requested (offset 0x2198 is likely a crew request flags array)
    // Each slot is 0x1c bytes
    *(char *)(*(int *)(thisPtr + 0x58) + 0x2198 + crewSlotIndex * 0x1c) = 1;
    *outFlag = '\x01'; // Set the output flag to indicate success
  }
  return;
}