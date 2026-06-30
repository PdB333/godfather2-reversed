// FUNC_NAME: ColorBufferProcessor::applyScale
// Function address: 0x0053ab80
// Applies a per-component scale to an array of 4-component (RGBA) color values.
// Scales the first three components (R,G,B) by the corresponding factors in param_4,
// while preserving the original alpha (fourth component) after conversion via packFloatToByte.

int __thiscall ColorBufferProcessor::applyScale(int *this, int destBuffer, int count, float *scaleFactors)
{
    float *srcData;
    float *dstData;
    float r, g, b, a;
    float scaleR, scaleG, scaleB, scaleA;
    int i;

    // Virtual call to get source data pointer (vtable+0xc)
    srcData = (float *)(*(code **)(*this + 0xc))();
    if (srcData == 0) {
        return 0;
    }

    if (0 < count) {
        dstData = (float *)(destBuffer + 0xc); // +0xc offset for destination start
        srcData = (float *)((int)srcData + 0x10); // +0x10 offset for source start

        do {
            // Read source components (RGBA) from current source block
            r = *(srcData - 4); // offset -0x10
            g = *(srcData - 3); // offset -0xc
            b = *(srcData - 2); // offset -8
            a = *(srcData - 1); // offset -4

            // Scale factors
            scaleR = scaleFactors[0];
            scaleG = scaleFactors[1];
            scaleB = scaleFactors[2];
            scaleA = scaleFactors[3];

            // Write scaled R,G,B to destination (preserve original alpha for now)
            *(dstData - 3) = r * scaleR; // offset -0xc
            *(dstData - 2) = g * scaleG; // offset -8
            *(dstData - 1) = b * scaleB; // offset -4
            *dstData = a * scaleA;        // offset 0 (temporary)

            // Convert the scaled alpha via packFloatToByte and overwrite with original alpha
            *dstData = a; // restore original alpha (fourth component unchanged)
            packFloatToByte(); // returns pointer to packed byte data in EDX
            // Copy 4 bytes from the packed result into the destination alpha slot
            *(unsigned char *)((int)dstData + 3) = *(unsigned char *)(extraout_EDX - 1);
            *(unsigned short *)dstData = *(unsigned short *)(extraout_EDX - 4);
            *(unsigned char *)((int)dstData + 2) = *(unsigned char *)(extraout_EDX - 2);

            // Advance to next block (stride 0x20 for source, 0x20 for destination)
            srcData = (float *)((int)srcData + 0x20);
            dstData += 8; // 8 floats = 0x20 bytes
            count--;
        } while (count != 0);
    }
    return 1;
}