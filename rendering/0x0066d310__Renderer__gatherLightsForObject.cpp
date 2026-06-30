// FUNC_NAME: Renderer::gatherLightsForObject
undefined1 FUN_0066d310(int param_1,undefined8 *param_2,undefined4 *param_3,void *param_4,float *param_5,
            void *param_6,int param_7)

{
  undefined4 *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined1 uVar10;
  undefined1 (*pauVar11) [16];
  undefined4 *puVar12;
  int *piVar13;
  int unaff_FS_OFFSET;
  bool bVar14;
  double dVar15;
  float fVar17;
  float fVar18;
  undefined1 auVar16 [16];
  float fVar19;
  undefined4 uVar20;
  int local_4c;
  undefined1 (*local_48) [16];
  undefined1 (*local_44) [16];
  undefined1 (*local_40) [16];
  int local_24;
  int local_20;
  
  *param_2 = 0;
  param_2[1] = 0;
  _memset(param_3,0,0x40); // Clear color buffer (16 floats)
  _memset(param_4,0,0x40); // Clear direction buffer
  _memset(param_5,0,0x40); // Clear position buffer
  _memset(param_6,0,0x40); // Clear attenuation buffer
  if (DAT_0120ec6c != (code *)0x0) {
    uVar10 = (*DAT_0120ec6c)(param_1,param_2,param_3,param_4,param_5,param_6,param_7,0);
    return uVar10;
  }
  iVar3 = **(int **)(unaff_FS_OFFSET + 0x2c); // Get current frame index
  iVar4 = *(int *)(*(int *)(DAT_012233a4 + 0x68) + 4 + *(int *)(iVar3 + 8)); // Get main light
  local_4c = 1;
  local_20 = param_7;
  if (3 < param_7) {
    local_20 = 4; // Clamp max lights to 4
  }
  bVar14 = (*(byte *)(param_1 + 0x94) & 0x10) != 0; // Check if object has specular flag
  iVar5 = *(int *)(param_1 + 0x98); // Number of light sources
  local_24 = 0;
  uVar20 = DAT_00e2b1a4; // Default ambient color
  if (0 < iVar5) {
    local_44 = (undefined1 (*) [16])((int)param_4 + 0x10); // Direction buffer offset
    puVar12 = (undefined4 *)((int)param_6 + 0x10); // Attenuation buffer offset
    pauVar11 = (undefined1 (*) [16])(param_5 + 4); // Position buffer offset
    local_48 = (undefined1 (*) [16])(param_3 + 4); // Color buffer offset
    piVar13 = (int *)(param_1 + 0x14); // Light source array
    local_40 = pauVar11;
    do {
      if (local_20 <= local_4c) break; // Max lights reached
      if (*piVar13 != 0) {
        *local_48 = *(undefined1 (*) [16])(piVar13 + -5); // Copy light color
        iVar6 = *(int *)(*piVar13 + 0x20); // Light type
        if (iVar6 == 3) { // Ambient light
          *(undefined4 *)((int)param_2 + local_4c * 4) = uVar20; // Set light type to ambient
          local_4c = local_4c + 1;
          *local_44 = *(undefined1 (*) [16])(*(int *)(*piVar13 + 0x18) + 0x30 + *(int *)(iVar3 + 8)); // Copy direction
          *puVar12 = *(undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x70 + *(int *)(iVar3 + 8)); // Copy attenuation
          local_48 = local_48 + 1;
          puVar12[1] = *(undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x78 + *(int *)(iVar3 + 8));
          local_44 = local_44 + 1;
          pauVar11 = pauVar11 + 1;
          puVar12 = puVar12 + 4;
          local_40 = pauVar11;
        }
        else if ((iVar6 == 1) && (*piVar13 != iVar4)) { // Directional light (not main)
          *(undefined4 *)((int)param_2 + local_4c * 4) = DAT_00e2b04c; // Set light type to directional
          if (bVar14) {
            puVar1 = (undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x40 + *(int *)(iVar3 + 8)); // Specular color
            uVar7 = puVar1[1];
            uVar8 = puVar1[2];
            uVar9 = puVar1[3];
            *(undefined4 *)*local_48 = *puVar1;
            *(undefined4 *)(*local_48 + 4) = uVar7;
            *(undefined4 *)(*local_48 + 8) = uVar8;
            *(undefined4 *)(*local_48 + 0xc) = uVar9;
          }
          pfVar2 = (float *)(*(int *)(*piVar13 + 0x18) + 0x20 + *(int *)(iVar3 + 8)); // Light position
          fVar17 = pfVar2[1];
          fVar18 = pfVar2[2];
          fVar19 = pfVar2[3];
          local_4c = local_4c + 1;
          *(float *)*pauVar11 = *pfVar2;
          *(float *)((int)*pauVar11 + 4) = fVar17;
          *(float *)((int)*pauVar11 + 8) = fVar18;
          *(float *)((int)*pauVar11 + 0xc) = fVar19;
          local_48 = local_48 + 1;
          local_44 = local_44 + 1;
          auVar16._0_4_ = DAT_00e2eff4 * *param_5; // Multiply by global light scale
          auVar16._4_4_ = DAT_00e2eff4 * param_5[1];
          auVar16._8_4_ = DAT_00e2eff4 * param_5[2];
          auVar16._12_4_ = DAT_00e2eff4 * param_5[3];
          *pauVar11 = auVar16;
          pauVar11 = pauVar11 + 1;
          puVar12 = puVar12 + 4;
          local_40 = pauVar11;
        }
        else if ((iVar6 == 4) || (iVar6 == 5)) { // Point or spot light
          *(undefined4 *)((int)param_2 + local_4c * 4) = DAT_00e445ac; // Set light type
          puVar1 = (undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x30 + *(int *)(iVar3 + 8)); // Light direction
          uVar20 = puVar1[1];
          uVar7 = puVar1[2];
          uVar8 = puVar1[3];
          *(undefined4 *)*local_44 = *puVar1;
          *(undefined4 *)(*local_44 + 4) = uVar20;
          *(undefined4 *)(*local_44 + 8) = uVar7;
          *(undefined4 *)(*local_44 + 0xc) = uVar8;
          *puVar12 = *(undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x70 + *(int *)(iVar3 + 8)); // Attenuation start
          puVar12[1] = *(undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x78 + *(int *)(iVar3 + 8)); // Attenuation end
          pfVar2 = (float *)(*(int *)(*piVar13 + 0x18) + 0x20 + *(int *)(iVar3 + 8)); // Light position
          fVar17 = pfVar2[1];
          fVar18 = pfVar2[2];
          fVar19 = pfVar2[3];
          *(float *)*pauVar11 = *pfVar2;
          *(float *)((int)*pauVar11 + 4) = fVar17;
          *(float *)((int)*pauVar11 + 8) = fVar18;
          *(float *)((int)*pauVar11 + 0xc) = fVar19;
          puVar12[2] = *(undefined4 *)(*(int *)(*piVar13 + 0x18) + 0x74 + *(int *)(iVar3 + 8)); // Attenuation power
          dVar15 = (double)*(float *)(*(int *)(*piVar13 + 0x18) + 0x6c + *(int *)(iVar3 + 8)); // Light range
          FUN_00b99e20(); // Some math function (likely sqrt or cos)
          uVar20 = DAT_00e2b1a4;
          local_4c = local_4c + 1;
          local_48 = local_48 + 1;
          local_44 = local_44 + 1;
          pauVar11 = local_40 + 1;
          puVar12[3] = (float)dVar15; // Store range
          puVar12 = puVar12 + 4;
          local_40 = pauVar11;
        }
      }
      local_24 = local_24 + 1;
      piVar13 = piVar13 + 8;
    } while (local_24 < iVar5);
  }
  *(undefined4 *)param_2 = DAT_00e2b04c; // Set first light type to directional
  fVar18 = DAT_00e4479c;
  fVar17 = DAT_00e44798;
  iVar5 = *(int *)(*(int *)(DAT_012233a4 + 0x68) + 4 + *(int *)(iVar3 + 8)); // Get main light again
  if (iVar5 == 0) {
    *param_5 = DAT_00e4479c; // Default light position
    param_5[2] = fVar18;
    param_5[1] = fVar17;
    param_5[3] = 0.0;
  }
  else {
    pfVar2 = (float *)(*(int *)(iVar5 + 0x18) + 0x20 + *(int *)(iVar3 + 8)); // Main light position
    fVar17 = pfVar2[1];
    fVar18 = pfVar2[2];
    fVar19 = pfVar2[3];
    *param_5 = *pfVar2;
    param_5[1] = fVar17;
    param_5[2] = fVar18;
    param_5[3] = fVar19;
  }
  fVar17 = DAT_00e2eff4 * param_5[1]; // Apply global light scale
  fVar18 = DAT_00e2eff4 * param_5[2];
  fVar19 = DAT_00e2eff4 * param_5[3];
  *param_5 = DAT_00e2eff4 * *param_5;
  param_5[1] = fVar17;
  param_5[2] = fVar18;
  param_5[3] = fVar19;
  if (iVar4 != 0) {
    puVar12 = (undefined4 *)(*(int *)(iVar4 + 0x18) + 0x40 + *(int *)(iVar3 + 8)); // Main light color
    uVar20 = puVar12[1];
    uVar7 = puVar12[2];
    uVar8 = puVar12[3];
    *param_3 = *puVar12;
    param_3[1] = uVar20;
    param_3[2] = uVar7;
    param_3[3] = uVar8;
    return bVar14;
  }
  *param_3 = uVar20; // Default ambient color
  param_3[1] = uVar20;
  param_3[2] = uVar20;
  param_3[3] = uVar20;
  return bVar14;
}