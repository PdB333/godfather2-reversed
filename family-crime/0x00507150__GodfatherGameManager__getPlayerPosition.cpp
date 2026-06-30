// FUNC_NAME: GodfatherGameManager::getPlayerPosition
int GodfatherGameManager::getPlayerPosition(float *outPosition)
{
  byte bVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = FUN_00505c90(DAT_0120550c); // Get player object from global
  fVar2 = DAT_00e2cd54; // Some offset constant
  iVar3 = *(int *)(iVar3 + 8); // +0x8: player entity pointer
  if (iVar3 == 0) {
    return iVar3;
  }
  if (*(char *)(iVar3 + 0x1e) == '\0') { // +0x1E: some flag (dead?)
    return -1;
  }
  if (DAT_0120575b != '\0') { // Some global flag
    bVar1 = *(byte *)(iVar3 + 0x1d); // +0x1D: byte offset
    *outPosition = ((float)*(byte *)(iVar3 + 0x1c) + DAT_00e2cd54) * DAT_00e445e4; // +0x1C: position component
    return 1;
  }
  *outPosition = *(float *)(iVar3 + 0x24); // +0x24: direct float position
  return 1;
}