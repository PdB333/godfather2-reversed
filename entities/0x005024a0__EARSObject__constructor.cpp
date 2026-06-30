// FUNC_NAME: EARSObject::constructor
void __thiscall EARSObject::constructor(int *this, int *param_1)
{
  uint *puVar1;
  undefined4 *puVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int in_EAX;
  undefined4 *unaff_EDI;
  int unaff_FS_OFFSET;
  undefined4 in_XMM0_Da;
  undefined4 uVar8;
  uint local_18;
  uint uStack_14;
  
  FUN_00533cc0(); // likely base class constructor or some init
  *unaff_EDI = &PTR_FUN_00e37e18; // vtable setup
  if (*(char *)(in_EAX + 0xd) == '\0') {
    iVar4 = **(int **)(unaff_FS_OFFSET + 0x2c); // TLS or thread-local storage
    unaff_EDI[10] = unaff_EDI + 0x18; // +0x28: pointer to some internal buffer
    *(undefined2 *)(unaff_EDI + 0xb) = 0; // +0x2c: some short field
    unaff_EDI[0xc] = 0; // +0x30: some int field
    unaff_EDI[9] = param_1; // +0x24: store param_1 pointer
    unaff_EDI[0xd] = 0; // +0x34: some int field
    *(undefined2 *)((int)unaff_EDI + 0x2e) = 0xffff; // +0x2e: short = -1
    unaff_EDI[0xf] = 0; // +0x3c: some int field
    unaff_EDI[0xe] = param_1[0xb]; // +0x38: copy param_1[0x2c] (offset 0x2c in param_1)
    puVar1 = (uint *)(*(int *)(iVar4 + 8) + unaff_EDI[4]); // +0x10: some offset
    *puVar1 = *puVar1 & 0xfffffffe; // clear bit 0
    unaff_EDI[0x10] = 0; // +0x40: some float/int field
    if ((param_1[8] & 0x10000U) != 0) { // check flag 0x10000 in param_1[8] (offset 0x20)
      FUN_004e41b0(); // likely some initialization function
      unaff_EDI[0x10] = in_XMM0_Da; // store float result
    }
    uVar6 = DAT_00e2b1a4; // some global constant
    uVar8 = 0;
    puVar2 = (undefined4 *)(unaff_EDI[4] + 0x10 + *(int *)(iVar4 + 8)); // +0x10 + offset
    *puVar2 = DAT_00e2b1a4; // set first value
    puVar2[1] = 0;
    puVar2[2] = 0;
    puVar2[3] = 0;
    puVar2[4] = 0;
    puVar2[5] = uVar6;
    puVar2[6] = 0;
    puVar2[7] = 0;
    puVar2[8] = 0;
    puVar2[9] = 0;
    puVar2[10] = uVar6;
    puVar2[0xb] = 0; // initialize 12-element array (likely 3x4 matrix or similar)
    if ((param_1[8] & 2U) == 0) { // check flag 0x2
      if ((param_1[8] & 4U) != 0) { // check flag 0x4
        iVar5 = unaff_EDI[4];
        iVar4 = *(int *)(iVar4 + 8);
        *(int *)(iVar5 + 0x40 + iVar4) = param_1[0x15]; // +0x54: copy param_1[0x54]
        iVar4 = iVar5 + 0x40 + iVar4;
        *(int *)(iVar4 + 4) = param_1[0x16]; // +0x58: copy param_1[0x58]
        *(int *)(iVar4 + 8) = param_1[0x17]; // +0x5c: copy param_1[0x5c]
      }
    }
    else { // flag 0x2 set: additive mode
      pfVar3 = (float *)(unaff_EDI[4] + 0x40 + *(int *)(iVar4 + 8));
      *pfVar3 = (float)param_1[0x15] + *(float *)(unaff_EDI[4] + 0x40 + *(int *)(iVar4 + 8));
      pfVar3[1] = (float)param_1[0x16] + pfVar3[1];
      pfVar3[2] = (float)param_1[0x17] + pfVar3[2]; // add integer params as floats
    }
    FUN_004ebb40(); // some initialization
    unaff_EDI[0x11] = DAT_00e2eff4; // +0x44: copy global
    unaff_EDI[0x12] = uVar8; // +0x48: set to 0
    uVar6 = *(undefined4 *)(unaff_EDI[1] + 0x10); // +0x04 + 0x10: some value
    local_18 = 0;
    uStack_14 = 0;
    if ((*param_1 != 0 || param_1[1] != 0) || (param_1[2] != 0 || param_1[3] != 0)) {
      local_18 = FUN_004e9270(); // likely hash or ID generation
      if ((local_18 != 0) &&
         ((((local_18 != 0xffffffff && (local_18 < 0x1000)) && (local_18 * 0x38 != -0x11a0f28)) &&
          (piVar7 = *(int **)(&DAT_011a0f38 + local_18 * 0x38), piVar7 != (int *)0x0)))) {
        *piVar7 = *piVar7 + 1; // increment reference count
      }
    }
    if ((param_1[4] != 0 || param_1[5] != 0) || (param_1[6] != 0 || param_1[7] != 0)) {
      uStack_14 = FUN_004e9270();
      if ((((uStack_14 != 0) && ((uStack_14 != 0xffffffff && (uStack_14 < 0x1000)))) &&
          (uStack_14 * 0x38 != -0x11a0f28)) &&
         (piVar7 = *(int **)(&DAT_011a0f38 + uStack_14 * 0x38), piVar7 != (int *)0x0)) {
        *piVar7 = *piVar7 + 1;
      }
    }
    FUN_005021a0(unaff_EDI,CONCAT44(param_1,uVar6),CONCAT44(uStack_14,local_18),unaff_EDI[4],
                 unaff_EDI[5]); // final initialization call
  }
  return;
}