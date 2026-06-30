// FUNC_NAME: ColorPicker::applyColorToVehicle
undefined4 FUN_005bb730(void)

{
  int iVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  
  FUN_005a0d00(0); // some init or reset
  iVar1 = FUN_005a7950(); // get current vehicle/entity
  iVar1 = *(int *)(iVar1 + 0x4c); // +0x4c: vehicle paint component
  if (iVar1 != 0) {
    uVar2 = FUN_005a8fe0(); // get color from UI/input (RGB packed as 0x00RRGGBB)
    fVar3 = (float)((int)uVar2 >> 0x10 & 0xff); // red channel
    fVar4 = (float)((int)uVar2 >> 8 & 0xff); // green channel
    FUN_005b5d20(); // begin paint update
    *(undefined1 *)(iVar1 + 100) = 0; // +0x64: paint state flag (0 = updating)
    *(float *)(*(int *)(iVar1 + 0x50) + 0x20) = fVar3; // +0x50: color struct ptr, +0x20: red
    *(float *)(iVar1 + 0x24) = fVar3 * DAT_00e44640; // +0x24: scaled red (DAT = 1/255.0f)
    FUN_005b5d20(); // commit paint update
    *(undefined1 *)(iVar1 + 100) = 0;
    *(float *)(*(int *)(iVar1 + 0x50) + 0x24) = fVar4; // +0x24: green
    *(float *)(iVar1 + 0x28) = fVar4 * DAT_00e44640; // +0x28: scaled green
    FUN_005b5d20();
    *(float *)(*(int *)(iVar1 + 0x50) + 0x28) = (float)(uVar2 & 0xff); // blue channel
    *(float *)(iVar1 + 0x2c) = (float)(uVar2 & 0xff) * DAT_00e44640; // +0x2c: scaled blue
    *(undefined4 *)(iVar1 + 0x14) = 0; // +0x14: clear some vector
    *(undefined4 *)(iVar1 + 0x18) = 0;
    *(undefined4 *)(iVar1 + 0x1c) = 0;
    *(undefined1 *)(iVar1 + 100) = 1; // +0x64: paint state flag (1 = done)
  }
  return DAT_0119cbbc; // return value (likely success/failure)
}