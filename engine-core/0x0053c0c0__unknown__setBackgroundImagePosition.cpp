// FUNC_NAME: unknown::setBackgroundImagePosition
void __cdecl setBackgroundImagePosition(void)
{
  undefined1 *imagePtr;
  int someFlag;
  uint ESI_value;
  undefined4 local_x;
  undefined4 local_y;
  float scaleX;
  float scaleY;
  
  DAT_01125b80 = ESI_value;
  if (DAT_01125ab4 == DAT_01125b44) {
    someFlag = DAT_01125b84;
    if (DAT_01125b4c != 0) {
      FUN_006063b0(); // likely some initialization/reset function
      someFlag = DAT_01125b84;
    }
  }
  else {
    someFlag = DAT_01125b88;
    if (DAT_01125b60 != 0) {
      FUN_006063b0(); // likely some initialization/reset function
      someFlag = DAT_01125b88;
    }
  }
  if (someFlag != 0) {
    local_x = 0;
    local_y = 0;
    if (ESI_value < 0x1000) {
      imagePtr = &DAT_011a0f28 + ESI_value * 0x38; // +0x38 size per entry, likely an array of image descriptors
    }
    else {
      imagePtr = (undefined1 *)0x0;
    }
    scaleX = DAT_00e2cd54 / (float)*(ushort *)(imagePtr + 2); // +0x2 = original width
    if (ESI_value < 0x1000) {
      imagePtr = &DAT_011a0f28 + ESI_value * 0x38;
    }
    else {
      imagePtr = (undefined1 *)0x0;
    }
    scaleY = DAT_00e2cd54 / (float)*(ushort *)(imagePtr + 4); // +0x4 = original height
    FUN_0060add0(DAT_01125ab4, someFlag, &local_x); // likely sets position with scaling
  }
  return;
}