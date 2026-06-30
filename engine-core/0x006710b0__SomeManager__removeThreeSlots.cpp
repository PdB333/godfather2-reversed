// FUNC_NAME: SomeManager::removeThreeSlots
void SomeManager::removeThreeSlots(void)
{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  // First slot removal
  iVar2 = *(int *)(DAT_0120669c + 0x1e38); // +0x1e38: slot array pointer
  if (DAT_012066a0 != 0) {
    iVar3 = DAT_012066a0 + -0x10; // Get slot header
    *(undefined4 *)(*(int *)(iVar2 + 0xc) + *(int *)(DAT_012066a0 + -8) * 4) = 0; // Clear slot entry
    piVar1 = (int *)(iVar2 + 4); // +0x4: slot count
    *piVar1 = *piVar1 + -1; // Decrement count
    (*DAT_01206694)(iVar3); // Free slot memory
  }
  
  // Second slot removal
  iVar2 = *(int *)(DAT_0120669c + 0x1e38);
  if (DAT_012066a4 != 0) {
    iVar3 = DAT_012066a4 + -0x10;
    *(undefined4 *)(*(int *)(iVar2 + 0xc) + *(int *)(DAT_012066a4 + -8) * 4) = 0;
    piVar1 = (int *)(iVar2 + 4);
    *piVar1 = *piVar1 + -1;
    (*DAT_01206694)(iVar3);
  }
  
  // Third slot removal
  iVar2 = *(int *)(DAT_0120669c + 0x1e38);
  if (DAT_012066a8 != 0) {
    iVar3 = DAT_012066a8 + -0x10;
    *(undefined4 *)(*(int *)(iVar2 + 0xc) + *(int *)(DAT_012066a8 + -8) * 4) = 0;
    piVar1 = (int *)(iVar2 + 4);
    *piVar1 = *piVar1 + -1;
    (*DAT_01206694)(iVar3);
  }
  return;
}