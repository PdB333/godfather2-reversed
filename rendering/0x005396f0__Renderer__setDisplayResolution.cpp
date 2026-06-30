// FUNC_NAME: Renderer::setDisplayResolution
void __fastcall Renderer::setDisplayResolution(uint param_1)
{
  int in_EAX;
  undefined1 *puVar1;
  undefined4 local_20;
  undefined4 local_1c;
  float local_18;
  float local_14;
  
  DAT_0121b824 = param_1; // Current width selection index
  DAT_0121b828 = in_EAX; // Current height selection index
  if ((DAT_012058e8 == &DAT_0121b740) && (DAT_0121b754 == DAT_0121bbb8)) {
    if (DAT_0121b9cc != 0) { // Fullscreen mode
      FUN_006063b0(); // applyFullscreenMode
    }
    if (DAT_0121b9d0 != 0) { // Windowed mode
      FUN_006063b0(); // applyWindowedMode
    }
    if (DAT_0121b9e4 != 0) { // Width resolution change pending
      local_20 = 0;
      local_1c = 0;
      if (DAT_0121b824 < 0x1000) { // Valid width index
        puVar1 = &DAT_011a0f28 + DAT_0121b824 * 0x38; // Resolution table entry
      }
      else {
        puVar1 = (undefined1 *)0x0;
      }
      local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 2); // Aspect ratio width
      if (DAT_0121b824 < 0x1000) {
        puVar1 = &DAT_011a0f28 + DAT_0121b824 * 0x38;
      }
      else {
        puVar1 = (undefined1 *)0x0;
      }
      local_14 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 4); // Aspect ratio height
      FUN_0060add0(DAT_0121b754,DAT_0121b9e4,&local_20); // setResolution
    }
    if (DAT_0121b9a8 != 0) { // Height resolution change pending
      local_20 = 0;
      local_1c = 0;
      if (DAT_0121b828 < 0x1000) {
        puVar1 = &DAT_011a0f28 + DAT_0121b828 * 0x38;
      }
      else {
        puVar1 = (undefined1 *)0x0;
      }
      local_18 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 2);
      if (DAT_0121b828 < 0x1000) {
        puVar1 = &DAT_011a0f28 + DAT_0121b828 * 0x38;
      }
      else {
        puVar1 = (undefined1 *)0x0;
      }
      local_14 = DAT_00e2cd54 / (float)*(ushort *)(puVar1 + 4);
      FUN_0060add0(DAT_0121b754,DAT_0121b9a8,&local_20);
    }
  }
  return;
}