// FUNC_NAME: setEntityTransform
// Function address: 0x0061f770
// Role: Initializes an entity's transform from a matrix and a compressed representation.
// The entity transform struct holds both a 4x4 matrix and a compressed transform (position/quaternion?).
// If the matrix pointer is null, an identity matrix scaled by global constant is used.

void __fastcall setEntityTransform(float* inputMatrix, float* inputCompressed, EntityTransform* outTransform)
{
    // Copy compressed transform (4 * 8 bytes = 32 bytes) to outTransform+0x10
    outTransform->compressed_0x10[0] = *inputCompressed;       // +0x10: 8 bytes
    outTransform->compressed_0x10[1] = inputCompressed[1];     // +0x18
    outTransform->compressed_0x10[2] = inputCompressed[2];     // +0x20
    outTransform->compressed_0x10[3] = inputCompressed[3];     // +0x28

    outTransform->flag_0xdc = 1;   // +0xdc

    if (inputMatrix != NULL)
    {
        // Copy 4x4 matrix (16 floats) to outTransform+0x70
        float* dest = &outTransform->matrix_0x70[0][0];
        dest[0]  = inputMatrix[0];
        dest[1]  = inputMatrix[1];
        dest[2]  = inputMatrix[2];
        dest[3]  = inputMatrix[3];
        dest[4]  = inputMatrix[4];
        dest[5]  = inputMatrix[5];
        dest[6]  = inputMatrix[6];
        dest[7]  = inputMatrix[7];
        dest[8]  = inputMatrix[8];
        dest[9]  = inputMatrix[9];
        dest[10] = inputMatrix[10];
        dest[11] = inputMatrix[11];
        dest[12] = inputMatrix[12];
        dest[13] = inputMatrix[13];
        dest[14] = inputMatrix[14];
        dest[15] = inputMatrix[15];
        return;
    }

    // If no matrix provided, set identity matrix scaled by global constant
    {
        float scale = DAT_00e2b1a4; // global constant (likely 1.0f)
        float* identityDest = &outTransform->matrix_0x70[0][0];

        // Row 0: [scale, 0, 0, 0]
        identityDest[0] = scale;
        identityDest[1] = 0.0f;
        identityDest[2] = 0.0f;
        identityDest[3] = 0.0f;

        // Row 1: [0, scale, 0, 0]
        identityDest[4] = 0.0f;
        identityDest[5] = scale;
        identityDest[6] = 0.0f;
        identityDest[7] = 0.0f;

        // Row 2: [0, 0, scale, 0]
        identityDest[8]  = 0.0f;
        identityDest[9]  = 0.0f;
        identityDest[10] = scale;
        identityDest[11] = 0.0f;

        // Row 3: [0, 0, 0, scale]
        identityDest[12] = 0.0f;
        identityDest[13] = 0.0f;
        identityDest[14] = 0.0f;
        identityDest[15] = scale;
    }
}

// Note: The struct EntityTransform is defined as:
// Offset 0x00: (unknown header)
// Offset 0x10: compressed[4] (each is 8 bytes, e.g. two floats each)
// Offset 0x70: matrix[4][4] (4x4 float matrix)
// Offset 0xdc: int flag (set to 1)