// FUNC_NAME: GodfatherGameManager::areEnoughFamilyMembersDead
uint32 GodfatherGameManager::areEnoughFamilyMembersDead(void)

{
  // Threshold value from DAT_00e2af44 (likely a configurable death threshold)
  // DAT_01219200 through DAT_0121922c are family member death counts or flags
  // First checks: are any of the primary family members below the threshold?
  if (((DAT_01219220 < DAT_00e2af44) ||
      (((DAT_01219200 < DAT_00e2af44 && (DAT_01219204 < DAT_00e2af44)) &&
       (DAT_01219208 < DAT_00e2af44)))) &&
     // Then checks: secondary family member counts
     ((DAT_0121922c < DAT_00e2af44 ||
      (((DAT_01219210 < DAT_00e2af44 && (DAT_01219214 < DAT_00e2af44)) &&
       (DAT_01219218 < DAT_00e2af44)))))) {
    // Not enough deaths (all members are below threshold)
    return 0;
  }
  // Enough family members have died
  return 1;
}