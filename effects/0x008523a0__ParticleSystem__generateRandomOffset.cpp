// FUNC_NAME: ParticleSystem::generateRandomOffset
void __thiscall ParticleSystem::generateRandomOffset(int this, float *outOffset)
{
  float fVar1;
  float fVar2;
  float *pfVar3;
  float *pfVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  double dVar10;
  
  fVar1 = *(float *)(this + 0x2c); // +0x2c: randomRangeX
  iVar5 = _rand();
  fVar6 = (float)iVar5 * DAT_00e44590; // DAT_00e44590: 1.0f / RAND_MAX
  fVar2 = *(float *)(this + 0x30); // +0x30: randomRangeY
  iVar5 = _rand();
  fVar7 = (float)iVar5 * DAT_00e44590;
  iVar5 = _rand();
  fVar8 = (float)iVar5 * DAT_00e44590 * DAT_00d5d70c; // DAT_00d5d70c: some scaling factor
  dVar10 = (double)fVar8;
  FUN_00b99fcb(); // likely cosf
  fVar9 = (float)dVar10 * fVar6 * fVar1;
  dVar10 = (double)fVar8;
  FUN_00b99e20(); // likely sinf
  fVar1 = *(float *)(this + 0xc); // +0xc: baseOffsetX
  pfVar3 = *(float **)(this + 0x24); // +0x24: axis1 pointer
  fVar6 = *(float *)(this + 0x20); // +0x20: baseOffsetZ
  pfVar4 = *(float **)(this + 0x28); // +0x28: axis2 pointer
  fVar8 = pfVar3[2]; // axis1.z
  fVar7 = (float)dVar10 * fVar7 * fVar2;
  fVar2 = pfVar4[2]; // axis2.z
  *outOffset = CONCAT44(pfVar4[1] * fVar7 + pfVar3[1] * fVar9 + *(float *)(this + 0x1c) * fVar1,
                      fVar7 * *pfVar4 + *pfVar3 * fVar9 + *(float *)(this + 0x18) * fVar1);
  *(float *)(outOffset + 1) = fVar2 * fVar7 + fVar8 * fVar9 + fVar6 * fVar1;
  return;
}