// FUNC_NAME: SomeClass::checkBounds
int __fastcall checkBounds(int this, int *outX, int mode, int maxX, int maxY)
{
  int x;
  int y;
  int *esi = (int *)this; // unaff_ESI likely points to this or a member

  switch(mode) {
  case 1:
    y = *(int *)(this + 0x10) + 1 + *(int *)(this + 8);
    goto LAB_005ce833;
  case 2:
    y = *(int *)(this + 0x14);
    x = *(int *)(this + 0xc);
    *outX = 1;
    *esi = y + 1 + x;
    break;
  case 3:
    y = *(int *)(this + 8);
    x = *(int *)(this + 0x14);
    int z = *(int *)(this + 0xc);
    *outX = y;
    *esi = x + 1 + z;
    if (y == 1) {
      return 0;
    }
    break;
  case 4:
    y = *(int *)(this + 8);
LAB_005ce833:
    *esi = *(int *)(this + 0xc);
    *outX = y;
  }
  if ((*outX + maxX <= DAT_012056b4) && (*esi + maxY <= DAT_012056b8)) {
    return 1;
  }
  return 0;
}