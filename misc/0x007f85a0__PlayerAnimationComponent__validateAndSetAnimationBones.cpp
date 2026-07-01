// FUNC_NAME: PlayerAnimationComponent::validateAndSetAnimationBones
void __fastcall PlayerAnimationComponent::validateAndSetAnimationBones(int *this)
{
  char isValid;
  uint boneIndex;
  int *boneData;
  
  boneData = this + 0x793; // +0x1E4C: bone validation array start
  boneIndex = 0;
  do {
    // Call virtual function at vtable+0x94 to validate bone name string
    isValid = (**(code **)(*this + 0x94))
                      (boneData, *(undefined4 *)((int)&PTR_s_r_wrist_00e5377c + boneIndex));
    if (isValid == '\0') {
      return; // Bone validation failed, abort
    }
    boneIndex = boneIndex + 4;
    boneData = boneData + 1;
  } while (boneIndex < 0x14); // 5 bones (0x14/4 = 5)
  
  // All 5 bones validated successfully, set flag at +0x1B94
  this[0x6e5] = this[0x6e5] | 0x1000; // +0x1B94: animationBonesValid flag
  return;
}