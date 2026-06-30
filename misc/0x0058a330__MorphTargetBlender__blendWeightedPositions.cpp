// FUNC_NAME: MorphTargetBlender::blendWeightedPositions
// This function blends compressed ushort delta data with base float positions to produce output positions.
// It processes a range of vertex indices [startIndex, endIndex), using a pseudo-random component selection
// to apply only some deltas (likely for performance or stochastic interpolation).
// The compressed data is stored as ushort deltas (scale factor DAT_00e445cc) and the base as float triplets.
// The output buffer is assumed to be pre-allocated.
// Structure offsets:
//   +0x58 (ushort*) - pointer to compressed delta data (indices advance variably)
//   +0x5c (float*)  - pointer to base position data (always advances by 12 bytes per element)
//   +0x64 (int)     - current element index (tracker for internal state)

void FUN_0058a330(int startIndex, int endIndex)  // Note: third parameter (float* outPos) is passed via EAX in original
{
    float* outPos;  // Implicitly provided via EAX in original assembly
    float scaleFactor = DAT_00e445cc;  // Global conversion factor for ushort to float
    uint rngVal;

    // --- Advance internal pointers to startIndex ---
    int currentIndex = *(int*)(this + 0x64);  // +0x64
    while (currentIndex < startIndex) {
        currentIndex = *(int*)(this + 0x64);
        rngVal = __aullshr() & 3;  // Pseudo-random value (likely from timer or hash)
        if ((rngVal - 1) < 3) {    // rngVal != 0 → compressed data uses 2 ushorts per vertex
            *(ushort**)(this + 0x58) = *(ushort**)(this + 0x58) + 2;
        } else {                   // rngVal == 0 → compressed data uses 6 ushorts per vertex
            *(ushort**)(this + 0x58) = *(ushort**)(this + 0x58) + 6;
        }
        *(float**)(this + 0x5c) = *(float**)(this + 0x5c) + 3;  // Always advance by 3 floats (12 bytes)
        currentIndex = currentIndex + 1;
        *(int*)(this + 0x64) = currentIndex;
    }

    // --- Process range [startIndex, endIndex) ---
    ushort* pCompressed = *(ushort**)(this + 0x58);
    float* pBase = *(float**)(this + 0x5c);
    currentIndex = *(int*)(this + 0x64);
    while (currentIndex < endIndex) {
        rngVal = __aullshr() & 3;  // Which component(s) to blend?
        switch (rngVal) {
            case 1:  // Blend only Y component
                outPos[0] = pBase[0];
                outPos[1] = (float)pCompressed[0] * scaleFactor + pBase[1];
                outPos[2] = pBase[2];
                pCompressed += 1;
                break;
            case 2:  // Blend only Z component
                outPos[0] = pBase[0];
                outPos[1] = pBase[1];
                outPos[2] = (float)pCompressed[0] * scaleFactor + pBase[2];
                pCompressed += 1;
                break;
            case 3:  // Blend all three components (with three deltas)
                outPos[0] = (float)pCompressed[0] * scaleFactor + pBase[0];
                outPos[1] = (float)pCompressed[1] * scaleFactor + pBase[1];
                outPos[2] = (float)pCompressed[2] * scaleFactor + pBase[2];
                pCompressed += 3;
                break;
            default:  // rngVal == 0: Blend only X component
                outPos[0] = (float)pCompressed[0] * scaleFactor + pBase[0];
                outPos[1] = pBase[1];
                outPos[2] = pBase[2];
                pCompressed += 1;
                break;
        }
        pBase += 3;  // Always advance base by 3 floats
        outPos += 3; // Advance output pointer
        currentIndex++;
        // Update internal pointers after processing each vertex
        *(ushort**)(this + 0x58) = pCompressed;
        *(float**)(this + 0x5c) = pBase;
        *(int*)(this + 0x64) = currentIndex;
    }
}