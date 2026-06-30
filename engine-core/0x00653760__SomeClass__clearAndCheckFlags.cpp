// FUNC_NAME: SomeClass::clearAndCheckFlags
void __fastcall SomeClass::clearAndCheckFlags(undefined4 param_1)
{
  char cVar1;
  undefined1 *in_EAX;
  int unaff_ESI; // this pointer
  undefined4 unaff_EDI; // some object pointer
  undefined4 local_4;

  // Save old value at +0xF4, then clear it
  *in_EAX = *(undefined1 *)(unaff_ESI + 0xf4);
  *(undefined1 *)(unaff_ESI + 0xf4) = 0;

  // Check if the old value is valid via some function
  cVar1 = FUN_0064bb50(*in_EAX);
  if (cVar1 != '\0') {
    // Build a new value from param_1 and a field at +0xB8
    local_4._1_3_ = (undefined3)((uint)param_1 >> 8);
    local_4 = CONCAT31(local_4._1_3_,(char)(*(uint *)(unaff_ESI + 0xb8) >> 2)) & 0xffffff01;
    
    // Check if the new value is valid
    cVar1 = FUN_0064bb50(local_4);
    if (cVar1 == '\0') {
      // If not valid, clear four fields at +0xD4, +0xD8, +0xDC, +0xE0
      FUN_006527e0(unaff_EDI,*(undefined4 *)(unaff_ESI + 0xe0));
      FUN_006527e0(unaff_EDI,*(undefined4 *)(unaff_ESI + 0xdc));
      FUN_006527e0(unaff_EDI,*(undefined4 *)(unaff_ESI + 0xd8));
      FUN_006527e0(unaff_EDI,*(undefined4 *)(unaff_ESI + 0xd4));
    }
  }
  return;
}