// FUNC_NAME: AnimationBlendController::setActiveAnimation
void __thiscall AnimationBlendController::setActiveAnimation(int thisPtr, uint *newAnimIdxPtr)
{
  uint oldIdx;
  float fVar2;
  int slotState;
  
  oldIdx = *(uint *)(thisPtr + 0x3d0);
  if (*newAnimIdxPtr != oldIdx) {
    // Clear previous slot if valid and not active (state != 1)
    if ((oldIdx < 0x14) && (slotState = *(int *)(oldIdx * 0x30 + thisPtr + 0x34), slotState != 1)) {
      *(undefined4 *)(oldIdx * 0x30 + thisPtr + 0x20) = 0; // +0x20: blend weight or timer
    }
    oldIdx = *newAnimIdxPtr;
    *(uint *)(thisPtr + 0x3d0) = oldIdx; // update current animation index
    slotState = *(int *)(oldIdx * 0x30 + thisPtr + 0x34); // state at slot+0x34
    if (slotState == 0) {
      // Animation type 0: trigger flag 1 and increment counter
      *(uint *)(thisPtr + 0x3d4) = *(uint *)(thisPtr + 0x3d4) | 1; // +0x3d4: flags
      *(int *)(thisPtr + 0x3dc) = *(int *)(thisPtr + 0x3dc) + 1; // +0x3dc: some counter
      fVar2 = (float)*(int *)(thisPtr + 0x3dc);
      if (*(int *)(thisPtr + 0x3dc) < 0) {
        fVar2 = fVar2 + 0.5f; // rounding constant
      }
      // Generate random float and compare with counter
      uint dummy = 0;
      FUN_008934e0(0xc22b9e2a, &dummy); // maybe random seed/state
      if ((float)dummy < fVar2) {
        FUN_00894ea0(0xc22b9e2a, fVar2, 0); // adjust random or condition
      }
    }
    else if (slotState == 3) {
      *(uint *)(thisPtr + 0x3d4) = *(uint *)(thisPtr + 0x3d4) | 1; // flag bit 0
    }
    else if (slotState == 1) {
      *(uint *)(thisPtr + 0x3d4) = *(uint *)(thisPtr + 0x3d4) | 2; // flag bit 1
    }
    else if (slotState == 2) {
      *(uint *)(thisPtr + 0x3d4) = *(uint *)(thisPtr + 0x3d4) | 4; // flag bit 2
    }
    FUN_006abf80(); // notify change or update system
  }
  return;
}