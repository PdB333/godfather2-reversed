// FUNC_NAME: NPCAnimationComponent::updateLookAtTarget
void NPCAnimationComponent::updateLookAtTarget(void)

{
  int npcPtr;
  undefined4 lookAtTarget;
  undefined4 lookAtTarget2;
  undefined4 lookAtTarget3;
  
  FUN_00414aa0();  // Likely plays a sound or triggers animation event
  lookAtTarget3 = 0;
  lookAtTarget2 = 0;
  lookAtTarget = 0;
  // Check if look-at target is enabled (bit 6 of flags at +0xb4)
  if ((*(uint *)(npcPtr + 0xb4) >> 6 & 1) == 0) {
    lookAtTarget3 = *(undefined4 *)(npcPtr + 0xf8);  // +0xf8: lookAt target X or entity reference
  }
  // Check if look-at target override is enabled (bit 5 of same flags)
  if ((*(uint *)(npcPtr + 0xb4) >> 5 & 1) == 0) {
    lookAtTarget2 = *(undefined4 *)(npcPtr + 0x104); // +0x104: target Y or Z
    lookAtTarget = *(undefined4 *)(npcPtr + 0x110);  // +0x110: target Z or time
  }
  FUN_0056b8a0(lookAtTarget3, lookAtTarget2, lookAtTarget); // Set look-at target position/entity
  return;
}