// FUNC_NAME: Matrix4x4::invertTranspose
void __fastcall Matrix4x4::invertTranspose(float *this)
{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float *in_EAX; // destination matrix pointer (likely return via ECX)
  float fVar15;
  float fVar16;
  float fVar17;
  
  // Load 4x3 affine part (column-major?): rows 0-2 (3x4 elements)
  // +0x00 - +0x02: row0 (x)
  // +0x04 - +0x06: row1 (y)
  // +0x08 - +0x0A: row2 (z)
  // +0x0C - +0x0F: row3 (translation)
  fVar1 = this[0xc]; // translation.x
  fVar2 = this[0xd]; // translation.y
  fVar3 = this[0xe]; // translation.z
  fVar4 = this[0xf]; // translation.w (usually 1.0)
  fVar5 = this[0];   // row0.x
  fVar6 = this[1];   // row0.y
  fVar7 = this[2];   // row0.z
  fVar8 = this[8];   // row2.x
  fVar9 = this[9];   // row2.y
  fVar10 = this[10]; // row2.z
  fVar11 = this[4];  // row1.x
  fVar12 = this[5];  // row1.y
  fVar13 = this[6];  // row1.z
  
  // Zero out translation components for inverse calculation
  fVar15 = fVar1 - fVar1; // 0
  fVar16 = fVar2 - fVar2; // 0
  fVar17 = fVar3 - fVar3; // 0
  
  // Write transposed upper 3x3 to destination (in_EAX is output pointer)
  // Transpose: row0 of source becomes column0 of dest, etc.
  in_EAX[0]  = fVar5;  // m00 = row0.x
  in_EAX[1]  = fVar11; // m10 = row1.x
  in_EAX[2]  = fVar8;  // m20 = row2.x
  in_EAX[3]  = fVar15; // m30 = translation x (zero)
  
  in_EAX[4]  = fVar6;  // m01 = row0.y
  in_EAX[5]  = fVar12; // m11 = row1.y
  in_EAX[6]  = fVar9;  // m21 = row2.y
  in_EAX[7]  = fVar16; // m31 = translation y (zero)
  
  fVar14 = _DAT_00d5780c; // global constant (likely something like 1.0 or epsilon)
  in_EAX[8]  = fVar7;  // m02 = row0.z
  in_EAX[9]  = fVar13; // m12 = row1.z
  in_EAX[10] = fVar10; // m22 = row2.z
  in_EAX[0xb] = fVar17; // m32 = translation z (zero)
  
  // Compute new translation: -transpose(R) * translation
  in_EAX[0xc] = fVar15 - (fVar2 * fVar6 + fVar1 * fVar5 + fVar3 * fVar7); // newTx = -(dot(row0, trans))
  in_EAX[0xd] = fVar16 - (fVar2 * fVar12 + fVar1 * fVar11 + fVar3 * fVar13); // newTy = -(dot(row1, trans))
  in_EAX[0xe] = fVar17 - (fVar2 * fVar9 + fVar1 * fVar8 + fVar3 * fVar10);   // newTz = -(dot(row2, trans))
  
  // Compute w component (for projective matrices)
  in_EAX[0xf] = (fVar4 - fVar4) - (fVar2 * fVar16 + fVar1 * fVar15 + fVar3 * fVar17);
  
  // Override w with the global constant (likely to handle w=1 or scaling)
  in_EAX[0xf] = fVar14;
  
  return;
}