// FUNC_NAME: Matrix4x4::setFromArray
void __thiscall Matrix4x4::setFromArray(int this, undefined4 *srcArray)
{
  undefined4 v1, v2, v3;
  
  // Copy first row (columns 0-3)
  v1 = srcArray[1];
  v2 = srcArray[2];
  v3 = srcArray[3];
  *(undefined4 *)(this + 0x170) = *srcArray;      // +0x170: m[0][0]
  *(undefined4 *)(this + 0x174) = v1;              // +0x174: m[0][1]
  *(undefined4 *)(this + 0x178) = v2;              // +0x178: m[0][2]
  *(undefined4 *)(this + 0x17c) = v3;              // +0x17c: m[0][3]

  // Copy second row (columns 4-7)
  v1 = srcArray[5];
  v2 = srcArray[6];
  v3 = srcArray[7];
  *(undefined4 *)(this + 0x180) = srcArray[4];     // +0x180: m[1][0]
  *(undefined4 *)(this + 0x184) = v1;              // +0x184: m[1][1]
  *(undefined4 *)(this + 0x188) = v2;              // +0x188: m[1][2]
  *(undefined4 *)(this + 0x18c) = v3;              // +0x18c: m[1][3]

  // Copy third row (columns 8-11)
  v1 = srcArray[9];
  v2 = srcArray[10];
  v3 = srcArray[0xb];
  *(undefined4 *)(this + 400) = srcArray[8];       // +0x190: m[2][0]
  *(undefined4 *)(this + 0x194) = v1;              // +0x194: m[2][1]
  *(undefined4 *)(this + 0x198) = v2;              // +0x198: m[2][2]
  *(undefined4 *)(this + 0x19c) = v3;              // +0x19c: m[2][3]

  // Copy fourth row (columns 12-15)
  v1 = srcArray[0xd];
  v2 = srcArray[0xe];
  v3 = srcArray[0xf];
  *(undefined4 *)(this + 0x1a0) = srcArray[0xc];   // +0x1a0: m[3][0]
  *(undefined4 *)(this + 0x1a4) = v1;              // +0x1a4: m[3][1]
  *(undefined4 *)(this + 0x1a8) = v2;              // +0x1a8: m[3][2]
  *(undefined4 *)(this + 0x1ac) = v3;              // +0x1ac: m[3][3]

  // Deallocate the source array (likely a temporary)
  FUN_004df720(srcArray);
  return;
}