// FUNC_NAME: TransformBlendNode::accumulateBlend
// Function at 0x004efb20 - Accumulates blended transformation data over 3 frames using weighted sum with global coefficients.
// The input is stored at offset 0x10 (8 uint32 values representing a transformation) and is blended using three global float coefficients.
// After 3 frames of accumulation, the blended result is written to a target node at offset 0x34 (or retrieved via FUN_00426a90 if null).
// Additionally, if the target node exists and has a matrix pointer at +0x90, a 4x4 matrix from the source node (at +0x30) is copied to that pointer.

class TransformBlendNode {
    // Offsets relative to "this" (param_1):
    // +0x10: uint32 inputVec[8]; // 8 dwords forming transformation data (e.g., quaternion + translation pairs)
    // +0x30: source matrix (16 floats) - used for copy
    // +0x34: int32 targetPtr; // pointer to target node (or 0)
    // +0x38: uint32 frameCounter; // counts frames up to 3
    // Target node offsets (at *targetPtr):
    // +0x30: sourceMatrix[16] (float)
    // +0x90: uint32* outputMatrixPtr; // pointer where source matrix will be copied
    // +0xb0: uint64 blendedData[4]; // destination for blended result
};

// Global constants used in weighted sum (accessed via absolute addresses)
extern float gBlendCoeff[9]; // from _DAT_01218d40, _DAT_01218d44, _DAT_01218d48, _DAT_01218d50, _DAT_01218d54, _DAT_01218d58, _DAT_01218d60, _DAT_01218d64, _DAT_01218d68, _DAT_01218d70, _DAT_01218d74, _DAT_01218d78 (but used as 3x3 or 3x4?)

void __fastcall TransformBlendNode::accumulateBlend(int thisPtr) {
    int targetPtr;
    float fVar1, fVar2, fVar3;
    uint32* dest64;
    uint32 inputVec[8]; // local storage for the 8 dwords from this+0x10-0x2c

    // Determine target node: use this->targetPtr (offset 0x34) if non-zero, otherwise call FUN_00426a90(this->source (offset 0x30))
    targetPtr = *(int*)(thisPtr + 0x34);
    if ((targetPtr == 0) && (targetPtr = FUN_00426a90(*(int*)(thisPtr + 0x30)), targetPtr == 0)) {
        return;
    }

    // Initialize local storage with zeros for the first 2 values (quaternion/vector part?)
    uint32 local0 = 0;
    uint32 local1 = 0;
    uint32 local2 = *(uint32*)(0x00e2e230); // from global DAT_00e2e230
    uint32 local3 = 0;
    uint32 local4 = 0;
    float local5 = 0.0f;
    float local6 = 0.0f;
    float local7 = 0.0f;

    if (*(uint32*)(thisPtr + 0x38) < 3) {
        // Increment counter, keep blending accumulation zeroed
        *(uint32*)(thisPtr + 0x38) = *(uint32*)(thisPtr + 0x38) + 1;
        // local0..local1 remain zero
    } else {
        // Read 8 dwords from this+0x10 to this+0x2c
        local0 = *(uint32*)(thisPtr + 0x10);
        local1 = *(uint32*)(thisPtr + 0x14);
        local2 = *(uint32*)(thisPtr + 0x18);
        local3 = *(uint32*)(thisPtr + 0x1c);
        local4 = *(uint32*)(thisPtr + 0x20); // low part of first blended component?
        fVar1 = *(float*)(thisPtr + 0x24);
        fVar2 = *(float*)(thisPtr + 0x28);
        fVar3 = *(float*)(thisPtr + 0x2c);

        // Weighted sum using 9 global coefficients (arranged as 3x3 matrix applied to (fVar1, fVar2, fVar3))
        // Coefficients: gBlendCoeff[0..2] for x, gBlendCoeff[3..5] for y, gBlendCoeff[6..8] for z? But there are 12 globals used?
        // Actually the code uses: _DAT_01218d50, _DAT_01218d40, _DAT_01218d60, _DAT_01218d70 (with *0.0) for first result;
        // then fRam01218d54, fRam01218d44, _DAT_01218d64, fRam01218d74 for second; then fRam01218d58, fRam01218d48, _DAT_01218d68, fRam01218d78 for third.
        // For simplicity, we treat them as constants floating point values.
        float g0 = *(float*)0x01218d40; // _DAT_01218d40
        float g1 = *(float*)0x01218d44; // fRam01218d44
        float g2 = *(float*)0x01218d48; // fRam01218d48
        float g3 = *(float*)0x01218d50; // _DAT_01218d50
        float g4 = *(float*)0x01218d54; // fRam01218d54
        float g5 = *(float*)0x01218d58; // fRam01218d58
        float g6 = *(float*)0x01218d60; // _DAT_01218d60
        float g7 = *(float*)0x01218d64; // _DAT_01218d64
        float g8 = *(float*)0x01218d68; // _DAT_01218d68
        // The code also reads _DAT_01218d70, fRam01218d74, fRam01218d78 but multiplies by 0.0, so irrelevant.

        local5 = fVar2 * g3 + fVar1 * g0 + fVar3 * g6 + 0.0f; // weighted sum for component 1
        local6 = fVar2 * g4 + fVar1 * g1 + fVar3 * g7 + 0.0f; // weighted sum for component 2
        local7 = fVar2 * g5 + fVar1 * g2 + fVar3 * g8 + 0.0f; // weighted sum for component 3
    }

    // Write 4 uint64 values to target node at offsets +0xb0, +0xb8, +0xc0, +0xc8
    // These are packed from the local 32-bit values: low<<32 | high
    *(uint64*)(targetPtr + 0xb0) = ((uint64)local1 << 32) | local0;   // pairs from local0, local1
    *(uint64*)(targetPtr + 0xb8) = ((uint64)local3 << 32) | local2;   // pairs from local2, local3
    // The third pair: low part = local4 (int), high part = local5 (float reinterpreted as uint32)
    *(uint64*)(targetPtr + 0xc0) = ((uint64)(*(uint32*)&local5) << 32) | local4;
    // The fourth pair: low part = local6, high part = local7
    *(uint64*)(targetPtr + 0xc8) = ((uint64)(*(uint32*)&local7) << 32) | (*(uint32*)&local6);

    // If the original targetPtr was not zero (i.e., this->targetPtr exists), perform matrix copy
    if (*(int*)(thisPtr + 0x34) != 0) {
        int sourceNode = *(int*)(thisPtr + 0x30); // source node from this+0x30
        uint32* outputMatrix = *(uint32**)(*(int*)(thisPtr + 0x34) + 0x90); // target's output matrix pointer
        if (outputMatrix != 0) {
            // Copy 4x4 matrix (16 floats = 64 bytes) from sourceNode+0x30 to outputMatrix
            // The source matrix is stored as 16 consecutive floats at sourceNode+0x30
            outputMatrix[0]  = *(uint32*)(sourceNode + 0x30);
            outputMatrix[1]  = *(uint32*)(sourceNode + 0x34);
            outputMatrix[2]  = *(uint32*)(sourceNode + 0x38);
            outputMatrix[3]  = *(uint32*)(sourceNode + 0x3c);
            outputMatrix[4]  = *(uint32*)(sourceNode + 0x40);
            outputMatrix[5]  = *(uint32*)(sourceNode + 0x44);
            outputMatrix[6]  = *(uint32*)(sourceNode + 0x48);
            outputMatrix[7]  = *(uint32*)(sourceNode + 0x4c);
            outputMatrix[8]  = *(uint32*)(sourceNode + 0x50);
            outputMatrix[9]  = *(uint32*)(sourceNode + 0x54);
            outputMatrix[10] = *(uint32*)(sourceNode + 0x58);
            outputMatrix[11] = *(uint32*)(sourceNode + 0x5c);
            outputMatrix[12] = *(uint32*)(sourceNode + 0x60);
            outputMatrix[13] = *(uint32*)(sourceNode + 0x64);
            outputMatrix[14] = *(uint32*)(sourceNode + 0x68);
            outputMatrix[15] = *(uint32*)(sourceNode + 0x6c);
        }
    }
}