// FUNC_NAME: Sentient::updateAnimationState
void Sentient::updateAnimationState(void)
{
  uint flags;
  uint animFlags;
  
  flags = *(uint *)(this + 0xc); // +0x0C: animationFlags / stateFlags
  animFlags = flags & 0x700000; // Extract animation type bits (bits 20-22)
  
  if ((flags & 0x30000) == 0x10000) { // Bit 16 set, bit 17 clear -> specific anim state
    *(byte *)(this + 0x21) = 1; // +0x21: animationSubState
    *(byte *)(this + 0x22) = 1; // +0x22: animationLayer
    *(byte *)(this + 0x20) = 1; // +0x20: animationState
  }
  else {
    *(byte *)(this + 0x22) = 2; // Default layer 2
    *(byte *)(this + 0x20) = 2; // Default state 2
    if ((flags & 0x30000) == 0x20000) { // Bit 17 set, bit 16 clear
      *(byte *)(this + 0x21) = 3; // +0x21: animationSubState = 3
      *(byte *)(this + 0x23) = 4; // +0x23: animationPriority = 4
      goto checkFlags;
    }
    *(byte *)(this + 0x21) = 2; // Default subState 2
  }
  *(byte *)(this + 0x23) = 1; // +0x23: animationPriority = 1
  
checkFlags:
  if ((flags & 1) == 0) { // Bit 0 clear -> no animation flag
    *(byte *)(this + 0x20) = 0; // Reset animation state
  }
  
  if (animFlags == 0x200000) { // Animation type 2 (bits 21 set)
    *(byte *)(this + 0x24) = 3; // +0x24: animationType = 3
  }
  else {
    if (animFlags == 0x100000) { // Animation type 1 (bits 20 set)
      *(byte *)(this + 0x24) = 2; // animationType = 2
      *(int *)(this + 0x28) = 0; // +0x28: animationParam = 0
      return;
    }
    if ((animFlags == 0x300000) || (animFlags == 0x400000)) { // Animation types 3 or 4
      *(byte *)(this + 0x24) = 4; // animationType = 4
    }
    else {
      *(byte *)(this + 0x24) = 1; // Default animationType = 1
    }
    if (animFlags == 0x400000) { // Animation type 4
      *(int *)(this + 0x28) = -1; // animationParam = -1 (infinite?)
      return;
    }
  }
  *(int *)(this + 0x28) = 0; // Reset animation param
  return;
}