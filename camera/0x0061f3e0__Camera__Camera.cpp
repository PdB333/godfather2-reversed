// FUNC_NAME: Camera::Camera
void __thiscall Camera::Camera(Camera *this)
{
  float identityScale = DAT_00e2b1a4; // Likely 1.0f (identity matrix diagonal)

  // Set vtable pointer
  *(void**)this = (void*)&PTR_FUN_00e41380;

  // Initialize 4x4 matrix at offset 0x70 to identity
  // Matrix is stored as 16 floats, row-major (index i*4 + j)
  // Diagonal elements set to identityScale (1.0f), rest zero
  this->matrix[0] = identityScale; // +0x70
  this->matrix[1] = 0.0f;          // +0x74
  this->matrix[2] = 0.0f;          // +0x78
  this->matrix[3] = 0.0f;          // +0x7C
  this->matrix[4] = 0.0f;          // +0x80

  this->matrix[5] = identityScale; // +0x84
  this->matrix[6] = 0.0f;          // +0x88
  this->matrix[7] = 0.0f;          // +0x8C
  this->matrix[8] = 0.0f;          // +0x90
  this->matrix[9] = 0.0f;          // +0x94

  this->matrix[10] = identityScale; // +0x98
  this->matrix[11] = 0.0f;          // +0x9C
  this->matrix[12] = 0.0f;          // +0xA0
  this->matrix[13] = 0.0f;          // +0xA4
  this->matrix[14] = 0.0f;          // +0xA8

  this->matrix[15] = identityScale; // +0xAC
  // Note: Matrix indices 16-18 are separate fields below (offset 0xB0-0xB8)

  // Zero additional fields after matrix
  this->extraField0 = 0.0f; // +0xB0 (index 16)
  this->extraField1 = 0.0f; // +0xB4 (index 17)
  this->extraField2 = 0.0f; // +0xB8 (index 18)

  // Zero fields at offset 0xC0-0xDC
  this->fieldAt0xC0 = 0; // +0xC0
  this->fieldAt0xC4 = 0; // +0xC4
  this->fieldAt0xC8 = 0; // +0xC8
  this->fieldAt0xCC = 0; // +0xCC
  this->fieldAt0xD0 = 0; // +0xD0
  *(short*)&this->fieldAt0xD4 = 0; // +0xD4 (2 bytes)
  *(short*)((int)&this->fieldAt0xD4 + 2) = 0; // +0xD6 (2 bytes)
  *(short*)&this->fieldAt0xD8 = 0; // +0xD8 (2 bytes)
  *(short*)((int)&this->fieldAt0xD8 + 2) = 0; // +0xDA (2 bytes)
  this->fieldAt0xDC = 0; // +0xDC
}