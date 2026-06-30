// FUNC_NAME: SomeClass::getSomeVector4
uint __thiscall SomeClass::getSomeVector4(int thisPtr, undefined4 *outVec4)
{
  undefined4 uVar1;
  undefined4 uVar2;
  uint in_EAX;
  uint uVar3;
  int iVar4;
  
  uVar2 = DAT_00e2b1a4; // Some global constant
  uVar3 = in_EAX & 0xffffff00;
  
  // Check if some state at +0x4c is non-zero and not 0x48
  if ((*(int *)(thisPtr + 0x4c) != 0) && (*(int *)(thisPtr + 0x4c) != 0x48)) {
    // Calculate offset based on state value
    if (*(int *)(thisPtr + 0x4c) == 0) {
      iVar4 = 0;
    }
    else {
      iVar4 = *(int *)(thisPtr + 0x4c) + -0x48;
    }
    
    // Copy 3 floats from offset +0x100, +0x104, +0x108
    *outVec4 = *(undefined4 *)(iVar4 + 0x100);
    outVec4[1] = *(undefined4 *)(iVar4 + 0x104);
    uVar1 = *(undefined4 *)(iVar4 + 0x108);
    outVec4[3] = uVar2; // Set w component to global constant
    outVec4[2] = uVar1;
    
    uVar3 = CONCAT31((int3)((uint)iVar4 >> 8),1);
  }
  
  return uVar3;
}