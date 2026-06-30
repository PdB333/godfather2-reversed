// FUNC_NAME: Matrix44::setAffineTransform

// Reconstructed from disassembly at 0x00610040
// Sets a 4x4 transformation matrix (stored column-major at offset 0x40) from a source matrix,
// ensuring the bottom row is (0,0,0,1) by zeroing the last element of the first three columns
// and setting the bottom-right element to 1.0f (from global constant DAT_00e2b1a4).
// The source matrix is expected to be row-major or column-major? The function copies all 16 floats,
// but then overwrites the fourth element of each column (row3) to enforce affine form.
// Likely used to initialize a world/view matrix with no perspective component.

#include <cstdint>

// Forward declaration of called function (likely normalization/inversion, not analyzed)
void FUN_006101b0();

class Matrix44 {
public:
    // Matrix at offset 0x40 stored as 4x4 column-major floats
    float m[4][4]; // +0x40

    // Member functions
    void setAffineTransform(const float* source); // 0x00610040
};

void Matrix44::setAffineTransform(const float* source) {
    // Copy all 16 floats from source into the matrix
    m[0][0] = source[0];  // +0x40
    m[0][1] = source[1];  // +0x44
    m[0][2] = source[2];  // +0x48
    m[0][3] = source[3];  // +0x4c (will be zeroed)
    m[1][0] = source[4];  // +0x50
    m[1][1] = source[5];  // +0x54
    m[1][2] = source[6];  // +0x58
    m[1][3] = source[7];  // +0x5c (will be zeroed)
    m[2][0] = source[8];  // +0x60
    m[2][1] = source[9];  // +0x64
    m[2][2] = source[10]; // +0x68
    m[2][3] = source[11]; // +0x6c (will be zeroed)
    m[3][0] = source[12]; // +0x70
    m[3][1] = source[13]; // +0x74
    m[3][2] = source[14]; // +0x78
    m[3][3] = source[15]; // +0x7c (will be overwritten)

    // Enforce affine: zero bottom row (row3) for first three columns, set bottom-right to 1.0
    m[0][3] = 0.0f;                    // +0x4c
    m[1][3] = 0.0f;                    // +0x5c
    m[2][3] = 0.0f;                    // +0x6c
    m[3][3] = *(float*)0x00e2b1a4;    // +0x7c, global constant (likely 1.0f)

    // Additional processing (e.g., normalization or inverse computation)
    FUN_006101b0();
}