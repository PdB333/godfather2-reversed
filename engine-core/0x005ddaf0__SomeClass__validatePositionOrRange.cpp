// FUNC_NAME: SomeClass::validatePositionOrRange
undefined4 __thiscall SomeClass::validatePositionOrRange(float *this, undefined4 param_2)
{
  undefined4 in_EAX;
  int iVar1;
  float *unaff_ESI;
  
  iVar1 = FUN_005dc670(in_EAX);
  if (iVar1 != 0) {
    FUN_005dd8a0(param_2, unaff_ESI);
    if (((0.0 <= *unaff_ESI) && (*unaff_ESI <= DAT_00e2b1a4)) && (0.0 <= *this)) {
      return 1;
    }
  }
  return 0;
}