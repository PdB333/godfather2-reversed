// FUNC_NAME: RenderEntityCommon::allocateOrLookupVertexBuffer
undefined4 * __fastcall RenderEntityCommon::allocateOrLookupVertexBuffer(undefined4 *param_1, int param_2, int *param_3)
{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint uVar6;
  
  puVar5 = DAT_0120557c; // Global vertex buffer pointer (DAT_0120557c)
  iVar1 = *param_3;      // Index/type parameter from caller
  if (iVar1 == 0) {
    // Allocate new 16-element (64 bytes) block by copying from param_1
    uVar2 = param_1[1];
    uVar3 = param_1[2];
    uVar4 = param_1[3];
    *DAT_0120557c = *param_1;
    puVar5[1] = uVar2;
    puVar5[2] = uVar3;
    puVar5[3] = uVar4;
    uVar2 = param_1[5];
    uVar3 = param_1[6];
    uVar4 = param_1[7];
    puVar5[4] = param_1[4];
    puVar5[5] = uVar2;
    puVar5[6] = uVar3;
    puVar5[7] = uVar4;
    uVar2 = param_1[9];
    uVar3 = param_1[10];
    uVar4 = param_1[0xb];
    puVar5[8] = param_1[8];
    puVar5[9] = uVar2;
    puVar5[10] = uVar3;
    puVar5[0xb] = uVar4;
    uVar2 = param_1[0xd];
    uVar3 = param_1[0xe];
    uVar4 = param_1[0xf];
    puVar5[0xc] = param_1[0xc];
    puVar5[0xd] = uVar2;
    puVar5[0xe] = uVar3;
    puVar5[0xf] = uVar4;
    return puVar5;
  }
  // Lookup existing buffer: param_2 + 0xb4 = texture/type pointer, param_2 + 0xb8 = data array
  if ((*(int *)(param_2 + 0xb4) != 0) &&
     (uVar6 = (uint)*(byte *)(*(int *)(param_2 + 0xb4) + iVar1), uVar6 != 0xff)) {
    return (undefined4 *)(uVar6 * 0x40 + *(int *)(param_2 + 0xb8)); // Use indexed slot (0x40 = 64 bytes per entry)
  }
  return DAT_0120557c + iVar1 * 0x10; // Fallback to global table at offset iVar1 * 16 (0x10)
}