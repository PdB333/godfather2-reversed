// FUNC_NAME: Vector4AddXYZ
// Address: 0x00501790
// Adds XYZ components of two 4-component vectors, preserving W of destination.
// Calling convention: __fastcall; dest in EAX, src1 in EDX, src2 on stack.

void __fastcall Vector4AddXYZ(float* dest, float* src1, float* src2)
{
    // Load src1 components
    float src1_y = src1[1];
    float src1_z = src1[2];
    float src1_w = src1[3]; // loaded but unused; w not added

    // Load src2 components
    float src2_y = src2[1];
    float src2_z = src2[2];
    float src2_w = src2[3]; // loaded but unused

    // Preserve destination's original W
    float original_w = dest[3];

    // Add XYZ components
    dest[0] = src1[0] + src2[0]; // x
    dest[1] = src1_y + src2_y;   // y
    dest[2] = src1_z + src2_z;   // z

    // Restore destination W (unchanged)
    dest[3] = original_w;
}