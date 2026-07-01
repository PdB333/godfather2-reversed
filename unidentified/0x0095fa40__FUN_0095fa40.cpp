// FUNC_NAME: SomeClass::buildRecognitionString
void __thiscall SomeClass::buildRecognitionString(int this, undefined4 param_2)
{
  undefined4 *puVar1;
  undefined1 *puVar2;
  
  FUN_0095ecd0();
  puVar1 = (undefined4 *)(*(int *)(this + 0x28) * 0x10 + DAT_01130828); // +0x28: index into a 0x10-sized table at DAT_01130828
  puVar2 = (undefined1 *)*puVar1;
  if (puVar2 == (undefined1 *)0x0) {
    puVar2 = &DAT_0120546e; // Fallback string constant
  }
  FUN_005c4660(param_2, puVar2, 0x80, puVar1[1]); // Copy up to 0x80 bytes from source to destination
  return;
}