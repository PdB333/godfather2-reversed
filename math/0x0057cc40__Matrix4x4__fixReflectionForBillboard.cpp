// FUNC_NAME: Matrix4x4::fixReflectionForBillboard
void Matrix4x4::fixReflectionForBillboard(void)
{
  // This function processes a matrix (likely a 4x4) stored at DAT_01223d40.
  // It iterates over rows (or columns) of the matrix, checking if the
  // determinant of the upper-left 3x3 submatrix is negative (indicating
  // a reflection). If so, it negates the third row (or column) to
  // remove the reflection, ensuring the matrix represents a pure
  // rotation (for billboard rendering).
  //
  // The matrix is stored as an array of 4x4 floats (16 floats per matrix).
  // The input in_EAX is an index into an array of matrices.
  // The loop processes each row (or column) of the matrix.
  //
  // Offsets from base (DAT_01223d40 + in_EAX * 0x10):
  //   +0x00: row0.x (or column0.x)
  //   +0x04: row0.y (or column0.y)
  //   +0x08: row0.z (or column0.z)
  //   +0x0C: row0.w (or column0.w)
  //   +0x10: row1.x
  //   +0x14: row1.y
  //   +0x18: row1.z
  //   +0x1C: row1.w
  //   +0x20: row2.x
  //   +0x24: row2.y
  //   +0x28: row2.z
  //   +0x2C: row2.w
  //   +0x30: row3.x
  //   +0x34: row3.y
  //   +0x38: row3.z
  //   +0x3C: row3.w

  float *pfVar1;
  int matrixIndex; // in_EAX
  float *pfVar2;

  // Check if the matrix pointer is valid (not pointing to itself)
  if (&DAT_01223d40 + matrixIndex * 0x10 != &DAT_01223d40) {
    // Start at the second row (offset 0x18 from base) to compute determinant
    pfVar2 = (float *)&DAT_01223d58; // This is offset 0x18 from base (row2)
    do {
      // Compute the determinant of the 3x3 submatrix formed by rows 0,1,2
      // (or columns 0,1,2) using the current row as the third row.
      // The formula: row0.x * row1.y * row2.z + row0.y * row1.z * row2.x + row0.z * row1.x * row2.y
      //             - row0.z * row1.y * row2.x - row0.y * row1.x * row2.z - row0.x * row1.z * row2.y
      // This is equivalent to the scalar triple product of the three row vectors.
      if (pfVar2[-5] * pfVar2[-1] + pfVar2[-3] * pfVar2[1] + pfVar2[-6] * pfVar2[-2] +
          pfVar2[-4] * *pfVar2 < 0.0) {
        // If determinant is negative, negate the third row (or column)
        // to flip the sign and remove reflection.
        pfVar2[-2] = 0.0 - pfVar2[-2]; // row2.x (or column2.x)
        pfVar2[-1] = 0.0 - pfVar2[-1]; // row2.y (or column2.y)
        *pfVar2 = 0.0 - *pfVar2;       // row2.z (or column2.z)
        pfVar2[1] = 0.0 - pfVar2[1];   // row2.w (or column2.w)
      }
      pfVar1 = pfVar2 + 10; // Move to next row (offset 0x28 from base)
      pfVar2 = pfVar2 + 0x10; // Advance by 16 floats (one row)
    } while (pfVar1 != (float *)(&DAT_01223d40 + matrixIndex * 0x10));
    // Loop until we've processed all rows (4 rows total)
  }
  return;
}