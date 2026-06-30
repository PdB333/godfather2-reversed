// FUNC_NAME: CameraManager::updateCameraTransform
void __thiscall CameraManager::updateCameraTransform(float *cameraMatrix, float fov)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  int iVar19;
  float *in_EAX;
  int unaff_ESI;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float local_60;
  float local_5c;
  undefined4 local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  
  // +0x128: pointer to current camera matrix (input)
  *(float **)(unaff_ESI + 0x128) = in_EAX;
  // +0x12C (300): pointer to camera matrix (output)
  *(float **)(unaff_ESI + 300) = cameraMatrix;
  // +0x130: field of view
  *(float *)(unaff_ESI + 0x130) = fov;
  
  // Check if this is the main camera (DAT_012058e8) and has more than 1 active view
  if ((DAT_012058e8 == unaff_ESI) && (1 < *(uint *)(unaff_ESI + 0x134))) {
    // Extract camera matrix rows (4x4 matrix stored as 16 floats)
    fVar1 = cameraMatrix[8];   // row 2, col 0
    fVar2 = cameraMatrix[9];   // row 2, col 1
    fVar3 = *cameraMatrix;     // row 0, col 0
    fVar4 = cameraMatrix[3];   // row 0, col 3
    fVar5 = cameraMatrix[2];   // row 0, col 2
    fVar6 = cameraMatrix[10];  // row 2, col 2
    fVar7 = cameraMatrix[0xc]; // row 3, col 0
    fVar8 = cameraMatrix[0xd]; // row 3, col 1
    fVar9 = cameraMatrix[0xe]; // row 3, col 2
    fVar10 = cameraMatrix[0xb];// row 2, col 3
    fVar11 = cameraMatrix[1];  // row 0, col 1
    fVar12 = cameraMatrix[4];  // row 1, col 0
    
    // Compute projection matrix row 0 (x component)
    local_40 = fVar4 * in_EAX[0xf] + fVar5 * in_EAX[0xb] + fVar11 * in_EAX[7] + fVar3 * in_EAX[3];
    
    fVar13 = cameraMatrix[5];  // row 1, col 1
    fVar14 = cameraMatrix[6];  // row 1, col 2
    fVar15 = cameraMatrix[0xf];// row 3, col 3
    fVar16 = cameraMatrix[7];  // row 1, col 3
    
    // Compute projection matrix row 1 (y component)
    local_3c = fVar16 * in_EAX[0xf] + fVar14 * in_EAX[0xb] + fVar13 * in_EAX[7] + fVar12 * in_EAX[3];
    
    // Compute projection matrix row 2 (z component)
    local_14 = fVar10 * in_EAX[0xf] + fVar6 * in_EAX[0xb] + fVar2 * in_EAX[7] + fVar1 * in_EAX[3];
    
    // Compute inverse field of view scaling factor
    fov = DAT_00e2b1a4 / fov;
    
    // Precompute dot products for translation components
    fVar20 = fVar7 * in_EAX[3];
    fVar21 = fVar8 * in_EAX[7];
    fVar22 = fVar9 * in_EAX[0xb];
    fVar23 = fVar15 * in_EAX[0xf];
    
    // Compute view matrix row 0 (x axis)
    local_60 = ((((fVar4 * in_EAX[0xc] + fVar5 * in_EAX[8] + fVar11 * in_EAX[4] + fVar3 * *in_EAX) -
                 fVar20) - fVar21) - fVar22) - fVar23;
    
    // Compute view matrix row 1 (y axis)
    local_5c = fVar16 * in_EAX[0xc] + fVar14 * in_EAX[8] + fVar13 * in_EAX[4] + fVar12 * *in_EAX;
    local_58 = 0;
    
    // Compute view matrix row 3 (z axis)
    local_54 = fVar15 * in_EAX[0xc] + fVar9 * in_EAX[8] + fVar8 * in_EAX[4] + fVar7 * *in_EAX;
    
    fVar17 = in_EAX[5];
    fVar18 = in_EAX[1];
    
    // Compute view matrix row 0 (y axis) for second pass
    local_30 = fVar4 * in_EAX[0xd] + fVar5 * in_EAX[9] + fVar11 * fVar17 + fVar3 * fVar18;
    
    fVar3 = in_EAX[9];
    
    // Compute view matrix row 1 (y axis) for second pass
    local_2c = ((((fVar16 * in_EAX[0xd] + fVar14 * fVar3 + fVar13 * fVar17 + fVar12 * fVar18) -
                 fVar20) - fVar21) - fVar22) - fVar23;
    
    // Compute view matrix row 3 (y axis) for second pass
    local_24 = fVar15 * in_EAX[0xd] + fVar9 * fVar3 + fVar8 * fVar17 + fVar7 * fVar18;
    
    // Apply screen center offset (DAT_00e44564)
    local_4c = DAT_00e44564 - local_3c;
    local_50 = DAT_00e44564 - local_40;
    
    // Compute depth scaling
    local_34 = (fVar23 + fVar22 + fVar21 + fVar20) * fov;
    
    // Apply FOV scaling to projection
    local_40 = fov * local_40;
    local_3c = fov * local_3c;
    
    local_28 = 0;
    local_48 = 0;
    local_44 = 0;
    local_38 = 0;
    
    // Compute view matrix row 2 (z axis) for second pass
    local_20 = fVar10 * in_EAX[0xc] + fVar6 * in_EAX[8] + fVar2 * in_EAX[4] + fVar1 * *in_EAX;
    local_1c = fVar10 * in_EAX[0xd] + fVar6 * fVar3 + fVar2 * fVar17 + fVar1 * fVar18;
    local_18 = DAT_00e44564 - local_14;
    local_14 = fov * local_14;
    
    // Set camera transform matrices via helper function
    // +0x10: camera object pointer
    // +0x2C4: view matrix slot 0
    FUN_0060add0(*(undefined4 *)(unaff_ESI + 0x10), *(undefined4 *)(unaff_ESI + 0x2c4), &local_60);
    // +0x2C8: view matrix slot 1
    FUN_0060add0(*(undefined4 *)(unaff_ESI + 0x10), *(undefined4 *)(unaff_ESI + 0x2c8), &local_30);
    // +0x2CC: projection matrix slot 0
    FUN_0060add0(*(undefined4 *)(unaff_ESI + 0x10), *(undefined4 *)(unaff_ESI + 0x2cc), &local_50);
    // +0x2D0: projection matrix slot 1
    FUN_0060add0(*(undefined4 *)(unaff_ESI + 0x10), *(undefined4 *)(unaff_ESI + 0x2d0), &local_40);
    
    // Handle additional viewport if present
    iVar19 = *(int *)(unaff_ESI + 0x37c + *(int *)(unaff_ESI + 0x138) * 4);
    if (iVar19 != 0) {
      // +0x14: secondary camera object pointer
      FUN_0060add0(*(undefined4 *)(unaff_ESI + 0x14), iVar19, &local_20);
    }
  }
  return;
}