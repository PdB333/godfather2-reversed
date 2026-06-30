// FUNC_NAME: ShaderManager::registerShaderConstantTable
uint __fastcall ShaderManager::registerShaderConstantTable(int param_1)
{
  undefined4 uVar1;
  int in_EAX;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 unaff_ESI;
  undefined4 unaff_EDI;
  
  // Get the shader constant table from the parameter using a global offset
  uVar1 = *(undefined4 *)(param_1 + DAT_00f15a14 * 4);
  
  // Check if the device supports the shader version
  iVar2 = (**(code **)(*DAT_01205750 + 0x16c))(DAT_01205750, uVar1);
  if (iVar2 == -0x7789fe84) {
    // If not supported, call error handler
    (*(code *)PTR_FUN_00f15a3c)(2);
  }
  
  // Check if there's an additional parameter and validate
  if ((in_EAX != 0) &&
     (iVar2 = (**(code **)(*DAT_01205750 + 0x158))(DAT_01205750), iVar2 == -0x7789fe84)) {
    (*(code *)PTR_FUN_00f15a3c)(2);
  }
  
  // Get the shader constant table interface
  D3DXGetShaderConstantTable(uVar1, &stack0xfffffff0);
  
  // Search for an empty slot in the constant table array (0x800 slots)
  uVar3 = 1;
  piVar4 = &DAT_011eb900;
  do {
    if (*piVar4 == 0) {
      // Found empty slot, store the table data
      iVar2 = uVar3 * 0x10;
      *(undefined4 *)(&DAT_011eb8f0 + iVar2) = unaff_EDI;
      *(undefined4 *)(&DAT_011eb8f8 + iVar2) = 0;
      *(undefined4 *)(&DAT_011eb8f4 + iVar2) = unaff_ESI;
      (&DAT_011eb8fc)[iVar2] = 1;
      return uVar3;
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 4;
  } while (uVar3 < 0x800);
  
  // No empty slot found
  return 0;
}