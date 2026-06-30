// FUNC_NAME: SomeClass::createTwoSubComponents
void __thiscall SomeClass::createTwoSubComponents(int arg)
{
  int sizes[2]; // array of two sizes
  sizes[0] = 0xb8; // size of first subcomponent (184 bytes)
  sizes[1] = 0xa8; // size of second subcomponent (168 bytes)
  // call into the engine to create two subcomponents with given sizes
  // The called function likely allocates memory and initializes subcomponents
  FUN_004eba90(this, arg, sizes, 2);
  return;
}