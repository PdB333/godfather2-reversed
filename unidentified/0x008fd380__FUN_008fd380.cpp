// FUNC_NAME: SomeClass::setAnimationOrState
void __thiscall SomeClass::setAnimationOrState(int this, int param_2, int param_3, uint param_4)
{
  undefined4 uVar1;
  
  // If there's an existing animation/state at +0x1c, clear it first
  if (*(int *)(this + 0x1c) != 0) {
    FUN_008fbcf0(); // likely clearAnimation or resetState
  }
  param_4 = param_4 | 1;
  *(int *)(this + 0x1c) = param_2; // +0x1c: current animation/state pointer
  *(undefined4 *)(this + 0x18) = 2; // +0x18: state type (2 = animation?)
  if (param_3 == 1) {
    param_2 = param_2 + 0xec; // offset for type 1
  }
  else {
    if (param_3 != 2) goto LAB_008fd3d5;
    param_2 = param_2 + 0xfc; // offset for type 2
  }
  uVar1 = FUN_008fc140(param_2); // likely getAnimationData or getStateData
  FUN_008fd000(uVar1, param_4); // likely startAnimation or applyState
LAB_008fd3d5:
  FUN_008fcb40(param_3 == 2); // likely setLooping or setFlag
  return;
}