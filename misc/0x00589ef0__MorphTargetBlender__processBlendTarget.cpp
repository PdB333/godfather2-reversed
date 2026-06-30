// FUNC_NAME: MorphTargetBlender::processBlendTarget
void __thiscall MorphTargetBlender::processBlendTarget(float *outVertices, int startFrame, int endFrame) {
    float scaleFactor = DAT_00e445cc; // Scale to convert 16-bit fixed-point to float (approx 0.000015258789?)

    int currentIndex = *(int *)(this + 0x44); // Current element index
    ushort *compressedData = *(ushort **)(this + 0x38); // Pointer to 16-bit compressed delta data
    float   *baseData      = *(float **)(this + 0x3c);  // Pointer to base float data

    // Advance current index to startFrame, skipping data as needed
    while (currentIndex < startFrame) {
        currentIndex = *(int *)(this + 0x44);
        uint controlTag = __aullshr(); // Read 2-bit control tag (likely from a bitstream)
        if ((controlTag & 3) != 3) {
            // Tag value 0,1,2: skip 2 ushorts of compressed data and 3 floats of base data
            *(int *)(this + 0x38) += 2; // compressedData += 2
        } else {
            // Tag value 3: skip 6 ushorts of compressed data and 3 floats of base data
            *(int *)(this + 0x38) += 6; // compressedData += 6
        }
        *(int *)(this + 0x3c) += 12; // baseData += 3 floats
        currentIndex++;
        *(int *)(this + 0x44) = currentIndex;
    }

    // Now actually decompress and interpolate data from startFrame to endFrame
    while (true) {
        if (endFrame <= currentIndex) return;

        currentIndex = *(int *)(this + 0x44);
        uint controlTag = __aullshr(); // Read 2-bit tag: 1,2,3 indicate which single component is delta-encoded; 0 means all three
        ushort *comp = *(ushort **)(this + 0x38);
        float   *base = *(float **)(this + 0x3c);
        controlTag &= 3;

        switch (controlTag) {
        case 1: // Delta only in X
            outVertices[0] = (float)*comp * scaleFactor + base[0];
            outVertices[1] = base[1];
            outVertices[2] = base[2];
            comp++;
            break;
        case 2: // Delta only in Y
            outVertices[0] = base[0];
            outVertices[1] = (float)*comp * scaleFactor + base[1];
            outVertices[2] = base[2];
            comp++;
            break;
        case 3: // Delta only in Z
            outVertices[0] = base[0];
            outVertices[1] = base[1];
            outVertices[2] = (float)*comp * scaleFactor + base[2];
            comp++;
            break;
        default: // case 0: Delta in all three components
            outVertices[0] = (float)*comp       * scaleFactor + base[0];
            outVertices[1] = (float)comp[1]     * scaleFactor + base[1];
            outVertices[2] = (float)comp[2]     * scaleFactor + base[2];
            comp += 3;
            break;
        }

        // Advance pointers and counters
        *(float **)(this + 0x3c) = base + 3;   // baseData += 3
        *(ushort **)(this + 0x38) = comp;
        currentIndex++;
        outVertices += 3;
        *(int *)(this + 0x44) = currentIndex;
    }
}