// FUNC_NAME: ConfigValue::parseBool
undefined4 ConfigValue::parseBool(int this, undefined1 *outValue)

{
  int iVar1;
  
  if (*(int *)(this + 4) != 0) {
    iVar1 = FUN_004d4b70(&DAT_00e36d8c);  // Compare with "true" string
    if (iVar1 == 0) {
      *outValue = 1;  // Set to true
      return 1;       // Success
    }
    iVar1 = FUN_004d4b70("false");  // Compare with "false" string
    if (iVar1 == 0) {
      *outValue = 0;  // Set to false
      return 1;       // Success
    }
  }
  return 0;  // Failed to parse (not a valid bool string or null value)
}