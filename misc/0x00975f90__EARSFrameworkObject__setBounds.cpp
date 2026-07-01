// FUNC_NAME: EARSFrameworkObject::setBounds
void __thiscall FUN_00975f90(int param_1, undefined4 *param_2)
{
  // Copy 4 consecutive float values from param_2 to object's bounding box data
  // Offsets +0x90 through +0x9C likely represent a 4-float bounding structure
  // (min.x, min.y, max.x, max.y) or a 3D AABB (min.x, min.y, min.z, max.x)
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = param_2[1]; // +0x04
  uVar2 = param_2[2]; // +0x08
  uVar3 = param_2[3]; // +0x0C
  
  *(undefined4 *)(param_1 + 0x90) = *param_2;      // +0x90 - first bound component
  *(undefined4 *)(param_1 + 0x94) = uVar1;         // +0x94 - second bound component
  *(undefined4 *)(param_1 + 0x98) = uVar2;         // +0x98 - third bound component
  *(undefined4 *)(param_1 + 0x9c) = uVar3;         // +0x9C - fourth bound component
  
  return;
}