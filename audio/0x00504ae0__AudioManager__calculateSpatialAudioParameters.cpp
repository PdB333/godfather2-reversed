// FUNC_NAME: AudioManager::calculateSpatialAudioParameters
uint __fastcall AudioManager::calculateSpatialAudioParameters(int this, int audioObject)
{
  float *pfVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  float fVar6;
  undefined1 *puVar7;
  int iVar8;
  int unaff_FS_OFFSET;
  float fVar9;
  float fVar10;
  float fVar11;
  
  // Get audio data entry from pool (max 0x1000 entries, each 0x38 bytes)
  if (*(uint *)(audioObject + 0x16c) < 0x1000) {
    puVar7 = &DAT_011a0f28 + *(uint *)(audioObject + 0x16c) * 0x38;
  }
  else {
    puVar7 = (undefined1 *)0x0;
  }
  
  fVar10 = *(float *)(this + 0x5c); // +0x5c: current listener distance
  iVar3 = *(int *)(this + 0x20);    // +0x20: audio settings pointer
  uVar2 = *(ushort *)(puVar7 + 4);  // +0x04: audio data width (spread)
  fVar9 = (float)*(ushort *)(puVar7 + 2); // +0x02: audio data height (elevation)
  
  // Calculate volume based on distance and audio data dimensions
  *(float *)(this + 0x44) = (fVar10 / fVar9) * *(float *)(iVar3 + 0x3c) * DAT_00e44760;
  
  fVar6 = DAT_00e2b1a4; // Global max value (likely 1.0)
  fVar10 = DAT_00e2b1a4 -
           ((fVar10 * fVar10 + *(float *)(this + 0x60) * *(float *)(this + 0x60)) *
           DAT_00e2d99c) / ((float)uVar2 * (float)uVar2 + fVar9 * fVar9);
  
  // Clamp pan value to [0, 1]
  *(float *)(this + 0x4c) = fVar10;
  if (0.0 < fVar10) {
    if (fVar6 <= fVar10) {
      fVar10 = fVar6;
    }
  }
  else {
    fVar10 = 0.0;
  }
  *(float *)(this + 0x4c) = fVar10 * fVar10; // +0x4c: squared pan value
  
  uVar4 = *(uint *)(iVar3 + 0x14); // +0x14: audio flags
  if ((uVar4 & 0x70000) != 0) {
    // Determine spatialization mode (0=2D, 1=3D, 2=surround)
    iVar8 = 0;
    if ((uVar4 & 0x20000) == 0) {
      if ((uVar4 & 0x40000) != 0) {
        iVar8 = 2;
      }
    }
    else {
      iVar8 = 1;
    }
    
    // Get listener position from thread-local storage
    iVar5 = *(int *)(**(int **)(unaff_FS_OFFSET + 0x2c) + 8);
    pfVar1 = (float *)(*(int *)(this + 8) + 0x80 + iVar5); // +0x08: listener transform
    fVar10 = *pfVar1;
    fVar9 = pfVar1[1];
    fVar11 = pfVar1[2];
    
    // Add audio source offset if not using world-space coordinates
    if ((uVar4 & 6) == 0) {
      fVar10 = *(float *)(iVar3 + 0x30) + fVar10;
      fVar9 = *(float *)(iVar3 + 0x34) + fVar9;
      fVar11 = *(float *)(iVar3 + 0x38) + fVar11;
    }
    
    // Calculate vector from listener to audio source
    fVar10 = fVar10 - *(float *)(audioObject + 0x70);
    fVar9 = fVar9 - *(float *)(audioObject + 0x74);
    fVar11 = fVar11 - *(float *)(audioObject + 0x78);
    
    // Calculate spatial blend factor using dot product with listener orientation
    iVar8 = (iVar8 + 5) * 0x10 + *(int *)(this + 8);
    fVar10 = ((DAT_00e44564 -
              (*(float *)(iVar8 + 4 + iVar5) * fVar9 + *(float *)(iVar8 + 8 + iVar5) * fVar11 +
              *(float *)(iVar8 + iVar5) * fVar10) /
              (SQRT(fVar9 * fVar9 + fVar11 * fVar11 + fVar10 * fVar10) + (float)PTR_FUN_00e4462c)) -
             *(float *)(iVar3 + 0x40)) / (fVar6 - *(float *)(iVar3 + 0x40));
    
    // Clamp blend factor to [0, 1]
    if (0.0 < fVar10) {
      if (fVar6 <= fVar10) {
        fVar10 = fVar6;
      }
    }
    else {
      fVar10 = 0.0;
    }
    
    // Calculate final spatial volume with curve interpolation
    fVar10 = fVar6 - fVar10;
    *(float *)(this + 0x50) =
         (fVar6 - fVar10 * fVar10 * fVar10 * fVar10) * *(float *)(iVar3 + 0x44) +
         (fVar6 - fVar10) * (fVar6 - *(float *)(iVar3 + 0x44));
    return iVar8 + iVar5;
  }
  
  // No spatialization - use full volume
  *(float *)(this + 0x50) = fVar6;
  return uVar4;
}