// FUNC_NAME: parseFloatWithExponent
void parseFloatWithExponent(void)
{
  char cVar1;
  bool bVar2;
  char *in_EAX;
  int iVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int _C;
  
  iVar3 = _isspace((int)*in_EAX);
  while (iVar3 != 0) {
    pcVar6 = in_EAX + 1;
    in_EAX = in_EAX + 1;
    iVar3 = _isspace((int)*pcVar6);
  }
  iVar3 = 1;
  bVar2 = true;
  if (*in_EAX != '+') {
    if (*in_EAX != '-') goto LAB_005c72c4;
    bVar2 = false;
  }
  in_EAX = in_EAX + 1;
LAB_005c72c4:
  iVar4 = _isdigit((int)*in_EAX);
  while (iVar4 != 0) {
    pcVar6 = in_EAX + 1;
    in_EAX = in_EAX + 1;
    iVar4 = _isdigit((int)*pcVar6);
  }
  if (*in_EAX == '.') {
    iVar4 = _isdigit((int)in_EAX[1]);
    for (pcVar6 = &DAT_00e3ea28; (in_EAX = in_EAX + 1, iVar4 != 0 && (pcVar6 <= "#_animate="));
        pcVar6 = pcVar6 + 4) {
      iVar4 = _isdigit((int)in_EAX[1]);
    }
  }
  iVar4 = _isdigit((int)*in_EAX);
  while (iVar4 != 0) {
    pcVar6 = in_EAX + 1;
    in_EAX = in_EAX + 1;
    iVar4 = _isdigit((int)*pcVar6);
  }
  iVar4 = _tolower((int)*in_EAX);
  if (iVar4 == 0x65) {
    cVar1 = in_EAX[1];
    pcVar6 = in_EAX + 1;
    iVar4 = _isdigit((int)cVar1);
    if (iVar4 == 0) {
      if (cVar1 == 0x2d) {
        iVar3 = -1;
      }
      pcVar6 = in_EAX + 2;
    }
    _C = (int)*pcVar6;
    iVar4 = 0;
    iVar5 = _isdigit(_C);
    while (iVar5 != 0) {
      iVar4 = _C + -0x30 + iVar4 * 10;
      _C = (int)pcVar6[1];
      pcVar6 = pcVar6 + 1;
      iVar5 = _isdigit(_C);
    }
    if (iVar3 == -1) {
      iVar4 = -iVar4;
    }
    if (7 < -iVar4) {
      iVar3 = (-iVar4 - 8U >> 3) + 1;
      iVar4 = iVar4 + iVar3 * 8;
      do {
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if (iVar4 < 0) {
      iVar3 = -iVar4;
      iVar4 = 0;
      do {
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    if (7 < iVar4) {
      iVar3 = (iVar4 - 8U >> 3) + 1;
      iVar4 = iVar4 + iVar3 * -8;
      do {
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    for (; 0 < iVar4; iVar4 = iVar4 + -1) {
    }
  }
  if (bVar2) {
    return;
  }
  return;
}