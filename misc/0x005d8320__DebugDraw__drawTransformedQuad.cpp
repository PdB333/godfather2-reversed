// FUNC_NAME: DebugDraw::drawTransformedQuad
void __thiscall DebugDraw::drawTransformedQuad(int this, int cmdBuffer, float* matrix4x4, float* pointA, float* pointB, unsigned int* colorA, unsigned int* colorB, unsigned int packedColor)
{
  int iVar1;
  int* piVar2;
  unsigned int* puVar3;
  uint uVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  unsigned int local_c0;        // temporary storage for pointB[0]
  float fStack_bc;              // pointA[1] copy
  float fStack_b8;              // pointA[2] copy
  float fStack_b4;              // pointA[3] copy
  float local_b0;               // pointA[0] copy (start of vectorA)
  unsigned int uStack_ac;       // pointB[1]
  unsigned int uStack_a8;       // pointB[2]
  unsigned int uStack_a4;       // pointB[3]
  unsigned int local_a0;        // colorA[0]
  unsigned int local_9c;        // colorA[1]
  unsigned int local_90;        // colorB[0]
  unsigned int local_8c;        // copy of colorA[1]
  unsigned int local_80;        // copy of colorA[0]
  unsigned int local_70;        // copy of colorB[0]
  unsigned int local_6c;        // copy of colorB[1]
  unsigned int local_60;        // pointB[0] for first transform
  unsigned int uStack_5c;       // pointB[1] (for second/third transform)
  unsigned int uStack_58;       // pointB[2]
  unsigned int uStack_54;       // pointB[3]
  float local_50;               // transformed point result (x)
  float fStack_4c;              // transformed point result (y)
  float fStack_48;              // transformed point result (z)
  float fStack_44;              // transformed point result (w)
  unsigned char local_40[16];   // transformed vector output (third multiply)
  unsigned char local_30[16];   // transformed vector output (second multiply)
  unsigned char local_20[28];   // transformed vector output (first multiply) – size 28? Actually 7 floats?
  
  // Constructor call – likely initializes this as a temporary object
  FUN_005c5320(this);
  
  // Copy input vectors to stack
  fVar5 = *pointA;          // pointA.x
  fVar6 = pointA[1];        // pointA.y
  fVar7 = pointA[2];        // pointA.z
  fVar8 = pointA[3];        // pointA.w
  local_60 = *pointB;       // pointB.x
  uStack_ac = pointB[1];    // pointB.y
  uStack_a8 = pointB[2];    // pointB.z
  uStack_a4 = pointB[3];    // pointB.w
  local_c0 = *pointB;       // duplicate
  local_b0 = *pointA;       // pointA.x
  fStack_bc = fVar6;        // pointA.y
  fStack_b8 = fVar7;        // pointA.z
  fStack_b4 = fVar8;        // pointA.w
  uStack_5c = uStack_ac;    // duplicate
  uStack_58 = uStack_a8;
  uStack_54 = uStack_a4;
  
  // Transform three vectors by the matrix:
  // 1. Full pointB (contiguous via local_60, uStack_5c, uStack_58, uStack_54)
  FUN_0056b420(matrix4x4, &local_60, local_20);   // matrix * pointB -> local_20
  // 2. A mixed vector formed from pointA[0], pointB[1..3] (due to stack layout)
  FUN_0056b420(matrix4x4, &local_b0, local_30);   // matrix * (pointA.x, pointB.y, pointB.z, pointB.w) -> local_30
  // 3. Another mixed vector: pointB[0], pointA[1..3]
  FUN_0056b420(matrix4x4, &local_c0, local_40);   // matrix * (pointB.x, pointA.y, pointA.z, pointA.w) -> local_40
  
  // Store colors from param_6 and param_7
  local_a0 = *colorA;           // colorA[0] (RGBA)
  local_50 = matrix4x4[0xc] * fVar8 + *matrix4x4 * fVar5 + matrix4x4[4] * fVar6 + matrix4x4[8] * fVar7; // transformed pointA.x
  fStack_4c = matrix4x4[0xd] * fVar8 + matrix4x4[1] * fVar5 + matrix4x4[5] * fVar6 + matrix4x4[9] * fVar7; // transformed pointA.y
  fStack_48 = matrix4x4[0xe] * fVar8 + matrix4x4[2] * fVar5 + matrix4x4[6] * fVar6 + matrix4x4[10] * fVar7; // transformed pointA.z
  fStack_44 = matrix4x4[0xf] * fVar8 + matrix4x4[3] * fVar5 + matrix4x4[7] * fVar6 + matrix4x4[0xb] * fVar7; // transformed pointA.w
  local_9c = colorA[1];         // colorA[1] (stride? probably second color)
  local_90 = *colorB;           // colorB[0]
  local_7c = colorB[1];         // colorB[1]
  
  // Byte-swap packedColor (likely from ABGR to RGBA)
  uVar4 = (packedColor & 0xff0000 | packedColor >> 0x10) >> 8 | (packedColor & 0xff00 | packedColor << 0x10) << 8;
  
  local_8c = local_9c;          // duplicate assignments
  local_80 = local_a0;
  local_70 = local_90;
  local_6c = local_7c;
  
  if (DAT_0119d0ac == 1)        // global debug flag
  {
    // Additional debug output – push commands to debug buffer
    FUN_005d8020();             // begin debug command
    iVar1 = DAT_01206880;       // debug buffer pointer
    *(unsigned int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8; // push command type identifier
    *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + 4;
    *(unsigned int**)(iVar1 + 0x14) = 8; // opcode 8
    *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + 4;
    
    iVar1 = DAT_01206880;
    *(unsigned int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18; // push another identifier
    *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + 4;
    
    piVar2 = (int*)(iVar1 + 0x14);
    puVar3 = (unsigned int*)(*(int*)(iVar1 + 0x14) + 3U & 0xfffffffc); // align to 4
    *piVar2 = (int)puVar3;
    *puVar3 = 1;   // float/uint data
    puVar3 = (unsigned int*)(*piVar2 + 7U & 0xfffffffc);
    *piVar2 = (int)puVar3;
    *puVar3 = 1;   // another one
    puVar3 = (unsigned int*)(*piVar2 + 7U & 0xfffffffc);
    *piVar2 = (int)puVar3;
    *puVar3 = 5;   // maybe vertex count or type
    *piVar2 = *piVar2 + 4;
    
    FUN_005d8140(*(int*)(cmdBuffer + 0x10), uVar4); // send packed color with some ID
    
    FUN_005d8020(); // begin another command
    iVar1 = DAT_01206880;
    *(unsigned int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126bb8;
    *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + 4;
    *(unsigned int**)(iVar1 + 0x14) = 7; // opcode 7
    *(int*)(iVar1 + 0x14) = *(int*)(iVar1 + 0x14) + 4;
    
    piVar2 = (int*)(DAT_01206880 + 0x14);
    *(unsigned int**)(DAT_01206880 + 0x14) = &PTR_LAB_01126b18;
    *piVar2 = *piVar2 + 4;
    
    puVar3 = (unsigned int*)(*piVar2 + 3U & 0xfffffffc);
    *piVar2 = (int)puVar3;
    *puVar3 = 1;
    puVar3 = (unsigned int*)(*piVar2 + 7U & 0xfffffffc);
    *piVar2 = (int)puVar3;
    *puVar3 = 7; // another data value
    puVar3 = (unsigned int*)(*piVar2 + 7U & 0xfffffffc);
    *piVar2 = (int)puVar3;
    *puVar3 = 8; // another
    *piVar2 = *piVar2 + 4;
    
    FUN_005d8140(*(int*)(cmdBuffer + 0x10), uVar4); // send again
    FUN_005d8020();
    return;
  }
  
  // Single command draw (non-debug)
  FUN_005d8140(*(int*)(cmdBuffer + 0x10), uVar4);
  return;
}