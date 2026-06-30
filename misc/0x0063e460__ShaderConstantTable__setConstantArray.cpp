// FUNC_NAME: ShaderConstantTable::setConstantArray
void __thiscall ShaderConstantTable::setConstantArray(int this, int *param_2)
{
  int *piVar1;
  undefined4 *in_EAX;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  
  piVar1 = *(int **)(this + 0x1c); // +0x1c: pointer to constant table data
  iVar3 = *piVar1; // pointer to shader program
  if (*(int *)(iVar3 + 0x34) < piVar1[0xb] + 1) { // +0x34: constant buffer capacity
    uVar2 = FUN_00627930(*(undefined4 *)(this + 0x20), // +0x20: allocator
                         *(undefined4 *)(iVar3 + 0x10), // +0x10: constant buffer pointer
                         (int *)(iVar3 + 0x34), // +0x34: constant count
                         4, // element size (4 bytes)
                         "constant table overflow");
    *(undefined4 *)(iVar3 + 0x10) = uVar2;
  }
  *(int *)(*(int *)(iVar3 + 0x10) + piVar1[0xb] * 4) = *param_2; // store constant value
  piVar1[0xb] = piVar1[0xb] + 1; // increment constant count
  uVar2 = FUN_006438e0((piVar1[0xb] + -1) * 0x40 | 0x22, // compute register offset
                       *(undefined4 *)(piVar1[3] + 8)); // +8: shader handle
  in_EAX[3] = 0xffffffff;
  in_EAX[4] = 0xffffffff;
  *in_EAX = 10; // constant type (float4)
  in_EAX[1] = uVar2; // register index
  iVar3 = 0;
  if (*(char *)(*param_2 + 0x44) != '\0') { // +0x44: array element count
    piVar4 = param_2 + 0xf; // start of array elements (offset 0x3c)
    do {
      FUN_006438e0(-(uint)(piVar4[-1] != 5) & 4 | *piVar4 << 0xf, // encode element type and value
                   *(undefined4 *)(piVar1[3] + 8));
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 5; // each element is 20 bytes (5 ints)
    } while (iVar3 < (int)(uint)*(byte *)(*param_2 + 0x44));
  }
  return;
}