// FUNC_NAME: AudioSystem::processSamples
void AudioSystem::processSamples(int param_1, int param_2, int param_3, int param_4, int param_5)
{
  int uVar1;
  char cVar2;
  int iVar3;
  uint *puVar4;
  uint *puVar5;
  uint local_40 [15];
  
  uVar1 = param_4;
  cVar2 = FUN_006073e0(&param_1, &param_2, &param_3, param_4, param_5);
  if (cVar2 != '\0') {
    if (((char)uVar1 == '\0') && (1 < (int)DAT_00f15a70)) {
      local_40[0] = local_40[0] / DAT_00f15a70;
      local_40[1] = local_40[1] / DAT_00f15a70;
    }
    puVar4 = local_40;
    puVar5 = &DAT_011d9188;
    for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    FUN_00607730(param_3, uVar1, param_5);
  }
  return;
}