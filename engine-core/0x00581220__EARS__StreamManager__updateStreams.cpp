// FUNC_NAME: EARS::StreamManager::updateStreams
void EARS::StreamManager::updateStreams(undefined4 *param_1)

{
  uint uVar1;
  uint *puVar2;
  int unaff_EDI;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar1 = **(uint **)(unaff_EDI + 0x68);  // +0x68: stream state flags pointer
  if ((uVar1 & 0x10) == 0) {
    if (((uVar1 & 0x20) == 0) || ((short)(*(uint **)(unaff_EDI + 0x68))[1] < 1)) {
      param_1[3] = DAT_00e2b1a4;  // default stream priority
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
    else if ((uVar1 & 0x200) == 0) {
      FUN_00589450(param_1,*(int *)(unaff_EDI + 0x1c),*(int *)(unaff_EDI + 0x1c) + 1);  // +0x1c: stream buffer pointer
    }
    else {
      FUN_00589360(param_1,*(int *)(unaff_EDI + 0xc),*(int *)(unaff_EDI + 0xc) + 1);  // +0x0c: alternate stream buffer
    }
  }
  else {
    FUN_00589a90(*(int *)(unaff_EDI + 0x24) + 1);  // +0x24: stream index
  }
  uVar1 = **(uint **)(unaff_EDI + 0x68);
  if ((uVar1 & 0x40) == 0) {
    if ((char)uVar1 < '\\0') {
      FUN_00589ef0(*(int *)(unaff_EDI + 0x44),*(int *)(unaff_EDI + 0x44) + 1);  // +0x44: secondary stream buffer
    }
    else if ((uVar1 & 0x100) == 0) {
      FUN_0058a290();  // default stream update
    }
    else {
      FUN_00589bf0(*(int *)(unaff_EDI + 0x34),*(int *)(unaff_EDI + 0x34) + 1);  // +0x34: tertiary stream buffer
    }
  }
  else {
    FUN_0058a1f0();  // stream cleanup
  }
  puVar2 = *(uint **)(unaff_EDI + 0x68);
  param_1[4] = local_c;
  param_1[5] = local_8;
  param_1[6] = local_4;
  param_1[7] = DAT_00e2b1a4;
  if ((*puVar2 & 0x800) != 0) {
    FUN_0058a330(*(int *)(unaff_EDI + 100),*(int *)(unaff_EDI + 100) + 1);  // +0x64: final stream buffer
  }
  *(int *)(unaff_EDI + 0x68) = *(int *)(unaff_EDI + 0x68) + 8;  // advance stream state pointer
  return;
}