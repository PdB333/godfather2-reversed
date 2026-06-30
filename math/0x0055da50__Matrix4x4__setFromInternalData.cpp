// FUNC_NAME: Matrix4x4::setFromInternalData
void Matrix4x4::setFromInternalData(void)
{
    // Temporary buffer to hold 12 float values (3x4 matrix or rotation+translation)
    float temp[12]; // local_50, local_4c, ..., local_18

    // Call helper to fill temp with data (e.g., from quaternion or Euler angles)
    FUN_00aa1a10(temp);

    // Copy the 12 values into the 4x4 matrix (column-major order)
    // The matrix is stored as float[16] with indices:
    // col0: 0,1,2,3; col1: 4,5,6,7; col2: 8,9,10,11; col3: 12,13,14,15
    // We set the first three elements of each column (rotation + translation)
    // The fourth element of each column (row3) is left unchanged (typically 0,0,0,1)
    this->m[0] = temp[0];   // col0.x
    this->m[1] = temp[1];   // col0.y
    this->m[2] = temp[2];   // col0.z
    // skip m[3] (col0.w)
    this->m[4] = temp[3];   // col1.x
    this->m[5] = temp[4];   // col1.y
    this->m[6] = temp[5];   // col1.z
    // skip m[7] (col1.w)
    this->m[8] = temp[6];   // col2.x
    this->m[9] = temp[7];   // col2.y
    this->m[10] = temp[8];  // col2.z
    // skip m[11] (col2.w)
    this->m[12] = temp[9];  // col3.x (translation)
    this->m[13] = temp[10]; // col3.y (translation)
    this->m[14] = temp[11]; // col3.z (translation)
    // skip m[15] (col3.w)
}