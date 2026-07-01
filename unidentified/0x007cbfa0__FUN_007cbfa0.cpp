// FUNC_NAME: UnknownClass::handleInputAction
void __thiscall UnknownClass::handleInputAction(int this, uint actionFlags, undefined4 param3)
{
  char cVar1;
  int iVar2;
  
  if ((actionFlags & 0x60000) == 0) {
    if (*(int *)(this + 0x1b0) != 0) {
      FUN_007cb510(0);
      return;
    }
  }
  else {
    *(undefined4 *)(this + 0x1e4) = 0x41;
    *(undefined4 *)(this + 0x1e8) = 0;
    if (actionFlags != 0) {
      cVar1 = FUN_007f7c50();
      if (cVar1 != '\0') {
        if (*(int *)(this + 0x1b4) == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(this + 0x1b4) + -0x48;
        }
        if (*(char *)(iVar2 + 0x1b8c) == '\0') {
          actionFlags = actionFlags & 0xfffffc5f | 0x40;
        }
      }
      *(uint *)(this + 0x1e4) = actionFlags;
      *(undefined4 *)(this + 0x1e8) = param3;
    }
  }
  return;
}