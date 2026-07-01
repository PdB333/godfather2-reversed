// FUNC_NAME: NPCComponent::updateAiState
void __fastcall NPCComponent::updateAiState(int thisPtr)
{
  *(byte *)(thisPtr + 0xc) = *(byte *)(thisPtr + 0xc) | 1;  // +0xc: flags byte, bit 0 = active
  FUN_004b6140();  // likely physicsTimestep or similar
  FUN_008cc2e0();  // updateDecisionMaking
  FUN_004a61b0(thisPtr + -0x50);  // updatePosition at offset -0x50 (likely parent entity)
  if ((*(byte *)(thisPtr + 0xc) & 2) != 0) {  // +0xc bit 1 = pause flag
    FUN_004b6330();  // pausePhysics
    return;
  }
  return;
}