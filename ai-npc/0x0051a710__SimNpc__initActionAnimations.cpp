// FUNC_NAME: SimNpc::initActionAnimations
void __fastcall SimNpc::initActionAnimations(undefined4 param_1, int param_2)
{
  byte bVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  
  // Read action count from the animation data source at +0x10 offset, +0x1c field
  bVar1 = *(byte *)(*(int *)(param_2 + 0x10) + 0x1c);
  iVar6 = 0;
  // Store action count at +0x80 (ushort)
  *(ushort *)(param_2 + 0x80) = (ushort)bVar1;
  if (bVar1 != 0) {
    iVar5 = 0;
    // Start writing action animation data at +0xfc
    puVar4 = (undefined4 *)(param_2 + 0xfc);
    do {
      iVar2 = *(int *)(param_2 + 0x10);
      // Copy animation ID from source at +0x38 offset per action slot (0x24 stride)
      puVar4[-3] = *(undefined4 *)(iVar5 + 0x38 + iVar2);
      // Get animation data pointer from source at +0x30 offset per action slot
      puVar3 = *(undefined4 **)(iVar5 + 0x30 + iVar2);
      if (puVar3 == (undefined4 *)0x0) {
        // No animation data: clear fields
        puVar4[-1] = 0;
        *puVar4 = 0;
      }
      else {
        // Copy animation data: first word and pointer to data after first 3 words
        puVar4[-1] = *puVar3;
        *puVar4 = puVar3 + 3;
      }
      // Initialize remaining fields to 0
      puVar4[-2] = 0;
      puVar4[1] = 0;
      iVar6 = iVar6 + 1;
      puVar4 = puVar4 + 5;
      iVar5 = iVar5 + 0x24;
    } while (iVar6 < *(short *)(param_2 + 0x80));
  }
  return;
}