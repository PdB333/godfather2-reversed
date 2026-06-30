// FUNC_NAME: ShadowMapRenderer::computeShadowVisibility
void ShadowMapRenderer::computeShadowVisibility(int param_1, uint param_2, int param_3)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined1 auVar5 [16];
  undefined1 auVar6 [16];
  float fVar7;
  int in_EAX;
  float *pfVar8;
  uint uVar9;
  uint uVar10;
  uint unaff_EBX;
  uint uVar11;
  int iVar12;
  float *pfVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  int local_40;
  byte local_38 [52];
  
  fVar7 = DAT_00e2b1a4; // Some global constant (likely shadow bias or light direction component)
  // Gather visibility flags from 5 cascade levels (each 0x60 bytes apart)
  local_38[0] = *(byte *)(in_EAX + 0x60);   // Cascade 0 visibility
  local_38[1] = *(undefined1 *)(in_EAX + 0x120); // Cascade 1
  local_38[2] = *(undefined1 *)(in_EAX + 0x1e0); // Cascade 2
  local_38[3] = *(byte *)(in_EAX + 0x2a0);   // Cascade 3
  local_38[4] = *(undefined1 *)(in_EAX + 0x360); // Cascade 4
  local_40 = 0;
  if (0 < param_3) {
    pfVar13 = (float *)(param_1 + 8); // Start of vertex data (x,y,z,w per vertex)
    uVar10 = (uint)*(byte *)(in_EAX + 0x2a0); // Cascade 3 visibility flag
    do {
      fVar1 = pfVar13[-2]; // Vertex x
      fVar2 = pfVar13[-1]; // Vertex y
      fVar3 = *pfVar13;    // Vertex z
      fVar4 = pfVar13[1];  // Vertex w (homogeneous or depth)
      uVar9 = 0;
      iVar12 = 0;
      pfVar8 = (float *)(in_EAX + 0x20); // Start of cascade data (each 0xC0 bytes = 0x30 floats)
      do {
        // Transform vertex into shadow map space for each cascade
        fVar14 = pfVar8[0xb] * fVar7 + pfVar8[10] * fVar3;
        fVar15 = pfVar8[9] * fVar2 + pfVar8[8] * fVar1;
        fVar16 = pfVar8[0xf] * fVar7 + pfVar8[0xe] * fVar3;
        fVar17 = pfVar8[0xd] * fVar2 + pfVar8[0xc] * fVar1;
        // Compare depth against shadow map values (4 samples per cascade)
        auVar5._4_4_ = -(uint)(fVar4 < pfVar8[-7] * fVar2 + pfVar8[-8] * fVar1 +
                                       pfVar8[-5] * fVar7 + pfVar8[-6] * fVar3);
        auVar5._0_4_ = -(uint)(fVar4 < pfVar8[-3] * fVar2 + pfVar8[-4] * fVar1 +
                                       pfVar8[-1] * fVar7 + pfVar8[-2] * fVar3);
        auVar5._8_4_ = -(uint)(fVar4 < pfVar8[5] * fVar2 + pfVar8[4] * fVar1 +
                                       pfVar8[7] * fVar7 + pfVar8[6] * fVar3);
        auVar5._12_4_ =
             -(uint)(fVar4 < pfVar8[1] * fVar2 + *pfVar8 * fVar1 +
                             pfVar8[3] * fVar7 + pfVar8[2] * fVar3);
        uVar11 = movmskps(unaff_EBX,auVar5); // Extract sign bits as mask
        // Also check against transformed coordinates (bilinear filter)
        auVar6._4_4_ = -(uint)(fVar4 < fVar15 + fVar14);
        auVar6._0_4_ = -(uint)(fVar4 < fVar17 + fVar16);
        auVar6._8_4_ = -(uint)(fVar4 < fVar17 + fVar16);
        auVar6._12_4_ = -(uint)(fVar4 < fVar15 + fVar14);
        uVar10 = movmskps(uVar10,auVar6);
        unaff_EBX = (uint)local_38[iVar12]; // Get cascade visibility flag
        iVar12 = iVar12 + 1;
        pfVar8 = pfVar8 + 0x30; // Next cascade (0xC0 bytes)
        uVar10 = (0 < (int)(uVar10 | uVar11)) - 1 & unaff_EBX; // Combine shadow test with cascade visibility
        uVar9 = uVar9 | uVar10;
      } while (iVar12 < 5); // 5 cascade levels
      *(char *)(local_40 + param_2) = (char)uVar9; // Store visibility result per vertex
      local_40 = local_40 + 1;
      pfVar13 = pfVar13 + 4; // Next vertex
      uVar10 = param_2;
    } while (local_40 < param_3);
  }
  return;
}