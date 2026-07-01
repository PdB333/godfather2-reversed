// FUNC_NAME: SomeClass::resetOrConstructor
void __fastcall SomeClass::resetOrConstructor(int this)
{
  FUN_008d5dd0(); // likely clears or resets a sub-object at offset 0x00
  FUN_008d5dd0(); // likely clears or resets a sub-object at offset 0x?? 
  FUN_008d5dd0(); // likely clears or resets a sub-object at offset 0x??
  FUN_008d5dd0(); // likely clears or resets a sub-object at offset 0x??
  *(undefined4 *)(this + 0x78) = 0; // +0x78: some integer field, set to 0
  return;
}