// FUNC_NAME: GambleManager::updateWager
void GambleManager::updateWager(void)
{
  undefined4 wagerAmount;
  int thisPtr; // in_EAX is implicit this pointer
  int stateResult;
  longlong wagerParam;
  
  // Check if the bit at +0xa8 offset 1 (0x02 mask) is not set
  // This is likely a status flag indicating some condition
  if ((*(byte *)(thisPtr + 0xa8) & 2) == 0) {
    // Call some global/singleton function with a data reference (DAT_00e2df9c)
    stateResult = FUN_00ac2870(&DAT_00e2df9c);
    
    // If the state check returns 1 (success/ready?) and wagerParam equals 0x20000
    if ((stateResult == 1) && (wagerParam = FUN_00ac28e0(), wagerParam == 0x20000)) {
      // Store current wager amount from offset 200 (0xC8)
      wagerAmount = *(undefined4 *)(thisPtr + 200);  // +0xC8: wagerAmountTemp
      
      // Increase wager total at offset 0xC0 by 0x20000 (131072 units)
      *(int *)(thisPtr + 0xc0) = *(int *)(thisPtr + 0xc0) + 0x20000;  // +0xC0: currentWagerTotal
      
      // Reset temp wager at offset 200 to 0
      *(undefined4 *)(thisPtr + 200) = 0;  // +0xC8: wagerAmountTemp = 0
      
      // Use some global DAT_012234a8 as a reference to another object
      // Increment some resource at offset 0x88 by same amount
      iVar2 = DAT_012234a8;
      *(int *)(iVar2 + 0x88) = *(int *)(iVar2 + 0x88) + 0x20000;  // +0x88: someResource
      
      // Process the wager through another function
      FUN_004d1ba0(wagerAmount);
      
      // Check if current wager total is less than max wager at offset 0xBC
      if (*(uint *)(thisPtr + 0xc0) < *(uint *)(thisPtr + 0xbc)) {  // +0xBC: maxWagerLimit
        // Continue to next wager step
        FUN_004d1ab0();
        return;
      }
    }
    else {
      // Set the status bit 2 (0x02) to indicate wager processing complete/blocked
      *(uint *)(thisPtr + 0xa8) = *(uint *)(thisPtr + 0xa8) | 2;  // +0xA8: statusFlags
    }
  }
  
  // Finalize or cleanup wager state
  FUN_004d1a30();
  return;
}