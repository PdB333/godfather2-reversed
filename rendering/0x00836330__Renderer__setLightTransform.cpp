// FUNC_NAME: Renderer::setLightTransform
void __thiscall Renderer::setLightTransform(int param_1, int param_2)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  
  iVar8 = DAT_0112dbbc;
  if (DAT_0112dbbc != 0) {
    // Copy light direction (param_2 + 0xa0) scaled by intensity (param_2 + 0x50)
    fVar1 = *(float *)(param_2 + 0xa0);
    fVar2 = *(float *)(param_2 + 0x54);
    fVar3 = *(float *)(param_2 + 0x58);
    fVar4 = *(float *)(param_2 + 0x5c);
    *(float *)(DAT_0112dbbc + 0x10) = fVar1 * *(float *)(param_2 + 0x50);
    *(float *)(iVar8 + 0x14) = fVar1 * fVar2;
    *(float *)(iVar8 + 0x18) = fVar1 * fVar3;
    *(float *)(iVar8 + 0x1c) = fVar1 * fVar4;
    iVar8 = DAT_0112dbbc;
    // Copy light color (param_2 + 0xa4) scaled by ambient (param_2 + 0x80)
    fVar1 = *(float *)(param_2 + 0xa4);
    fVar2 = *(float *)(param_2 + 0x84);
    fVar3 = *(float *)(param_2 + 0x88);
    fVar4 = *(float *)(param_2 + 0x8c);
    *(float *)(DAT_0112dbbc + 0x20) = fVar1 * *(float *)(param_2 + 0x80);
    *(float *)(iVar8 + 0x24) = fVar1 * fVar2;
    *(float *)(iVar8 + 0x28) = fVar1 * fVar3;
    *(float *)(iVar8 + 0x2c) = fVar1 * fVar4;
    iVar8 = DAT_0112dbbc;
    // Copy light position (param_2 + 0x60)
    uVar5 = *(undefined4 *)(param_2 + 100);
    uVar6 = *(undefined4 *)(param_2 + 0x68);
    uVar7 = *(undefined4 *)(param_2 + 0x6c);
    *(undefined4 *)(DAT_0112dbbc + 0x30) = *(undefined4 *)(param_2 + 0x60);
    *(undefined4 *)(iVar8 + 0x34) = uVar5;
    *(undefined4 *)(iVar8 + 0x38) = uVar6;
    *(undefined4 *)(iVar8 + 0x3c) = uVar7;
    iVar8 = DAT_0112dbbc;
    // Copy light direction (param_2 + 0x70)
    uVar5 = *(undefined4 *)(param_2 + 0x74);
    uVar6 = *(undefined4 *)(param_2 + 0x78);
    uVar7 = *(undefined4 *)(param_2 + 0x7c);
    *(undefined4 *)(DAT_0112dbbc + 0x40) = *(undefined4 *)(param_2 + 0x70);
    *(undefined4 *)(iVar8 + 0x44) = uVar5;
    *(undefined4 *)(iVar8 + 0x48) = uVar6;
    *(undefined4 *)(iVar8 + 0x4c) = uVar7;
    // Copy camera view matrix rows from param_1
    *(undefined4 *)(DAT_0112dbbc + 0x50) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(DAT_0112dbbc + 0x60) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(DAT_0112dbbc + 0x54) = *(undefined4 *)(param_1 + 0xc4);
    *(undefined4 *)(DAT_0112dbbc + 0x58) = *(undefined4 *)(param_1 + 200);
    // Set flags: light enabled, directional, and shadow casting
    *(uint *)(DAT_0112dbbc + 0x5c) = *(uint *)(DAT_0112dbbc + 0x5c) | 1;
    *(uint *)(DAT_0112dbbc + 0x5c) = *(uint *)(DAT_0112dbbc + 0x5c) | 2;
    *(uint *)(DAT_0112dbbc + 0x5c) = *(uint *)(DAT_0112dbbc + 0x5c) | 4;
  }
  return;
}