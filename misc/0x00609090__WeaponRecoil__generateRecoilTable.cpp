// FUNC_NAME: WeaponRecoil::generateRecoilTable
void WeaponRecoil::generateRecoilTable(int param_1)
{
  float fVar1;
  float fVar2;
  undefined2 uVar3;
  int iVar4;
  float fVar5;
  double dVar6;
  float fVar7;
  float local_24;

  fVar1 = *(float *)(param_1 + 4); // +0x04 recoilAmountX (or initial recoil)
  fVar2 = *(float *)(param_1 + 8); // +0x08 recoilAmountY (or recoil spread)
  fVar5 = (DAT_00e2b1a4 - fVar1) * DAT_00e2cd54; // DAT_00e2b1a4 = maxRecoil? DAT_00e2cd54 = recoilFactorPerFrame
  iVar4 = 0;
  do {
    dVar6 = (double)((float)iVar4 * DAT_00e44640); // DAT_00e44640 = recoilStepAngle (in radians per sample)
    FUN_00b9af10(); // likely sin/cos or math function
    local_24 = (float)dVar6 * fVar1 + fVar5 + fVar2; // compute recoil offset for this step
    fVar7 = 0.0;
    if ((local_24 < 0.0) || (fVar7 = DAT_00e2b1a4, DAT_00e2b1a4 < local_24)) {
      local_24 = fVar7; // clamp to [0, maxRecoil]
    }
    iVar4 = iVar4 + 1;
    uVar3 = (undefined2)(longlong)ROUND(local_24 * DAT_00e2e22c); // DAT_00e2e22c = scale factor to convert to fixed point (likely 0x10000 or similar)
    *(undefined2 *)(iVar4 * 2 + 0x11d91e6) = uVar3; // +0x11d91e6 = recoilTable1
    *(undefined2 *)(iVar4 * 2 + 0x11d93e6) = uVar3; // +0x11d93e6 = recoilTable2
    *(undefined2 *)(iVar4 * 2 + 0x11d95e6) = uVar3; // +0x11d95e6 = recoilTable3
  } while (iVar4 < 0x100); // 256 entries
  (**(code **)(*DAT_01205750 + 0x54))(DAT_01205750,0,0,&DAT_011d91e8); // call to send/upload table to GPU (maybe D3D9 or EA Render)
  return;
}