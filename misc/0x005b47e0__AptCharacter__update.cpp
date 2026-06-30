// FUNC_NAME: AptCharacter::update
void AptCharacter::update(int param_1, int param_2)
{
  // Check state field at offset 0x0 (first int in object)
  if (*(int*)this == 1) {
    // Check field at offset +0x18 (6th int)
    if (*(int*)((char*)this + 0x18) == 0) {
      FUN_0059bf00(); // likely some initialization or state transition
    }
    // Call function pointer stored at global DAT_0119cb70 with the object's field at +0x18
    (*(void (__thiscall**)(int, int, int))DAT_0119cb70)(*(int*)((char*)this + 0x18), param_1, param_2);
  }
  else if (*(int*)this != 0xb) {
    // Assertion failure: unexpected state
    FUN_0059bf00(&DAT_00e36da0, "..\\source\\Apt\\AptCharacter.cpp", 0x13e, 2, &DAT_01129121);
    return;
  }
  return;
}