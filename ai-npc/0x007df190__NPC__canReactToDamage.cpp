// FUNC_NAME: NPC::canReactToDamage
unsigned char __fastcall NPC::canReactToDamage(int thisPtr)
{
  char bCanReact;
  
  bCanReact = FUN_004ac2c0(0);  // Likely: isDead() or isUnconscious()
  if (bCanReact == '\0') {
    bCanReact = FUN_004ac870(0);  // Likely: isInVehicle() or isImmobilized()
    if ((bCanReact != '\0') && (*(float *)(thisPtr + 0x30) <= _DAT_00d6f7f4)) {
      // +0x30: current health or stagger timer
      // Global DAT_00d6f7f4: minHealthThreshold or staggerTimeLimit
      return 0;
    }
  }
  return 1;
}