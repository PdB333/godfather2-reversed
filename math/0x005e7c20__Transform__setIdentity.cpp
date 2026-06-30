// FUNC_NAME: Transform::setIdentity
// Address: 0x005e7c20
// Initializes a transformation structure: 4x4 matrix to identity, zeros a 4-vector at offset 0x40,
// and sets a 3-vector at offset 0x60 to (0,0,1) (or (0,0, combinedVal)).
void __thiscall Transform::setIdentity()
{
    // Global constant for identity diagonal (likely 1.0f)
    float identityVal = *(float*)0x00e2b1a4;
    // Combined constant from two ints (probably 0x3F800000 = 1.0f)
    float combinedVal = *(int*)0x00f15b78 | *(int*)0x00f15b7c;

    // Set 4x4 matrix to identity (diagonal = identityVal, off-diagonal = 0)
    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            // +0x00: matrix[4][4] (row-major, each element is 4 bytes)
            if (row == col)
                matrix[row][col] = identityVal;
            else
                matrix[row][col] = 0.0f;
        }
    }

    // Zero out 4 floats at offset 0x40 (likely pivot or extra translation)
    // +0x40: field_vec4_0[4]
    field_vec4_0[0] = 0.0f; // +0x40
    field_vec4_0[1] = 0.0f; // +0x44
    field_vec4_0[2] = 0.0f; // +0x48
    field_vec4_0[3] = 0.0f; // +0x4C

    // Zero first two floats at offset 0x60, set third to combinedVal
    // +0x60: field_vec3_1[3]
    field_vec3_1[0] = 0.0f; // +0x60
    field_vec3_1[1] = 0.0f; // +0x64
    field_vec3_1[2] = combinedVal; // +0x68, likely 1.0f
}