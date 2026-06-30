// FUNC_NAME: ConvolutionFilter::process
void __thiscall ConvolutionFilter::process(void)
{
    byte* pixel;               // pbVar1, pbVar2, pbVar3
    byte* srcPixel;            // pbVar6
    byte b;                    // bVar4
    float* kernelElements;     // pfVar5
    float* kernelPtr;          // pfVar8
    int row;                   // iVar10
    float sumR, sumG, sumB, sumA; // local_38, local_34, fStack_30, fStack_2c
    float invRadius;           // local_5c
    int col;                   // iVar9
    int remaining;             // iVar7
    ushort fpwPrev;            // in_FPUControlWord
    float weight;              // fVar11
    float fScale;              // fVar12
    int layerIdx;              // iStack_68
    float radiusResult;        // local_58
    uint kernelSizeAligned;    // local_4c
    undefined4 allocInfo;      // local_3c
    float unused1, unused2;    // local_38, local_34 (overwritten)
    longlong kernelAllocCount; // local_48

    // Compute radius from width/height ratio
    // +0x02: width (short), +0x06: height (short)
    float width = (float)(*(ushort*)((int)this + 0x02));
    float height = (float)(*(ushort*)((int)this + 0x06));
    radiusResult = width / height;

    // Clamp radius to global min (DAT_00e2b1a4)
    if (radiusResult <= MIN_RADIUS) {
        radiusResult = MIN_RADIUS;
    }

    // Multiply by scale factor from array indexed by byte at +0x08
    // +0x08: quality/scale index
    byte scaleIdx = *(byte*)((int)this + 0x08);
    float* scaleTable = (float*)&DAT_00f0ce48; // array of floats
    radiusResult = radiusResult * scaleTable[scaleIdx];

    // Clamp to global max (DAT_00e2cd54)
    if (radiusResult <= MAX_RADIUS) {
        radiusResult = MAX_RADIUS;
    }

    // Set FPU rounding to 24-bit precision (bitmask 0xC00)
    fpwPrev = in_FPUControlWord;
    local_4c = fpwPrev | 0xC00;
    local_3c = 2;                       // allocation size? not used

    // Kernel size = 2*radius + constant (DAT_00e445ac), rounded to integer
    kernelAllocCount = (longlong)ROUND(radiusResult + radiusResult + KERNEL_OFFSET);
    kernelElements = (float*)(**(code**)*DAT_01205868)((int)kernelAllocCount * 4, &local_3c);

    // Inverse radius for normalization
    invRadius = MIN_RADIUS / radiusResult;
    if ( /* some stack value */ fStack_64 <= MAX_RADIUS) {
        invRadius = MIN_RADIUS;
    }

    layerIdx = 0;
    // +0x06: number of layers (short) – outer loop
    short numLayers = *(short*)((int)this + 0x06);
    if (numLayers != 0) {
        do {
            // Generate kernel for this layer (Gaussian?)
            FUN_0061c8f0(layerIdx, radiusResult, *(short*)((int)this + 0x02),
                         invRadius, *(byte*)((int)this + 0x08),
                         &col, &local_50, kernelElements);

            // +0x1A: number of rows per layer (short)
            short numRows = *(short*)((int)this + 0x1A);
            if (numRows != 0) {
                fScale = 0.0f;
                row = 0;
                col = col; // iStack_54 (start column)
                weight = *(float*)&DAT_00e44640; // kernel weight factor

                do {
                    sumR = fScale;
                    sumG = fScale;
                    sumB = fScale;
                    sumA = fScale;

                    if (col < (int)local_50) { // local_50 is kernel width?
                        // +0x00: pixel data base pointer (byte*)
                        // +0x04: row stride (int)
                        int stride = *(int*)((int)this + 0x04);
                        byte* basePtr = *(byte**)((int)this + 0x00);
                        srcPixel = basePtr + stride * row + col * 4;
                        remaining = (int)local_50 - col;
                        kernelPtr = kernelElements;
                        do {
                            b = *srcPixel;                   // R (or B)
                            byte* nextPixel = srcPixel + 4;
                            // Note: kernelElement is weight * weight? Actually fVar11 * fVar11 * pixel?
                            float baseWeight = *kernelPtr * (float)b * weight * weight;
                            float weighted = baseWeight;   // fStack_1c
                            pixel = srcPixel + 1;         // G
                            byte* pixel2 = srcPixel + 2;  // B
                            byte* pixel3 = srcPixel + 3;  // A

                            sumR += baseWeight * (float)b;                     // local_38
                            sumG += baseWeight * (float)*pixel;                // local_34
                            sumB += baseWeight * (float)*pixel2;               // fStack_30
                            sumA += baseWeight * (float)*pixel3;               // fStack_2c

                            srcPixel = nextPixel;
                            kernelPtr++;
                            remaining--;
                        } while (remaining != 0);
                    }
                    // Apply accumulated result to pixel (call to write)
                    FUN_0061cb30();
                    row++;
                } while (row < (int)(uint)numRows);
            }
            layerIdx++;
        } while (layerIdx < (int)(uint)numLayers);
    }

    // Free kernel memory (second call of vtable at DAT_01205868)
    (**(code**)(*DAT_01205868 + 4))(kernelElements, 0);
    return;
}