// FUNC_NAME: AnimationCurve::evaluate
void __thiscall AnimationCurve::evaluate(int curveIndex, int interpType, float time, float* outValues)
{
    // +0x00: m_keyData (pointer to packed keyframe data array)
    float* keyData = *(float**)this;
    // Constants from global memory (likely configurable step sizes and scales)
    const float delta = *(float*)0x00e2b1a4;    // small time step for derivative estimation
    const float scale = *(float*)0x00e445d0;    // scaling factor for cubic spline interpolation
    // Precomputed spline basis function lookup table (256 entries)
    extern float splineBasisTable[256];         // DAT_00e2c320

    switch (interpType)
    {
    case 1: // Linear interpolation
    {
        float val = linearInterp(time);
        outValues[0] = val;
        float val2 = linearInterp(time + delta);
        outValues[1] = val2;
        return;
    }
    case 2: // Ease‑in interpolation
    {
        float val = easeInInterp();
        outValues[0] = val;
        float val2 = easeInInterp();
        outValues[1] = val2;
        return;
    }
    case 3: // Ease‑out interpolation
    {
        float val = easeOutInterp();
        outValues[0] = val;
        float val2 = easeOutInterp();
        outValues[1] = val2;
        return;
    }
    case 4: // Raw keyframe data (Bézier control points)
    {
        // Each keyframe stores two 4‑byte floats packed in a 8‑byte block.
        // The base pointer keyData is treated as a byte array; offsets are relative to curveIndex*4.
        uint8_t* byteData = (uint8_t*)keyData;
        // First float at offset 2 + curveIndex*4
        outValues[0] = *(float*)(byteData + 2 + curveIndex * 4);
        // Second float at offset 6 + curveIndex*4
        outValues[1] = *(float*)(byteData + 6 + curveIndex * 4);
        return;
    }
    case 6: // Cubic spline (simpler variant)
    case 7: // Cubic spline (with extra weighting)
    {
        uint8_t* byteData = (uint8_t*)keyData;
        // Read two 3‑byte values (little‑endian) from positions 2 and 5,
        // shift left by 8 bits to form a full integer (interpreted as float)
        uint32_t valA = *(uint32_t*)(byteData + 2) & 0xFFFFFF;
        uint32_t valB = *(uint32_t*)(byteData + 5) & 0xFFFFFF;
        float fVar2 = (float)(valA << 8);
        float fVar3 = (float)(valB << 8);

        if (interpType == 6)
        {
            uint8_t idx1 = byteData[8 + curveIndex];
            uint8_t idx2 = byteData[9 + curveIndex];
            float basis1 = splineBasisTable[idx1];
            float basis2 = splineBasisTable[idx2];
            outValues[0] = basis1 * fVar3 + fVar2;
            outValues[1] = basis2 * fVar3 + fVar2;
        }
        else // interpType == 7
        {
            uint8_t idxA = byteData[9 + curveIndex * 2];
            uint8_t idxB = byteData[8 + curveIndex * 2];
            uint8_t idxC = byteData[11 + curveIndex * 2];
            uint8_t idxD = byteData[10 + curveIndex * 2];
            float basisA = splineBasisTable[idxA];
            float basisB = splineBasisTable[idxB];
            float basisC = splineBasisTable[idxC];
            float basisD = splineBasisTable[idxD];
            outValues[0] = (basisA * scale + basisB) * fVar3 + fVar2;
            outValues[1] = (basisC * scale + basisD) * fVar3 + fVar2;
        }
        return;
    }
    default:
        return;
    }
}