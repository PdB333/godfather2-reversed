// FUNC_NAME: Matrix3x4::Matrix3x4(Matrix3x4 const&)
// Address: 0x00825640
// Role: Copy constructor for a 3x4 transformation matrix (row-major, 12 floats).
// The source object is assumed to be fully constructed (FUN_0081f9f0 likely finalizes it).
// The matrix data resides at offset +0x50 in both this and source.

class Matrix3x4 {
public:
    // Vtable pointer at offset 0x00
    void* vfptr;

    // Matrix data: 3 rows of 4 floats (row-major), at offset 0x50
    // Index: [0x14]..[0x1f] corresponds to row0[0..3], row1[0..3], row2[0..3]
    float matrix[3][4];

    // Constructor that copies from another Matrix3x4
    Matrix3x4(Matrix3x4 const& source) {
        // Call some preparation function on source (likely ensures valid state)
        FUN_0081f9f0(&source);

        // Set vtable pointer
        this->vfptr = &PTR_LAB_00d73454;

        // Copy 3 rows from source's matrix (offset 0x50) to this matrix
        // Row 0 (source offsets +0x50, +0x54, +0x58, +0x5c)
        this->matrix[0][0] = *(float*)(&source + 0x50);
        this->matrix[0][1] = *(float*)((uint8_t*)&source + 0x54);
        this->matrix[0][2] = *(float*)((uint8_t*)&source + 0x58);
        this->matrix[0][3] = *(float*)((uint8_t*)&source + 0x5c);

        // Row 1 (source offsets +0x60, +0x64, +0x68, +0x6c)
        this->matrix[1][0] = *(float*)((uint8_t*)&source + 0x60);
        this->matrix[1][1] = *(float*)((uint8_t*)&source + 0x64);
        this->matrix[1][2] = *(float*)((uint8_t*)&source + 0x68);
        this->matrix[1][3] = *(float*)((uint8_t*)&source + 0x6c);

        // Row 2 (source offsets +0x70, +0x74, +0x78, +0x7c)
        this->matrix[2][0] = *(float*)((uint8_t*)&source + 0x70);
        this->matrix[2][1] = *(float*)((uint8_t*)&source + 0x74);
        this->matrix[2][2] = *(float*)((uint8_t*)&source + 0x78);
        this->matrix[2][3] = *(float*)((uint8_t*)&source + 0x7c);
    }
};