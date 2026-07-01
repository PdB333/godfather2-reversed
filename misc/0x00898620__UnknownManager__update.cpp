// FUNC_NAME: UnknownManager::update
void __fastcall UnknownManager::update(void *this)
{
  char isEnabled;

  isEnabled = checkCondition(); // FUN_00481620 - e.g., isActive() or isEnabled()
  if (isEnabled != '\0') {
    processObject(*(undefined4 *)((int)this + 0x10c)); // +0x10c: pointer to some object/data
  }
  postUpdate(); // FUN_008b5610 - global tick or finalize step
  return;
}