// FUNC_NAME: Renderer::processDrawCall
undefined4 Renderer::processDrawCall(int param_1, int *param_2, int *param_3, undefined4 *param_4)

{
  int in_EAX;
  uint uVar1;
  undefined4 uVar2;
  uint *unaff_ESI;
  uint uVar3;
  undefined4 uVar4;
  int local_8;
  uint local_4;
  
  local_4 = unaff_ESI[3]; // +0x0C: source height
  uVar3 = unaff_ESI[4];   // +0x10: source width
  local_8 = DAT_012056b4;  // global render target width
  if (param_1 == 1) {
    uVar3 = 0x800;
    local_8 = 0x800;
  }
  uVar2 = *(undefined4 *)(DAT_01205668 + 0xc); // renderer context +0x0C
  if ((*unaff_ESI & 0xf000000) == 0) { // check if draw call is valid
    *param_4 = 0;
    return 1;
  }
  if (in_EAX == 0) {
    DAT_0119dac0 = 0; // reset some global state
  }
  else {
    FUN_005cdd30(); // flush pending draw calls
  }
  uVar1 = unaff_ESI[9] & 0x70000; // +0x24: texture flags
  uVar4 = DAT_00e2b198; // default texture
  if (((uVar1 != 0x10000) && (uVar4 = DAT_00e2b19c, uVar1 != 0x20000)) &&
     (uVar4 = DAT_00e2b1a0, uVar1 != 0x40000)) {
    uVar4 = DAT_00e2b1a4; // fallback texture
  }
  uVar2 = FUN_00670550(uVar2, // renderer context
                       *unaff_ESI & 0xf0ffffff, // clear upper bits of flags
                       (int)(float)unaff_ESI[1], // +0x04: z value
                       &local_8, // output width
                       &local_4, // output height
                       0,
                       unaff_ESI[6], // +0x18: source x
                       uVar3, // source width
                       unaff_ESI[5], // +0x14: source y
                       unaff_ESI[7], // +0x1C: source height
                       uVar4, // texture handle
                       unaff_ESI[2]); // +0x08: scale factor
  *param_2 = (int)((float)local_8 * (float)unaff_ESI[2]); // scaled output width
  *param_3 = (int)((float)(int)local_4 * (float)unaff_ESI[2]); // scaled output height
  *param_4 = uVar2; // return value from render call
  return 1;
}