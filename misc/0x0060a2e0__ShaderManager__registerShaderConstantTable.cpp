// FUNC_NAME: ShaderManager::registerShaderConstantTable
uint ShaderManager::registerShaderConstantTable(int param_1)
{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  undefined4 unaff_ESI;
  undefined4 uStack_10;
  undefined4 *puStack_c;
  
  // Get the shader constant table pointer from the object at offset DAT_00f15a14 * 4
  uVar1 = *(undefined4 *)(param_1 + DAT_00f15a14 * 4);
  puStack_c = &param_1;
  uStack_10 = uVar1;
  
  // Check if we need to initialize the shader system
  iVar2 = (**(code **)(*DAT_01205750 + 0x1a8))(DAT_01205750);
  if (iVar2 == -0x7789fe84) {
    (*(code *)PTR_FUN_00f15a3c)(2);
  }
  
  // Get the shader constant table from D3DX
  D3DXGetShaderConstantTable(uVar1, &uStack_10);
  
  // Search for an empty slot in the constant table array (0x800 slots)
  uVar3 = 1;
  piVar4 = &DAT_011eb900;
  do {
    if (*piVar4 == 0) {
      // Found empty slot, store the constant table info
      iVar2 = uVar3 * 0x10;
      *(undefined4 *)(&DAT_011eb8f0 + iVar2) = unaff_ESI;
      *(undefined4 *)(&DAT_011eb8f4 + iVar2) = uStack_10;
      *(undefined4 *)(&DAT_011eb8f8 + iVar2) = 0;
      (&DAT_011eb8fc)[iVar2] = 0;
      return uVar3;
    }
    uVar3 = uVar3 + 1;
    piVar4 = piVar4 + 4;
  } while (uVar3 < 0x800);
  
  // No empty slot found
  return 0;
}