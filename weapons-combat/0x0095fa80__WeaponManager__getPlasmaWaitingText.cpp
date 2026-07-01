// FUNC_NAME: WeaponManager::getPlasmaWaitingText
void __thiscall WeaponManager::getPlasmaWaitingText(int this, char *outBuffer)
{
  char *str;
  char *local_10;
  int local_c;
  int local_8;
  void *local_4;
  
  FUN_0095ecd0(); // likely some thread safety / lock
  *outBuffer = 0;
  if (DAT_011307fc == 0) {
    // No plasma weapon available
    FUN_005c4660(outBuffer, "$fe_plasma_waiting", 0x80, 0); // format string into buffer
  }
  else if (*(uint *)(this + 8) < DAT_011307fc) {
    // There is a plasma weapon slot, get the name
    local_10 = (char *)0x0;
    local_c = 0;
    local_8 = 0;
    local_4 = (void *)0x0;
    // +0x8 is current plasma weapon index
    // DAT_011307f8 is pointer to plasma weapon name table (array of 8-byte entries)
    FUN_00603330(*(undefined4 *)(DAT_011307f8 + *(uint *)(this + 8) * 8), &local_10);
    str = local_10;
    if (local_10 == (char *)0x0) {
      str = &DAT_0120546e; // empty string fallback
    }
    FUN_005c4660(outBuffer, str, 0x80, local_c);
    if (local_10 != (char *)0x0) {
      (*local_4)(local_10); // free the allocated string
      return;
    }
  }
  return;
}