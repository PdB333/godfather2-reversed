// FUNC_NAME: BoneMatrixBlock::setQuantizedTransform
void __thiscall BoneMatrixBlock::setQuantizedTransform(BoneMatrixBlock *this, float *inputMatrix)
{
  float scaleX;
  float scaleY;
  float scaleZ;
  float quantized[16];
  uint64_t oldValue;
  int idx;

  // Scale factors stored at offsets 0x134, 0x138, 0x13C (as raw ints reinterpreted as float)
  scaleX = *(float *)&this->field_0x4d;
  scaleY = *(float *)&this->field_0x4e;
  scaleZ = *(float *)&this->field_0x4f;

  // Copy 16 floats from incoming matrix (typically a 4x4 transform with rotation+scale+translation)
  for (idx = 0; idx < 16; idx++) {
    quantized[idx] = inputMatrix[idx];
  }

  // Apply axis scaling to the first three rows/columns (rotation+scale parts)
  quantized[0] *= scaleX;
  quantized[1] *= scaleX;
  quantized[2] *= scaleX;

  quantized[4] *= scaleY;
  quantized[5] *= scaleY;
  quantized[6] *= scaleY;

  quantized[8] *= scaleZ;
  quantized[9] *= scaleZ;
  quantized[10] *= scaleZ;

  // Preserve a 64-bit value stored in the object (likely a timestamp or hash)
  oldValue = *(uint64_t *)&this->field_0x30;

  // Store quantized (truncated to int) values into the internal int array (offsets 0xD0–0x10C)
  this->matrixInt[0] = (int)quantized[0];   // +0x34
  this->matrixInt[1] = (int)quantized[1];   // +0x35
  this->matrixInt[2] = (int)quantized[2];   // +0x36
  this->matrixInt[3] = (int)quantized[3];   // +0x37 (actually iStack_44)
  this->matrixInt[4] = (int)quantized[4];   // +0x38
  this->matrixInt[5] = (int)quantized[5];   // +0x39
  this->matrixInt[6] = (int)quantized[6];   // +0x3A
  this->matrixInt[7] = (int)quantized[7];   // +0x3B (iStack_34)
  this->matrixInt[8] = (int)quantized[8];   // +0x3C
  this->matrixInt[9] = (int)quantized[9];   // +0x3D
  this->matrixInt[10] = (int)quantized[10]; // +0x3E
  this->matrixInt[11] = (int)quantized[11]; // +0x3F (iStack_24)
  this->matrixInt[12] = (int)(uint32_t)oldValue;      // +0x40
  this->matrixInt[13] = (int)(uint32_t)(oldValue >> 32); // +0x41
  this->matrixInt[14] = this->oldFieldX;   // +0x42 copied from this->field_0x32
  this->matrixInt[15] = this->oldFieldY;   // +0x43 – will be overwritten below

  // Overwrite some entries with zeros and a global constant
  this->matrixInt[3]  = 0;   // +0x37
  this->matrixInt[7]  = 0;   // +0x3B
  this->matrixInt[11] = 0;   // +0x3F
  this->matrixInt[15] = DAT_00e2b1a4; // +0x43 global constant (maybe 1)

  // Possibly log or debug function
  FUN_006101b0();

  // Call virtual function at vtable offset 0x68 (e.g., OnMatrixFinalized)
  (this->vtable[0x68 / 4])(this);
}