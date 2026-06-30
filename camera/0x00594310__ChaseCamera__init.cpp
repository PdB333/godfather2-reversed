// FUNC_NAME: ChaseCamera::init
undefined4 __thiscall ChaseCamera::init(ChaseCamera *this, int *param_2, char in_stack_00000018)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  // +0x160: store a 32-bit value from 4 bytes (big-endian conversion)
  *(int *)((int)this + 0x160) =
       ((*param_2 * 0x100 + param_2[1]) * 0x100 + param_2[2]) * 0x100 + param_2[3];
  
  // Call some initialization function
  FUN_0059b5e0();
  
  // Load global constants
  uVar2 = DAT_00e2b1a4;
  uVar1 = DAT_00e2afac;
  
  // +0x14c: set to 0
  *(undefined4 *)((int)this + 0x14c) = 0;
  // +0xb8: set to 0
  *(undefined4 *)((int)this + 0xb8) = 0;
  // +0x130: set from global
  *(undefined4 *)((int)this + 0x130) = uVar2;
  // +0x134: set from global
  *(undefined4 *)((int)this + 0x134) = uVar2;
  // +0xb0: set from global
  *(undefined4 *)((int)this + 0xb0) = uVar2;
  // +0xb4: set from another global
  *(undefined4 *)((int)this + 0xb4) = DAT_00e35654;
  
  // +0x7c: bitfield manipulation - set bits based on in_stack_00000018 flag
  *(uint *)((int)this + 0x7c) =
       (in_stack_00000018 != '\0' | 0x1c2) * 4 | *(uint *)((int)this + 0x7c) & 0xfffff70a;
  
  // +0x138: set from global
  *(undefined4 *)((int)this + 0x138) = uVar1;
  // +0x140: set to 8
  *(undefined4 *)((int)this + 0x140) = 8;
  // +0x15c: set to 0
  *(undefined4 *)((int)this + 0x15c) = 0;
  
  // Call a function via vtable (likely some math/vector setup)
  // First call: (0,0,0,1.0f, &this->0xa0) - probably set a quaternion or vector
  (**(code **)(*DAT_012055a8 + 4))(0,0,0,0x3f800000,(int)this + 0xa0);
  // Second call: (0,0,1.0f,0, &this->0x80) - probably set another vector/quaternion
  (**(code **)(*DAT_012055a8 + 4))(0,0,0x3f800000,0,(int)this + 0x80);
  
  return 1;
}