// FUNC_NAME: Animated::scaleAddMatrices
void __thiscall Animated::scaleAddMatrices(int this, int src, float alpha)
{
    // this +0x50, +0x90, +0xD0 are three 4x4 matrices (each 16 floats)
    // Add scaled source matrices to destination: dst[i] = src[i] * alpha + dst[i]
    float* dstRow = (float*)(this + 0x50);  // offset to first matrix
    float* srcRow = (float*)(src + 0x50);   // offset to first matrix in source
    int rows = 4;
    do {
        // Process first matrix row (at +0x50 relative to base)
        float* srcPtr = (float*)((src - this) + (int)dstRow);  // computes srcRow + rowOffset
        float v0 = srcPtr[1];
        float v1 = srcPtr[2];
        float v2 = srcPtr[3];
        dstRow[0] = srcPtr[0] * alpha + dstRow[0];
        dstRow[1] = v0 * alpha + dstRow[1];
        dstRow[2] = v1 * alpha + dstRow[2];
        dstRow[3] = v2 * alpha + dstRow[3];

        // Process second matrix row (at +0x90 relative to base)
        float* srcRow2 = (float*)(src + 0x90);  // reused later; actually we use offsets from a moving pointer
        // The original code uses pfVar7 which starts at src + 0xD0 and is incremented
        // We'll replicate the exact behavior:
        // For second matrix: source at (src + 0x90 + row*16), destination at (this + 0x90 + row*16)
        // pdVar7[-0x10] gives (src + 0x90 + row*16) because pfVar7 was advanced from src+0xD0
        // But to mirror the original, we do pointer arithmetic as written.
        // However, for clarity we can index directly.
        // I'll keep the original pointer manipulation to stay faithful.
        // Let me restructure: this function matches the decompiled exactly.
    } while (rows--);
}
// The above is a template; actual code should reflect the decompiled structure precisely. Let's rewrite cleanly.

// Reconstructed from decompiled assembly, maintaining the exact pointer arithmetic.

// Assume this and src are pointers to objects of the same type with three 4x4 matrices at offsets 0x50, 0x90, 0xD0.
void __thiscall Animated::scaleAddMatrices(int this, int src, float alpha)
{
    float* dstBase = (float*)(this + 0x50);
    float* srcBase = (float*)(src + 0x50);
    float* srcMatrices = (float*)(src + 0xD0); // points to third matrix start
    int row = 4;
    do {
        // Compute pointer to same row in source for the first matrix
        float* srcRow = (float*)((src - this) + (int)dstBase);
        float a1 = srcRow[0];
        float a2 = srcRow[1];
        float a3 = srcRow[2];
        float a4 = srcRow[3];
        dstBase[0] = a1 * alpha + dstBase[0];
        dstBase[1] = a2 * alpha + dstBase[1];
        dstBase[2] = a3 * alpha + dstBase[2];
        dstBase[3] = a4 * alpha + dstBase[3];

        // Second matrix row: source is at srcMatrices[-0x10] (i.e., src+0x90) + rowOffset
        float* srcRow2 = (float*)((char*)srcMatrices - 0x40); // +0x90 base
        float b1 = srcRow2[1];
        float b2 = srcRow2[2];
        float b3 = srcRow2[3];
        dstBase[0x10] = srcRow2[0] * alpha + dstBase[0x10];
        dstBase[0x11] = b1 * alpha + dstBase[0x11];
        dstBase[0x12] = b2 * alpha + dstBase[0x12];
        dstBase[0x13] = b3 * alpha + dstBase[0x13];

        // Third matrix row: source is at srcMatrices (src+0xD0) + rowOffset
        float c1 = srcMatrices[1];
        float c2 = srcMatrices[2];
        float c3 = srcMatrices[3];
        dstBase[0x20] = srcMatrices[0] * alpha + dstBase[0x20];
        dstBase[0x21] = c1 * alpha + dstBase[0x21];
        dstBase[0x22] = c2 * alpha + dstBase[0x22];
        dstBase[0x23] = c3 * alpha + dstBase[0x23];

        // Advance to next row (4 floats)
        dstBase += 4;
        srcMatrices += 4;
        row--;
    } while (row != 0);
}