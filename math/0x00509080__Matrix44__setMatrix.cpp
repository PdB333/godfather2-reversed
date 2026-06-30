// FUNC_NAME: Matrix44::setMatrix
// Address: 0x00509080
// Sets the 4x4 matrix transform (16 floats) and updates the dirty/valid flag.
// Offsets:
// +0x08: uint m_flags (bit 0x8 = kFlagMatrixValid)
// +0x20: float m_matrix[16] (row-major 4x4)

void __thiscall Matrix44::setMatrix(uint32 *matrix)
{
  // Update the valid flag based on whether a matrix is provided
  if (matrix != nullptr)
  {
    m_flags |= 0x8;  // kFlagMatrixValid

    // Copy 16 floats (64 bytes) from source to the internal matrix
    m_matrix[0]  = matrix[0];
    m_matrix[1]  = matrix[1];
    m_matrix[2]  = matrix[2];
    m_matrix[3]  = matrix[3];
    m_matrix[4]  = matrix[4];
    m_matrix[5]  = matrix[5];
    m_matrix[6]  = matrix[6];
    m_matrix[7]  = matrix[7];
    m_matrix[8]  = matrix[8];
    m_matrix[9]  = matrix[9];
    m_matrix[10] = matrix[10];
    m_matrix[11] = matrix[11];
    m_matrix[12] = matrix[12];
    m_matrix[13] = matrix[13];
    m_matrix[14] = matrix[14];
    m_matrix[15] = matrix[15];
  }
  else
  {
    // Clear the valid flag when setting to null
    m_flags &= ~0x8;
  }
}