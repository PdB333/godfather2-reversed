// FUNC_NAME: setRenderDebugFlag
// Sets debug rendering flags in the global game state bitfield.
// 0x40000 = disable something, 0x80000 = enable something (or vice versa)
void setRenderDebugFlag(char param_1)
{
  if (param_1 != '\0') {
    DAT_01130590 = DAT_01130590 | 0x80000;
    return;
  }
  DAT_01130590 = DAT_01130590 | 0x40000;
  return;
}