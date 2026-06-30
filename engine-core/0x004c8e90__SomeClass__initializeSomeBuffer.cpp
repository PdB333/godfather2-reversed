// FUNC_NAME: SomeClass::initializeSomeBuffer
void __fastcall SomeClass::initializeSomeBuffer(int param_1)
{
  int in_EAX;
  int unaff_ESI;
  
  if ((in_EAX != 0) && (param_1 == *(int *)(unaff_ESI + 0xc))) {
    *(int *)(unaff_ESI + 0x290) = in_EAX;
    FUN_004d9a70(in_EAX);
    FUN_005dbe70();
    *(undefined4 *)(unaff_ESI + 0x2b0) = 0;
    *(undefined4 *)(unaff_ESI + 0x2b4) = 0xbadbadba;
    *(undefined4 *)(unaff_ESI + 0x2b8) = 0xbeefbeef;
    *(undefined4 *)(unaff_ESI + 700) = 0xeac15a55;
    *(undefined4 *)(unaff_ESI + 0x2c0) = 0x91100911;
    *(undefined1 *)(unaff_ESI + 0x2c4) = 0;
  }
  return;
}