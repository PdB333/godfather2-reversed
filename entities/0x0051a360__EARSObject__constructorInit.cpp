// FUNC_NAME: EARSObject::constructorInit
void __thiscall EARSObject::constructorInit(EARSObject *this, int param_1)
{
  int *piVar1;
  byte bVar2;
  int iVar3;
  bool bVar4;
  float fVar5;
  float fVar6;
  
  // Set vtable pointer
  *(int *)this = &PTR_FUN_00e3825c;
  // +0x04: next sibling? set to 0
  *(int *)(this + 1) = 0;
  // +0x08: first child? set to 0
  *(int *)(this + 2) = 0;
  // +0x18: some pointer/reference (at offset 6 ints) set to 0
  *(int *)(this + 6) = 0;
  // +0x1c: set to 0
  *(int *)(this + 7) = 0;
  // +0x20: set to 0
  *(int *)(this + 8) = 0;
  piVar1 = (int *)(this + 6); // pointer to +0x18
  // +0xb0: default value 2 (object type? state?)
  *(int *)(this + 0x2c) = 2;
  // +0xb4: 0
  *(int *)(this + 0x2d) = 0;
  // +0xb8: -1 (invalid handle/index)
  *(int *)(this + 0x2e) = 0xffffffff;
  // +0xbc: 0
  *(int *)(this + 0x2f) = 0;
  // +0xc4: 0
  *(int *)(this + 0x31) = 0;
  // +0xc8: 0
  *(int *)(this + 0x32) = 0;
  
  // Manage list (tree) insertion? DAT_01205518 is some global list head
  if (*piVar1 != DAT_01205518) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // removeFromList?
    }
    iVar3 = DAT_01205518;
    bVar4 = DAT_01205518 != 0;
    *piVar1 = DAT_01205518;
    if (bVar4) {
      *(int *)(this + 7) = *(int *)(iVar3 + 4); // +0x1c = old head's next
      *(int **)(iVar3 + 4) = piVar1;             // old head's next = new node
    }
  }
  
  fVar5 = DAT_00e2b1a4; // some constant float (1.0f?)
  
  // +0x0c: flags = 0x10000000 (some engine flag)
  *(int *)(this + 3) = 0x10000000;
  // +0x10: set from param_1 (parent object? context?)
  *(int *)(this + 4) = param_1;
  // +0xa0 through +0xac: four floats set to same value (quaternion? or position?)
  *(float *)(this + 0x28) = fVar5;
  *(float *)(this + 0x29) = fVar5;
  *(float *)(this + 0x2a) = fVar5;
  *(float *)(this + 0x2b) = fVar5;
  
  // Copy a value from param_1 + 0x20
  *(int *)(this + 0x22) = *(int *)(param_1 + 0x20);
  
  // Set flags based on param_1's flags
  if ((*(uint *)(param_1 + 0x14) & 0x200) != 0) {
    *(int *)(this + 3) = *(int *)(this + 3) | 0x40000000;
  }
  if ((*(uint *)(param_1 + 0x14) & 0x20000000) != 0) {
    *(int *)(this + 3) = *(int *)(this + 3) | 0x80000000;
  }
  if ((*(uint *)(param_1 + 0x14) & 0x100) != 0) {
    *(int *)(this + 3) = *(int *)(this + 3) | 0x400000;
  }
  
  // +0xe0: copy from param_1 + 0x18
  *(float *)(this + 0x38) = *(float *)(param_1 + 0x18);
  
  fVar6 = fVar5;
  if (DAT_00e2b05c < *(float *)(param_1 + 0x18)) {
    bVar2 = *(byte *)(param_1 + 0x16);
    FUN_004e41b0(); // random/pseudo function?
    fVar6 = DAT_00e2b1a4;
    *(float *)(this + 0x38) =
         (float)(bVar2 & 0x1f) * fVar5 * *(float *)(param_1 + 0x18) * DAT_00e2e780 +
         *(float *)(this + 0x38);
  }
  
  // +0x14: reference count set to 0
  *(int *)(this + 5) = 0;
  
  // Manage reference on +0x20 child: decrement and possibly delete
  if (*(int *)(this + 8) != 0) {
    piVar1 = (int *)(*(int *)(this + 8) + 4);
    *piVar1 = *piVar1 + -1;
    if (*(int *)(*(int *)(this + 8))[1] == 0) {
      (**(code **)(*(int *)(*(int *)(this + 8)) + 4))(); // delete/release
    }
    *(int *)(this + 8) = 0;
  }
  
  *(int *)(this + 8) = 0; // reset child pointer
  
  // Zero out +0x7c through +0x8c (some state)
  *(int *)(this + 0x1f) = 0;
  *(float *)(this + 0x24) = fVar6;
  *(float *)(this + 0x23) = fVar6;
  *(short *)(this + 0x20) = 0;
  *(short *)((int)this + 0x82) = 0x1c;
  *(int *)(this + 0x21) = 0xffffffff;
  
  // Initialize a series of vector/color values
  *(float *)(this + 0xc) = fVar6;
  *(int *)(this + 0xd) = 0;
  *(int *)(this + 0xe) = 0;
  *(int *)(this + 0xf) = 0;
  *(int *)(this + 0x10) = 0;
  *(float *)(this + 0x11) = fVar6;
  *(int *)(this + 0x12) = 0;
  *(int *)(this + 0x13) = 0;
  *(int *)(this + 0x14) = 0;
  *(int *)(this + 0x15) = 0;
  *(float *)(this + 0x16) = fVar6;
  *(int *)(this + 0x17) = 0;
  *(int *)(this + 0x18) = 0;
  *(int *)(this + 0x19) = 0;
  *(int *)(this + 0x1a) = 0;
  *(float *)(this + 0x1b) = fVar6;
  return;
}