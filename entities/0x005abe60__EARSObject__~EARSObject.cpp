// FUNC_NAME: EARSObject::~EARSObject
void EARS::~EARSObject(void)
{
  undefined4 in_EAX;
  int thisPtr; // unaff_EDI
  undefined1 *local_14;
  undefined1 local_10 [16];
  
  FUN_005a0a00(in_EAX); // likely base class destructor call
  FUN_005a1060(); // likely member cleanup
  if ((local_14 != local_10) && (local_14 != (undefined1 *)0x0)) {
    (*DAT_0119caf4)(local_14); // free/delete call via function pointer
  }
  *(undefined4 *)(thisPtr + 0x20) = 0xbeefceec; // magic number sentinel for debugging
  return;
}