// FUNC_NAME: EARSBone::setTransform
// Function at 0x00491650: Sets the local transform (4x4 matrix) and scale factors for a bone node.
// Input: EAX = bone index, stack param1 = pointer to 16 floats (4x4 matrix), ESI = this pointer.
void __thiscall EARSBone::setTransform(uint boneIndex, float* transformMatrix) {
    // Store the bone index at +0x2D4
    *(uint*)(this + 0x2D4) = boneIndex;

    // Look up bone data from a global table (DAT_011a0f28) of 0x38-byte entries.
    // Extract two shorts at offset +2 and +4, convert to float, store at +0x330 and +0x334 (scale?)
    undefined1* boneData;
    if (boneIndex < 0x1000) {
        boneData = &DAT_011a0f28 + boneIndex * 0x38;
    } else {
        boneData = nullptr;
    }
    *(float*)(this + 0x330) = (float)*(ushort*)(boneData + 2);  // first scale component
    *(float*)(this + 0x334) = (float)*(ushort*)(boneData + 4);  // second scale component

    // Copy the 16 floats from input matrix to local storage at +0x2E0 (4x4 matrix)
    // The matrix is stored as 4 consecutive float4 (column-major or row-major? just copying)
    *(float4*)(this + 0x2E0) = *(float4*)transformMatrix;
    *(float4*)(this + 0x2F0) = *(float4*)(transformMatrix + 4);
    *(float4*)(this + 0x300) = *(float4*)(transformMatrix + 8);
    *(float4*)(this + 0x310) = *(float4*)(transformMatrix + 12);

    // If this bone belongs to the current active model (checked via global pointer DAT_012058e8),
    // update rendering data.
    if (DAT_012058e8 == (int)this) {
        // If the bone has a parent (offset +0x2D0 != 0), mark something dirty? (function at 0x006063b0)
        if (*(int*)(this + 0x2D0) != 0) {
            FUN_006063b0();  // likely invalidates parent chain
        }
        // Update the combined transform (offset +0x2E0) relative to parent? (function 0x0060b020)
        FUN_0060b020(*(undefined4*)(this + 0x14),  // bone node ID
                     *(undefined4*)(this + 0x2D8),  // parent transform
                     (undefined4*)(this + 0x2E0)); // local transform
        // Update scale values (offset +0x330) into rendering (function 0x0060add0)
        FUN_0060add0(*(undefined4*)(this + 0x14),  // bone node ID
                     *(undefined4*)(this + 800),   // some global or scale offset? 0x320
                     this + 0x330);                // pointer to two floats
    }
}