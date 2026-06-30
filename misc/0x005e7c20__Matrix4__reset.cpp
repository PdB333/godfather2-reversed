// FUNC_NAME: Matrix4::reset

void Matrix4::reset(void)
{
    float *matrix = (float *)this;                 // +0x00, 4x4 matrix (16 floats)
    float diagVal = *(float *)&DAT_00e2b1a4;       // default diagonal value (likely 1.0f)

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            if (row == col)
                matrix[row * 4 + col] = diagVal;
            else
                matrix[row * 4 + col] = 0.0f;
        }
    }

    this[0x10] = 0;   // +0x40, translation X (or padding)
    this[0x11] = 0;   // +0x44, translation Y
    this[0x12] = 0;   // +0x48, translation Z
    this[0x13] = 0;   // +0x4C, translation W (or unused)
    this[0x18] = 0;   // +0x60, unknown field
    this[0x19] = 0;   // +0x64, unknown field
    this[0x1a] = DAT_00f15b7c | DAT_00f15b78;  // +0x68, flags or combined value
}