// FUNC_NAME: Math::Matrix44::setFromAffineTransform
void Matrix44::setFromAffineTransform()
{
    // Buffer to receive 12 float values from external function (e.g., identity or source matrix)
    float transformData[12];
    // FUN_00aa1a10 likely fills 12 floats representing a 3x4 affine transform (rotation + translation)
    FUN_00aa1a10(transformData);

    // Copy the 12 values into a 4x4 matrix, skipping the fourth column (elements 3,7,11)
    // These elements correspond to the homogeneous w components (0,0,0,1) assumed unchanged
    this->m[0] = transformData[0];  // +0x00: row0.x
    this->m[1] = transformData[1];  // +0x04: row0.y
    this->m[2] = transformData[2];  // +0x08: row0.z
    // row0.w (+0x0C) remains default (0 in rotation rows, 1 in translation row)

    this->m[4] = transformData[4];  // +0x10: row1.x
    this->m[5] = transformData[5];  // +0x14: row1.y
    this->m[6] = transformData[6];  // +0x18: row1.z

    this->m[8] = transformData[8];  // +0x20: row2.x
    this->m[9] = transformData[9];  // +0x24: row2.y
    this->m[10] = transformData[10]; // +0x28: row2.z

    this->m[12] = transformData[12]; // +0x30: row3.x (translation x)
    this->m[13] = transformData[13]; // +0x34: row3.y (translation y)
    this->m[14] = transformData[14]; // +0x38: row3.z (translation z)
    // row3.w (+0x3C) should remain 1.0f
}