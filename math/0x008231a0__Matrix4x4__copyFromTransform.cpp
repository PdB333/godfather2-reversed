// FUNC_NAME: Matrix4x4::copyFromTransform
undefined4 * __thiscall Matrix4x4::copyFromTransform(undefined4 *thisMatrix, int transformPtr)
{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  // Call base class or utility function on transform
  FUN_0081f9f0(transformPtr);
  
  // Set vtable pointer
  *thisMatrix = &PTR_LAB_00d7340c;
  
  // Copy 4x4 matrix from transform (16 floats, 4 per row)
  // Row 0: offset 0x50-0x5C
  uVar1 = *(undefined4 *)(transformPtr + 0x54);
  uVar2 = *(undefined4 *)(transformPtr + 0x58);
  uVar3 = *(undefined4 *)(transformPtr + 0x5c);
  thisMatrix[0x14] = *(undefined4 *)(transformPtr + 0x50);
  thisMatrix[0x15] = uVar1;
  thisMatrix[0x16] = uVar2;
  thisMatrix[0x17] = uVar3;
  
  // Row 1: offset 0x60-0x6C
  uVar1 = *(undefined4 *)(transformPtr + 100);
  uVar2 = *(undefined4 *)(transformPtr + 0x68);
  uVar3 = *(undefined4 *)(transformPtr + 0x6c);
  thisMatrix[0x18] = *(undefined4 *)(transformPtr + 0x60);
  thisMatrix[0x19] = uVar1;
  thisMatrix[0x1a] = uVar2;
  thisMatrix[0x1b] = uVar3;
  
  // Row 2: offset 0x70-0x7C
  uVar1 = *(undefined4 *)(transformPtr + 0x74);
  uVar2 = *(undefined4 *)(transformPtr + 0x78);
  uVar3 = *(undefined4 *)(transformPtr + 0x7c);
  thisMatrix[0x1c] = *(undefined4 *)(transformPtr + 0x70);
  thisMatrix[0x1d] = uVar1;
  thisMatrix[0x1e] = uVar2;
  thisMatrix[0x1f] = uVar3;
  
  // Row 3: offset 0x80-0x8C
  uVar1 = *(undefined4 *)(transformPtr + 0x84);
  uVar2 = *(undefined4 *)(transformPtr + 0x88);
  uVar3 = *(undefined4 *)(transformPtr + 0x8c);
  thisMatrix[0x20] = *(undefined4 *)(transformPtr + 0x80);
  thisMatrix[0x21] = uVar1;
  thisMatrix[0x22] = uVar2;
  thisMatrix[0x23] = uVar3;
  
  // Row 4: offset 0x90-0x9C
  uVar1 = *(undefined4 *)(transformPtr + 0x94);
  uVar2 = *(undefined4 *)(transformPtr + 0x98);
  uVar3 = *(undefined4 *)(transformPtr + 0x9c);
  thisMatrix[0x24] = *(undefined4 *)(transformPtr + 0x90);
  thisMatrix[0x25] = uVar1;
  thisMatrix[0x26] = uVar2;
  thisMatrix[0x27] = uVar3;
  
  // Row 5: offset 0xA0-0xAC
  uVar1 = *(undefined4 *)(transformPtr + 0xa4);
  uVar2 = *(undefined4 *)(transformPtr + 0xa8);
  uVar3 = *(undefined4 *)(transformPtr + 0xac);
  thisMatrix[0x28] = *(undefined4 *)(transformPtr + 0xa0);
  thisMatrix[0x29] = uVar1;
  thisMatrix[0x2a] = uVar2;
  thisMatrix[0x2b] = uVar3;
  
  // Row 6: offset 0xB0-0xBC
  uVar1 = *(undefined4 *)(transformPtr + 0xb4);
  uVar2 = *(undefined4 *)(transformPtr + 0xb8);
  uVar3 = *(undefined4 *)(transformPtr + 0xbc);
  thisMatrix[0x2c] = *(undefined4 *)(transformPtr + 0xb0);
  thisMatrix[0x2d] = uVar1;
  thisMatrix[0x2e] = uVar2;
  thisMatrix[0x2f] = uVar3;
  
  // Row 7: offset 0xC0-0xCC
  uVar1 = *(undefined4 *)(transformPtr + 0xc4);
  uVar2 = *(undefined4 *)(transformPtr + 200);
  uVar3 = *(undefined4 *)(transformPtr + 0xcc);
  thisMatrix[0x30] = *(undefined4 *)(transformPtr + 0xc0);
  thisMatrix[0x31] = uVar1;
  thisMatrix[0x32] = uVar2;
  thisMatrix[0x33] = uVar3;
  
  // Row 8: offset 0xD0-0xDC
  uVar1 = *(undefined4 *)(transformPtr + 0xd4);
  uVar2 = *(undefined4 *)(transformPtr + 0xd8);
  uVar3 = *(undefined4 *)(transformPtr + 0xdc);
  thisMatrix[0x34] = *(undefined4 *)(transformPtr + 0xd0);
  thisMatrix[0x35] = uVar1;
  thisMatrix[0x36] = uVar2;
  thisMatrix[0x37] = uVar3;
  
  // Row 9: offset 0xE0-0xEC
  uVar1 = *(undefined4 *)(transformPtr + 0xe4);
  uVar2 = *(undefined4 *)(transformPtr + 0xe8);
  uVar3 = *(undefined4 *)(transformPtr + 0xec);
  thisMatrix[0x38] = *(undefined4 *)(transformPtr + 0xe0);
  thisMatrix[0x39] = uVar1;
  thisMatrix[0x3a] = uVar2;
  thisMatrix[0x3b] = uVar3;
  
  // Row 10: offset 0xF0-0xFC
  uVar1 = *(undefined4 *)(transformPtr + 0xf4);
  uVar2 = *(undefined4 *)(transformPtr + 0xf8);
  uVar3 = *(undefined4 *)(transformPtr + 0xfc);
  thisMatrix[0x3c] = *(undefined4 *)(transformPtr + 0xf0);
  thisMatrix[0x3d] = uVar1;
  thisMatrix[0x3e] = uVar2;
  thisMatrix[0x3f] = uVar3;
  
  // Row 11: offset 0x100-0x10C
  uVar1 = *(undefined4 *)(transformPtr + 0x104);
  uVar2 = *(undefined4 *)(transformPtr + 0x108);
  uVar3 = *(undefined4 *)(transformPtr + 0x10c);
  thisMatrix[0x40] = *(undefined4 *)(transformPtr + 0x100);
  thisMatrix[0x41] = uVar1;
  thisMatrix[0x42] = uVar2;
  thisMatrix[0x43] = uVar3;
  
  return thisMatrix;
}