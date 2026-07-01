// FUNC_NAME: someModule::isPointerValid
bool isPointerValid(void* ptr)

{
  if (ptr != (void *)0x0) {
    return FUN_0043b870(DAT_0112ded0); // check pointer validity via some global state
  }
  return false;
}