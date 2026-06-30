// FUNC_NAME: TransformBlender::blendMatrices
void TransformBlender::blendMatrices(float *inMatrix, float *inMatrix2, float *blendVector, float *outMatrix, byte flags)
{
    float fVar1, fVar2, fVar10, fVar11, fVar12, fVar13;
    float scaleFactorIn104;  // from this+0x104
    float globalScale;       // from this+0x108
    float *pfVar6;
    int iVar7;

    // Constants
    const float c_identityW = DAT_00e2b1a4;  // likely 1.0f
    const float c_epsilon = DAT_00e2cbe0;    // small epsilon

    // Check if output matrix is identity (or special flag)
    if (*outMatrix == c_identityW)
    {
        // Blend between inMatrix2 and inMatrix3 based on flags
        if ((flags & 0xC) == 0xC)
        {
            // Use blendVector as source
            FUN_0056cef0(blendVector);  // "decompose" or "normalize" ?
            // Copy 4 floats from the result to outMatrix+0x30
            *(undefined4 *)(outMatrix + 0x30 / 4) = *(undefined4 *)(extraout_ECX + 0x10);
            *(undefined4 *)(outMatrix + 0x34 / 4) = *(undefined4 *)(extraout_ECX + 0x14);
            *(undefined4 *)(outMatrix + 0x38 / 4) = *(undefined4 *)(extraout_ECX + 0x18);
            *(undefined4 *)(outMatrix + 0x3c / 4) = *(undefined4 *)(extraout_ECX + 0x1c);
            // Overwrite last float with identityW
            outMatrix[0x3c / 4] = c_identityW;
        }
        else
        {
            // Use inMatrix2 as source
            FUN_0056cef0(inMatrix2);
            *(undefined4 *)(outMatrix + 0x30 / 4) = *(undefined4 *)(extraout_EDX + 0x10);
            *(undefined4 *)(outMatrix + 0x34 / 4) = *(undefined4 *)(extraout_EDX + 0x14);
            *(undefined4 *)(outMatrix + 0x38 / 4) = *(undefined4 *)(extraout_EDX + 0x18);
            *(undefined4 *)(outMatrix + 0x3c / 4) = *(undefined4 *)(extraout_EDX + 0x1c);
            outMatrix[0x3c / 4] = c_identityW;

            if ((flags & 4) == 0)
            {
                if ((flags & 8) != 0)
                {
                    FUN_00414aa0();  // some reset function
                }
            }
            else
            {
                // Blend using blendVector as well
                FUN_0056cef0(blendVector);
                *extraout_ECX_00 = 0;
                extraout_ECX_00[1] = 0;
                extraout_ECX_00[2] = 0;
                extraout_ECX_00[3] = c_identityW;  // quaternion with w=1, others 0
            }
        }

        // Scale the first three rows of the output matrix by factor from this+0x104
        pfVar6 = (float *)(outMatrix + 8);
        iVar7 = 3;
        do
        {
            pfVar6[-2] = pfVar6[-2] * *(float *)(this + 0x104);
            pfVar6[-1] = *(float *)(this + 0x104) * pfVar6[-1];
            *pfVar6 = *pfVar6 * *(float *)(this + 0x104);
            pfVar6 = pfVar6 + 4;
            iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
        return;
    }

    // General blend path: scale inMatrix by globalScale (this+0x108)
    float local_90[4], local_80[4], local_70[4], local_60[4];
    float local_50[4], local_40[4], local_30[4], local_20[4];
    float local_b0[4]; // for transformed blend vector
    float fStack_a8[4]; // temporary

    globalScale = *(float *)(this + 0x108);

    // Copy and scale inMatrix into local variables (16 floats)
    local_90[0] = globalScale * inMatrix[0];
    local_90[1] = globalScale * inMatrix[1];
    local_90[2] = globalScale * inMatrix[2];
    local_90[3] = globalScale * inMatrix[3];

    local_80[0] = globalScale * inMatrix[4];
    local_80[1] = globalScale * inMatrix[5];
    local_80[2] = globalScale * inMatrix[6];
    local_80[3] = globalScale * inMatrix[7];

    local_70[0] = globalScale * inMatrix[8];
    local_70[1] = globalScale * inMatrix[9];
    local_70[2] = globalScale * inMatrix[10];
    local_70[3] = globalScale * inMatrix[11];

    local_60[0] = globalScale * inMatrix[12];
    local_60[1] = globalScale * inMatrix[13];
    local_60[2] = globalScale * inMatrix[14]; // note: param_1[14]
    local_60[3] = c_identityW;  // set to 1.0

    // Compute something from the scaled matrix (maybe transpose or inverse)
    FUN_0056c640(&local_90, &local_50);  // result in local_50...?

    // Compute dot product of blendVector with itself
    fVar10 = blendVector[1];
    fVar11 = blendVector[2];
    fVar12 = blendVector[0];
    fVar8 = fVar11 * fVar11 + fVar10 * fVar10 + fVar12 * fVar12;

    if (fVar8 <= c_epsilon)
    {
        fVar8 = 0.0f;
    }
    else
    {
        fVar8 = c_identityW / SQRT(fVar8);
    }

    // Normalize blendVector components
    fVar10 = fVar10 * fVar8;
    fVar12 = fVar8 * fVar12;
    fVar11 = fVar11 * fVar8;

    // Compute transformed blend direction (dot products with some matrix rows)
    local_b0[0] = fVar10 * local_40[0] + fVar12 * local_50[0] + fVar11 * local_30[0];
    local_b0[1] = fVar10 * local_40[1] + fVar12 * local_50[1] + fVar11 * local_30[1];
    local_b0[2] = fVar10 * local_40[2] + fVar12 * local_50[2] + fVar11 * local_30[2];
    local_b0[3] = fVar10 * local_40[3] + fVar12 * local_50[3] + fVar11 * local_30[3];

    // static cache initialization
    if ((g_cacheFlags & 1) == 0)
    {
        g_cacheFlags |= 1;
        g_cacheVector0[0] = 0.0f;
        g_cacheVector0[1] = 0.0f;
        g_cacheVector0[2] = 0.0f;
        g_cacheVector1[0] = c_identityW;
        g_cacheVector1[1] = c_identityW;
        g_cacheVector1[2] = c_identityW;
        g_cacheVector1[3] = c_identityW;
        g_cachePosition = c_identityW;
    }

    if ((flags & 8) != 0)
    {
        // Use blendVector's quaternion/spin part to compute cache
        g_cachePosition = blendVector[5] * local_40[3] + blendVector[4] * local_50[3] + blendVector[6] * local_30[3] + blendVector[7] * local_40[3];
        g_cacheVector1[0] = *(float *)(this + 0x108);  // scale
        g_cacheVector1[1] = g_cacheVector1[0] * (blendVector[5] * local_40[0] + blendVector[4] * local_50[0] + blendVector[6] * local_30[0] + blendVector[7] * local_20[0]);
        g_cacheVector1[2] = g_cacheVector1[0] * (blendVector[5] * local_40[1] + blendVector[4] * local_50[1] + blendVector[6] * local_30[1] + blendVector[7] * local_20[1]);
        g_cacheVector1[3] = g_cacheVector1[0] * (blendVector[5] * local_40[2] + blendVector[4] * local_50[2] + blendVector[6] * local_30[2] + blendVector[7] * local_20[2]);
        // Note: indices for blendVector might be offset; probably 4..7 correspond to another vector
    }

    // Update locals for output
    local_a0[0] = local_b0[0];
    local_a0[1] = local_b0[1];
    local_a0[2] = local_b0[2];

    if ((flags & 4) != 0)
    {
        // Scale the transformed vector by an angle factor
        double angle = (double)blendVector[3];
        FUN_00b9b988();  // possibly sin/cos? but not used directly
        float scale = (float)angle * DAT_00e2b04c;  // some conversion constant (radians?)
        local_b0[0] = scale * local_b0[0];
        local_b0[1] = scale * local_b0[1];
        local_b0[2] = scale * local_b0[2];
        FUN_0056d1f0(&local_b0, &g_cacheVector0);  // probably adds to cache
        // Overwrite with result? The code then sets local_b0, local_ac, local_a8 again
    }

    // Call final processing
    FUN_00574760();

    return;
}