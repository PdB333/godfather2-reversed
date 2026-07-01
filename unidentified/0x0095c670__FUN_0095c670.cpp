// FUNC_NAME: SomeClass::logMessageWithFormat
void __thiscall SomeClass::logMessageWithFormat(undefined4 *this, undefined4 param_2, undefined4 param_3)
{
  undefined1 *formatString;
  
  formatString = (undefined1 *)*this;
  if (formatString == (undefined1 *)0x0) {
    formatString = &DAT_0120546e; // Default format string (likely "%s" or empty)
  }
  FUN_005c4660(param_2, formatString, param_3, this[1]); // Likely a printf-style logging function
  return;
}