// FUNC_NAME: AudioManager::updateVolumeRamp
void __thiscall AudioManager::updateVolumeRamp(int this, int param_2, int param_3, float param_4)
{
  undefined8 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  float local_24;
  undefined4 local_1c;
  int local_c;
  
  iVar4 = param_2 * 0x30 + *(int *)(this + 0x58); // +0x58: audioChannelArray
  uVar2 = DAT_010c2678 & DAT_012054b4;
  DAT_012054b4 = DAT_012054b4 + 1;
  local_24 = (*(float *)(iVar4 + 0x20) - *(float *)(iVar4 + 0x1c)) *
             *(float *)(&DAT_010c2680 + uVar2 * 4) + *(float *)(iVar4 + 0x1c);
  if (param_4 <= DAT_00e44598) goto LAB_006a4413;
  uVar1 = *(undefined8 *)(param_3 + 8);
  local_1c = (undefined4)(longlong)ROUND(local_24 * param_4);
  FUN_00826410(0,0,0,0,local_1c);
  iVar3 = *(int *)(iVar4 + 0x14);
  local_c = (int)uVar1;
  if (*(int *)(iVar4 + 0x18) < iVar3) {
    if (iVar3 <= local_c) goto LAB_006a4413;
LAB_006a43e6:
    if (local_c <= *(int *)(iVar4 + 0x18)) goto LAB_006a4413;
    if (local_c < iVar3) goto LAB_006a43ee;
    iVar3 = (iVar3 - local_c) + 0x18;
  }
  else {
    if (iVar3 <= local_c) goto LAB_006a43e6;
LAB_006a43ee:
    iVar3 = iVar3 - local_c;
  }
  local_24 = ((float)(iVar3 * 0xe10) + local_24 * param_4) / param_4;
LAB_006a4413:
  FUN_00440590(&DAT_0112a534,this + 0x3c,local_24,iVar4 + 0x24,5);
  *(undefined1 *)(iVar4 + 0x2c) = 1;
  return;
}