// FUNC_NAME: PlayerSM::updateActionState
undefined4 PlayerSM::updateActionState(undefined4 *param_1, int *param_2, int *param_3)
{
  char cVar1;
  int iVar2;
  int iVar3;
  int *unaff_ESI;
  uint *unaff_EDI;
  float10 fVar4;
  
  // Check if player is dead (flag at +0x7b5*4)
  if (unaff_ESI[0x7b5] == 0x637b907) {
    return 0;
  }
  
  iVar2 = FUN_00806440(); // Get current movement state
  *param_1 = 2; // Default action: idle
  iVar3 = FUN_00800ad0(); // Check if player is in combat
  if ((iVar3 == 0) || (((uint)unaff_ESI[0x238] >> 10 & 1) == 0)) {
    iVar3 = 0;
  }
  else {
    iVar3 = 1;
  }
  *param_2 = iVar3; // Combat flag
  *unaff_EDI = 0; // Reset some flag
  *param_3 = 4; // Default animation state
  
  // Check if player is ragdolling or stunned
  if ((((uint)unaff_ESI[0x7d5] >> 0x1a & 1) == 0) && (unaff_ESI[0x9a4] == 0)) {
    // Not ragdolling or stunned
    if (((iVar2 == 0) || (iVar2 == 1)) && (*param_2 == 0)) {
      // Idle or walking, not in combat
      *param_1 = 0; // Idle action
      iVar2 = (**(code **)(*unaff_ESI + 0x22c))(); // Check if weapon drawn
      *unaff_EDI = (uint)(iVar2 != 0);
    }
    else {
      // Running or in combat
      iVar3 = FUN_0077dd80(); // Check if sprinting
      *unaff_EDI = (uint)(iVar3 != 0);
      if ((iVar2 == 2) && (*param_1 = 1, *unaff_EDI == 1)) {
        // Running and sprinting
        cVar1 = FUN_00730210(); // Check if can sprint
        if (cVar1 != '\0') {
          *unaff_EDI = 0; // Can't sprint
        }
      }
    }
  }
  else {
    // Ragdolling or stunned
    *param_1 = 0; // Idle action
    iVar2 = (**(code **)(*unaff_ESI + 0x22c))(); // Check weapon drawn
    *unaff_EDI = (uint)(iVar2 != 0);
    *param_2 = 1; // Force combat flag
  }
  
  // Check if player is aiming (bit 7 of +0x238*4)
  if (((uint)unaff_ESI[0x238] >> 7 & 1) != 0) {
    *unaff_EDI = 1; // Set weapon drawn flag
  }
  
  // Check health or damage state
  fVar4 = (float10)(**(code **)(*unaff_ESI + 0xc0))(); // Get health percentage
  if ((fVar4 <= (float10)0) || (((uint)unaff_ESI[0x7d6] >> 0x19 & 1) != 0)) {
    // Dead or dying
    *param_3 = 1; // Death animation
    return 1;
  }
  
  cVar1 = FUN_007f7c60(); // Check if climbing
  if (cVar1 != '\0') {
    *param_3 = 0; // Climbing animation
    return 1;
  }
  
  // Determine animation state based on movement speed
  if ((char)unaff_ESI[0x6e3] != '\x01') {
    *param_3 = (-(uint)(1 < (byte)((char)unaff_ESI[0x6e3] - 2U)) & 2) + 2;
    return 1;
  }
  
  *param_3 = 3; // Running animation
  return 1;
}