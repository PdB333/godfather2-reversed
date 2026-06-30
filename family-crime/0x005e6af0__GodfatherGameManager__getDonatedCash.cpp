// FUNC_NAME: GodfatherGameManager::getDonatedCash
int GodfatherGameManager::getDonatedCash(void)

{
  int *piVar1;
  int iVar2;
  undefined local_5;
  int local_4;
  
  iVar2 = DAT_01223514; // pointer to GameManager instance (global)
  local_5 = 0;
  local_4 = 0;
  piVar1 = (int *)GodfatherGameManager::getDonationArrayEntry(DAT_01223514,&local_5); // gets array entry at index 0
  if (piVar1 != (int *)0x0) {
    iVar2 = GodfatherDonationEntry::getAmount(iVar2,*piVar1); // extracts donation amount from entry
    return iVar2;
  }
  return 0;
}