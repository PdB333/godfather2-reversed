// FUNC_NAME: SomeClass::clearAnimationState

void __thiscall SomeClass::clearAnimationState(int this, undefined4 param_2)
{
  int *animationPtr;
  int animationId;
  
  // Clear bit 18 (0x40000) in flags at +0x5c (likely animation state flags)
  *(uint *)(this + 0x5c) = *(uint *)(this + 0x5c) & 0xfff9ffff;
  
  animationPtr = (int *)(this + 0xa4); // +0xa4: pointer to current animation data
  if ((*(int *)(this + 0xa4) != 0) && (*(int *)(this + 0xa4) != 0x48)) {
    animationId = *animationPtr;
    if ((animationId == 0) || (animationId == 0x48)) {
      animationId = 0;
    }
    else {
      animationId = animationId + -0xc;
    }
    // Call to stop/clear animation with given ID
    FUN_00408bf0(param_2, animationId, 0);
    if (*animationPtr != 0) {
      // Free/release animation resource
      FUN_004daf90(animationPtr);
      *animationPtr = 0;
    }
  }
  return;
}