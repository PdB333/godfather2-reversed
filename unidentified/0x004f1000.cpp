// FUN_004f1000: Character::applyJointForce

void __thiscall Character::applyJointForce(int param2)
{
  int iVar1;
  float currentVal, diff1, diff2;
  float clamped1, clamped2;
  const float kMaxForce = DAT_00e2b1a4; // Global maximum force clamp
  
  // Assume FUN_00423860 processes param2 (e.g., validate target)
  FUN_00423860(param2);
  // Assume FUN_00417560 performs pre-apply checks
  FUN_00417560();
  
  // Current value from character state (e.g., health, velocity)
  // +0x4 points to a sub-object (e.g., CharacterState)
  currentVal = *(float *)(*(int *)(this + 4) + 0x8c); // +0x8c: current magnitude
  
  // Array of joint parameters indexed by this+0xe (short index)
  // Sub-object +0x10 points to base of joint array, +0x30 offset, index multiplied by 0x24 (36 bytes per joint)
  iVar1 = *(int *)(*(int *)(this + 4) + 0x10) + 0x30 + *(short *)(this + 0xe) * 0x24;
  
  // Diff = (currentVal - threshold) * multiplier, clamped to [0, kMaxForce]
  diff1 = currentVal - *(float *)(iVar1 + 0x18); // +0x18: threshold1
  diff1 *= *(float *)(iVar1 + 0x14);             // +0x14: multiplier1
  if (diff1 <= 0.0f)
    clamped1 = 0.0f;
  else if (diff1 >= kMaxForce)
    clamped1 = kMaxForce;
  else
    clamped1 = diff1;
  
  diff2 = currentVal - *(float *)(iVar1 + 0x20); // +0x20: threshold2
  diff2 *= *(float *)(iVar1 + 0x1c);             // +0x1c: multiplier2
  if (diff2 <= 0.0f)
    clamped2 = 0.0f;
  else if (diff2 >= kMaxForce)
    clamped2 = kMaxForce;
  else
    clamped2 = diff2;
  
  // Call virtual function index 2 via vtable from this+0x28
  // Parameters: param2, globalContext+offset, local buffer 76 bytes, this+0x24, this+0x30, product of clamps
  // Global context: FS[0x2c] -> pointer -> +8 -> value -> +0x50 + this+0x10
  int* globalPtr = reinterpret_cast<int*>(*(int*)(FS_OFFSET + 0x2c));
  int contextAddr = *(int*)(*globalPtr + 8) + 0x50 + *(int*)(this + 0x10);
  
  (**(code **)(**(int **)(this + 0x28) + 8))
    (param2, contextAddr, (undefined1*)local_50, *(int*)(this + 0x24), (void*)(this + 0x30), clamped1 * clamped2);
}