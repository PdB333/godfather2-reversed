// FUNC_NAME: AudioSystem::buildPluginChain
undefined1 FUN_005ee090(int param_1)
{
  int iVar1;
  undefined1 uVar2;
  undefined4 *in_EAX;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int *piVar6;
  int local_4;
  
  uVar2 = 0;
  uVar3 = FUN_004dafd0("ST_PLUGINCHAIN");
  *in_EAX = uVar3;
  FUN_004d3d90("ST_PLUGINCHAIN");
  puVar4 = in_EAX + 0x10;
  iVar5 = 5;
  do {
    *puVar4 = *in_EAX;
    puVar4 = puVar4 + 0xc;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  piVar6 = in_EAX + 10;
  local_4 = 5;
  do {
    if ((((piVar6[-5] == 0) && (*(int *)(param_1 + 0x580) != 0)) && (*(int *)(param_1 + 0x56c) != 0)
        ) && (piVar6[2] == 0x10)) {
      FUN_00c9eac0();
      FUN_005e9ba0("SndPlayer");
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x536e5031);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 6;
      FUN_005e9ba0("Rechannel");
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x52636830);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 1;
      FUN_005e9ba0("Resample");
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x52737030);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 1;
      FUN_005e9ba0("LoPass");
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x4c493230);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 1;
      FUN_005e9ba0("MatrixPanner");
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x4d745030);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 6;
      FUN_005e9ba0(&DAT_00e3f858);
      iVar5 = piVar6[1];
      iVar1 = *piVar6;
      uVar3 = FUN_00c9cd50(0x53656e30);
      *(undefined4 *)(iVar1 + iVar5 * 0xc + -8) = uVar3;
      *(undefined4 *)(*piVar6 + -0xc + piVar6[1] * 0xc) = 0;
      *(undefined1 *)(*piVar6 + -4 + piVar6[1] * 0xc) = 6;
      iVar5 = FUN_00ca55a0(*(undefined4 *)(param_1 + 0x580),0,piVar6[1],*piVar6,0);
      piVar6[-5] = iVar5;
      piVar6[-4] = iVar5 + 0x50;
      uVar2 = 1;
      FUN_00c9eae0();
    }
    piVar6 = piVar6 + 0xc;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  return uVar2;
}