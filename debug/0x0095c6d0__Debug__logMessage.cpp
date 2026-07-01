// FUNC_NAME: Debug::logMessage
void __thiscall Debug::logMessage(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)*this;
  if (puVar1 == (undefined1 *)0x0) {
    puVar1 = &DAT_0120546e; // Default debug channel string
  }
  FUN_005c4660(param_2, puVar1, param_3, this[1]); // Call to underlying logging function
  return;
}