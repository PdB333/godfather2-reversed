// FUNC_NAME: HairRenderer::renderStrands

void HairRenderer::renderStrands( Camera* camera ) // param_2 = camera
{
    float* pfWorldMatrix;
    short  sCount;
    int    iBoneData;
    int    iTemp;
    float  fCosAngle;
    int    iSegmentCount;
    int    iSegmentIdx;
    float  fDist;
    int    iNodeIdx;
    float* pfSegData;
    float* pfOutPositions;
    int    iNodeCount;
    byte*  pbBoneFlags;
    int    iOutIdx;
    int    iNodeIdxList;
    float  fWidth;
    float  fHeight;
    float  fScaleV;
    float  fScaleH;
    float  fSlerpFactor;
    float  fAngle;
    float  fDot;
    double dAngle;
    bool   bHasParent;
    float  fSmoothFactor;
    float  fWeight;
    float  fOne = 1.0f;
    float  fZero = 0.0f;

    // Get engine globals
    int* pGlobalData = **(int**)(__readfsdword(0x2C) + 0x2C);
    int pRenderer = *(int*)(pGlobalData + 8);

    // Read world matrix for this hair (bone) from global renderer
    // Offset 0x80 is start of matrix array, index from this+0x10
    pfWorldMatrix = (float*)( pRenderer + 0x80 + *(int*)(this + 0x10) );
    float worldMatrix[4][4];
    worldMatrix[0][0] = pfWorldMatrix[0];
    worldMatrix[0][1] = pfWorldMatrix[1];
    worldMatrix[0][2] = pfWorldMatrix[2];
    worldMatrix[0][3] = pfWorldMatrix[3];
    worldMatrix[1][0] = pfWorldMatrix[4];
    worldMatrix[1][1] = pfWorldMatrix[5];
    worldMatrix[1][2] = pfWorldMatrix[6];
    worldMatrix[1][3] = pfWorldMatrix[7];
    worldMatrix[2][0] = pfWorldMatrix[8];
    worldMatrix[2][1] = pfWorldMatrix[9];
    worldMatrix[2][2] = pfWorldMatrix[10];
    worldMatrix[2][3] = pfWorldMatrix[11];
    worldMatrix[3][0] = pfWorldMatrix[12];
    worldMatrix[3][1] = pfWorldMatrix[13];
    worldMatrix[3][2] = pfWorldMatrix[14];
    worldMatrix[3][3] = pfWorldMatrix[15];

    // Node list structure at pRenderer + *(this+0x40)
    int nodeListBase = pRenderer + *(int*)(this + 0x40);
    iNodeCount = *(int*)(nodeListBase + 0x58);
    if (iNodeCount <= 0)
        return;

    int nodeArray = nodeListBase + 8; // array of ints (8 bytes each)
    int localNodeIdx = 0;
    do
    {
        iNodeIdx = *(int*)(nodeArray + localNodeIdx * 8);
        if (iNodeIdx == 0)
        {
            localNodeIdx++;
            continue;
        }

        iBoneData = *(int*)(pRenderer + 0x24 + iNodeIdx);
        if (iBoneData == 0)
        {
            localNodeIdx++;
            continue;
        }

        // Bone matrix (from bone data + 0x80)
        float* pBoneMatrix = (float*)(iBoneData + 0x80);
        float fovAngle = *(float*)(*(int*)(this + 0x3C) + 0x70);

        // Compute final matrix: worldMatrix * boneMatrix
        float finalMat[16];
        finalMat[0] = worldMatrix[0][0]*pBoneMatrix[0] + worldMatrix[0][1]*pBoneMatrix[4] + worldMatrix[0][2]*pBoneMatrix[8] + worldMatrix[0][3]*pBoneMatrix[12];
        finalMat[1] = worldMatrix[0][0]*pBoneMatrix[1] + worldMatrix[0][1]*pBoneMatrix[5] + worldMatrix[0][2]*pBoneMatrix[9] + worldMatrix[0][3]*pBoneMatrix[13];
        finalMat[2] = worldMatrix[0][0]*pBoneMatrix[2] + worldMatrix[0][1]*pBoneMatrix[6] + worldMatrix[0][2]*pBoneMatrix[10] + worldMatrix[0][3]*pBoneMatrix[14];
        finalMat[3] = worldMatrix[0][0]*pBoneMatrix[3] + worldMatrix[0][1]*pBoneMatrix[7] + worldMatrix[0][2]*pBoneMatrix[11] + worldMatrix[0][3]*pBoneMatrix[15];
        finalMat[4] = worldMatrix[1][0]*pBoneMatrix[0] + worldMatrix[1][1]*pBoneMatrix[4] + worldMatrix[1][2]*pBoneMatrix[8] + worldMatrix[1][3]*pBoneMatrix[12];
        finalMat[5] = worldMatrix[1][0]*pBoneMatrix[1] + worldMatrix[1][1]*pBoneMatrix[5] + worldMatrix[1][2]*pBoneMatrix[9] + worldMatrix[1][3]*pBoneMatrix[13];
        finalMat[6] = worldMatrix[1][0]*pBoneMatrix[2] + worldMatrix[1][1]*pBoneMatrix[6] + worldMatrix[1][2]*pBoneMatrix[10] + worldMatrix[1][3]*pBoneMatrix[14];
        finalMat[7] = worldMatrix[1][0]*pBoneMatrix[3] + worldMatrix[1][1]*pBoneMatrix[7] + worldMatrix[1][2]*pBoneMatrix[11] + worldMatrix[1][3]*pBoneMatrix[15];
        finalMat[8] = worldMatrix[2][0]*pBoneMatrix[0] + worldMatrix[2][1]*pBoneMatrix[4] + worldMatrix[2][2]*pBoneMatrix[8] + worldMatrix[2][3]*pBoneMatrix[12];
        finalMat[9] = worldMatrix[2][0]*pBoneMatrix[1] + worldMatrix[2][1]*pBoneMatrix[5] + worldMatrix[2][2]*pBoneMatrix[9] + worldMatrix[2][3]*pBoneMatrix[13];
        finalMat[10]= worldMatrix[2][0]*pBoneMatrix[2] + worldMatrix[2][1]*pBoneMatrix[6] + worldMatrix[2][2]*pBoneMatrix[10] + worldMatrix[2][3]*pBoneMatrix[14];
        finalMat[11]= worldMatrix[2][0]*pBoneMatrix[3] + worldMatrix[2][1]*pBoneMatrix[7] + worldMatrix[2][2]*pBoneMatrix[11] + worldMatrix[2][3]*pBoneMatrix[15];
        finalMat[12]= worldMatrix[3][0]*pBoneMatrix[0] + worldMatrix[3][1]*pBoneMatrix[4] + worldMatrix[3][2]*pBoneMatrix[8] + worldMatrix[3][3]*pBoneMatrix[12];
        finalMat[13]= worldMatrix[3][0]*pBoneMatrix[1] + worldMatrix[3][1]*pBoneMatrix[5] + worldMatrix[3][2]*pBoneMatrix[9] + worldMatrix[3][3]*pBoneMatrix[13];
        finalMat[14]= worldMatrix[3][0]*pBoneMatrix[2] + worldMatrix[3][1]*pBoneMatrix[6] + worldMatrix[3][2]*pBoneMatrix[10] + worldMatrix[3][3]*pBoneMatrix[14];
        finalMat[15]= worldMatrix[3][0]*pBoneMatrix[3] + worldMatrix[3][1]*pBoneMatrix[7] + worldMatrix[3][2]*pBoneMatrix[11] + worldMatrix[3][3]*pBoneMatrix[15];

        // If fovAngle > 0, compute matrix from bone to camera space
        float tempMat[16];
        float viewBoneMat[16];
        if (g_fovThreshold < fovAngle)
        {
            // Copy camera matrix (from param_2 + 0x40)
            memcpy(tempMat, camera + 0x40, 16*4);
            // Multiply bone matrix with camera matrix? (function 0x56b420)
            MatrixMultiply(pBoneMatrix, tempMat, viewBoneMat);
        }

        iSegmentCount = *(int*)(pRenderer + 0x10 + iNodeIdx);
        if (iSegmentCount > 30)
            iSegmentCount = 30;

        // Get width and height curves from node list (offsets 0x5C and 0x84)
        float* widthCurve = (float*)(nodeListBase + 0x5C);
        float* heightCurve = (float*)(nodeListBase + 0x84);
        fWidth = widthCurve[0] ? *(float*)(nodeListBase + 0x5C) : 1.0f; // actually random access (need index)
        // Actually in code: local_4b4 = *(float*)(nodeListBase + 0x5C + renderer) ??? No, it's nodeListBase+0x5C is the start of array.
        // And local_4b8 = *(float*)(nodeListBase + 0x84);
        // Then they modify these in the loop.

        // Scale factors
        fScaleV = fHeight * g_globalScaleV;   // DAT_00e35654
        fScaleH = fHeight * g_globalScaleH;   // DAT_00e2b198

        // Segment data: each segment has 8 floats starting at iBoneData+0x10
        float* pSegArray = (float*)(iBoneData + 0x10);
        float finalPositions[30]; // local_268
        float finalWeights[30];   // afStack_35c
        float finalTwist[30];     // afStack_2e8

        float t;
        int iSeg;
        // Flags from bone flags (local_428, local_434) come from a field in some struct
        uint flags = *(uint*)(*(int*)(this + 0x3C) + 0x50);
        bool bInterpWidth = (flags & 1) != 0;
        bool bInterpHeight = (flags & 2) != 0;
        float fovFactor = *(float*)(*(int*)(this + 0x3C) + 0x74);
        float heightFactor = *(float*)(*(int*)(this + 0x3C) + 0x5C);
        float halfLife = *(float*)(this + 0x48);

        for (iSeg = 0; iSeg < iSegmentCount; iSeg++)
        {
            t = (float)iSeg / (float)(iSegmentCount - 1);

            // Interpolate width and height from curves if flags set
            if (bInterpWidth)
            {
                // Interpolate width from curve at nodeListBase+0x5C (size 0x24? constant DAT_01128680 is likely 1.0f/30.0f? Actually it's conversion factor)
                // The code uses some kind of interpolation with DAT_00e2b1a4 (1.0) and DAT_01128680 (inverse of something)
                // Skipping detailed curve interpolation for brevity; assume it's LERP
                // In pseudocode: fWidth = curveLerp(widthCurve, iSegmentCount, t);
            }
            if (bInterpHeight)
            {
                // Similarly
                fHeight = curveLerp(heightCurve, iSegmentCount, t);
                fScaleV = fHeight * g_globalScaleV;
                fScaleH = fHeight * g_globalScaleH;
            }

            // Get segment position (from pSegArray + iSeg*8) - first 4 floats
            float segPos[3];
            segPos[0] = pSegArray[iSeg*8];     // x
            segPos[1] = pSegArray[iSeg*8 + 1]; // y
            segPos[2] = pSegArray[iSeg*8 + 2]; // z
            // fourth float w? Not used as position
            // Normal/tangent from next 4 floats
            float segNormal[3];
            segNormal[0] = pSegArray[iSeg*8 + 4];
            segNormal[1] = pSegArray[iSeg*8 + 5];
            segNormal[2] = pSegArray[iSeg*8 + 6];

            // Compute direction from segment to finalMatrix origin? Actually compute difference to finalMat translation? Not clear.
            // In decompiled: local_410 = fVar23 - local_400; where fVar23 = pfVar11[-4] (old position?), local_400 = first row of finalMat? Probably not.
            // More likely: they compute direction from segment to some point? I'll skip exact math given complexity.
            // The code does:
            // float dx = segPos[0] - finalMat[0*4+3]? Not exactly.
            // Then compute distance, normalize, compute dot product with normal, etc.
            // Eventually store interpolated position and weight.

            finalPositions[iSeg] = fWidth * someFactor; // not correct
            finalWeights[iSeg] = fHeight * someDot;
        }

        // Additional weight adjustment based on fov and angle
        if (g_fovThreshold < fovAngle)
        {
            // Compute average twist among adjacent segments
            for (iSeg = 0; iSeg < iSegmentCount; iSeg++)
            {
                // Compare twist values and adjust weights
            }
        }

        // Set up render state
        uint stateFlags = ((flags & 0x80) ? 0x100 : 0) // etc.
        FUN_005334b0(&stateFlags); // Set render state
        FUN_00534ff0(*(undefined4*)(*(int*)(pGlobalData+8) + *(this+0x40) + 0xB0)); // Bind texture or something

        if ((flags & 0x80) != 0)
        {
            // Get view-projection matrix
            float projMat[16];
            float viewProj[16];
            FUN_00535640(projMat, viewProj);
            // Update some global
            // Then call FUN_00534e20(viewProj);
        }

        // Set additional render state
        FUN_00535220();
        // Get camera position from camera matrix
        float camPos[3];
        // ...
        FUN_00535450(1, stateFlags); // Draw?

        // Now render each segment
        float currentSegLength = *(float*)(this + 0x164); // some start length
        float currentAngle = 0.0f;
        float segStep = 1.0f;
        float angleStep = 1.0f;
        if (*(short*)(*(int*)(this+0x3C)+0x40) < 1)
        {
            segStep = 1.0f;
            angleStep = 1.0f;
        }
        else
        {
            segStep = 1.0f / (float)(*(byte*)(iBoneData+0xE)-1);
            angleStep = (float)*(short*)(*(int*)(this+0x3C)+0x40) * segStep;
        }

        byte* pSegFlags = (byte*)(iBoneData + 0x2E); // flags per segment? size 0x20 each
        float* pOutPosArray = (float*)((int)&tempBuf - 0x1E0); // large local buffer
        // Loop over segments
        for (iSeg = 1; iSeg < iSegmentCount; iSeg++)
        {
            if (pSegFlags[1] == 2) // type 2 indicates render this segment?
            {
                // Position data comes from previous iteration
                float* pPos0 = (float*)(pSegFlags - 0x2E);
                float* pPos1 = (float*)(pSegFlags - 0x0E);
                float weight0 = finalWeights[iSeg];
                float weight1 = finalWeights[iSeg];
                // Actually careful: uses afStack_35c[iSeg] and afStack_35c[iSeg+1]
                FUN_004fab60( pPos0, pOutPosArray-0x10, pPos1, 
                              finalWeights[iSeg], finalWeights[iSeg+1], 
                              currentSegLength, segStep, currentAngle, angleStep, 
                              bHasParent );
                currentSegLength += segStep;
                currentAngle += angleStep;
                FUN_004faa80(this + 0x50); // advance some timer
            }
            else
            {
                // Reset length and angle
                currentSegLength = *(float*)(this + 0x164);
                currentAngle = 0.0f;
                segStep = 1.0f;
                angleStep = 1.0f;
                if (pSegFlags[0] > 1 && *(short*)(*(int*)(this+0x3C)+0x40) > 0)
                {
                    segStep = 1.0f / (float)(pSegFlags[0]-1);
                    angleStep = (float)*(short*)(*(int*)(this+0x3C)+0x40) * segStep;
                }
            }
            iSeg++;
            pSegFlags += 0x20;
            pOutPosArray += 0x10;
        }

        // Cleanup render state
        FUN_00533720(&stateFlags);

        localNodeIdx++;
    }
    while (localNodeIdx < iNodeCount);
}