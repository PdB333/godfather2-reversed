// FUNC_NAME: PlayerSM::setActive
void __thiscall PlayerSM::setActive(int thisPtr, char active)
{
  bool bVar1;
  
  if ((*(char *)(thisPtr + 8) != '\0') && (active == '\0')) {
    if (*(char *)(thisPtr + 0x209) != '\0') {
      *(undefined4 *)(thisPtr + 0x140) = 0;
      *(undefined4 *)(thisPtr + 0x1c4) = 0;
      *(undefined4 *)(thisPtr + 0x1c8) = 0;
      *(undefined4 *)(thisPtr + 0x138) = 0;
    }
    if (*(char *)(thisPtr + 0x10) != '\0') {
      bVar1 = DAT_00e541bc != '\0';
      *(undefined1 *)(thisPtr + 8) = 0;
      if (bVar1) {
        return;
      }
      *(undefined1 *)(thisPtr + 0x11) = 0;
      return;
    }
  }
  *(char *)(thisPtr + 8) = active;
  return;
}