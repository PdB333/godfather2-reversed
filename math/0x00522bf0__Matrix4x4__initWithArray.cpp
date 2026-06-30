// FUNC_NAME: Matrix4x4::initWithArray
// Function address: 0x00522bf0
// Copies 16 floats from an array into the 4x4 matrix storage (at offset 0x60) and zeros auxiliary fields.
// Called two initialization functions at 0x00424470 and 0x00417560 (probably base class or internal setup)

void __thiscall Matrix4x4::initWithArray(Matrix4x4* this, const float* data) {
    // EA EARS internal initialization (likely sets identity flags or reference counting)
    FUN_00424470(this);    // setUnknown1
    FUN_00417560(this);    // setUnknown2

    // Matrix data stored as 16 floats starting at offset 0x60 (4x4 row-major?)
    this->matrix[0]  = data[0];   // offset +0x60
    this->matrix[1]  = data[1];   // offset +0x64
    this->matrix[2]  = data[2];   // offset +0x68
    this->matrix[3]  = data[3];   // offset +0x6c
    this->matrix[4]  = data[4];   // offset +0x70
    this->matrix[5]  = data[5];   // offset +0x74
    this->matrix[6]  = data[6];   // offset +0x78
    this->matrix[7]  = data[7];   // offset +0x7c
    this->matrix[8]  = data[8];   // offset +0x80
    this->matrix[9]  = data[9];   // offset +0x84
    this->matrix[10] = data[10];  // offset +0x88
    this->matrix[11] = data[11];  // offset +0x8c
    this->matrix[12] = data[12];  // offset +0x90
    this->matrix[13] = data[13];  // offset +0x94
    this->matrix[14] = data[14];  // offset +0x98
    this->matrix[15] = data[15];  // offset +0x9c

    // Zero out transformation state flags (likely identity, scale, rotation flags)
    this->flags1 = 0;   // offset +0x08 (int32)
    this->flags2 = 0;   // offset +0x0c (int32)
    this->type1 = 0;    // offset +0x10 (int16)
    this->type2 = 0;    // offset +0x12 (int16)
    this->extra = 0;    // offset +0x14 (int32)
}