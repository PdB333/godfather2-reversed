// FUNC_NAME: SomeEntity::setSomeStringField
void __thiscall SomeEntity::setSomeStringField(int param_1, char *param_2)
{
  // Copy up to 0x20 (32) characters from input string into field at offset +0x208
  _strncpy((char *)(param_1 + 0x208), param_2, 0x20);
  return;
}