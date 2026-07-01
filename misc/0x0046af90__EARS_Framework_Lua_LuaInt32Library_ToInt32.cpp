// Xbox PDB: EARS::Framework::Lua::LuaInt32Library::ToInt32
// FUNC_NAME: DataVariant::toInt32

int DataVariant::toInt32(int index)
{
  int *pTypedValue;
  int result;
  char *strValue;
  int *pDefault;
  int localInt;
  int *pArrayElement;
  
  // First attempt: get as Int32 directly (e.g., from a dictionary lookup)
  pTypedValue = (int *)getValueByType(this, "Int32");
  if (pTypedValue != (int *)0x0) {
    return *pTypedValue;
  }
  
  // If index is negative (less than 1), try default processing
  if (index < 1) {
    pDefault = (int *)getDefaultObject(); // maybe global defaults
LAB_0046b025:
    if ((pDefault != (int *)0x0) && (*pDefault == 3)) { // check type tag
      loadDefault();
      result = getDefaultInt32(); // retrieve default int32 value
      return result;
    }
  }
  else {
    // Index >= 1: treat as array access on internal data
    pArrayElement = (int *)(*(int *)((char *)this + 0x0c) + -8 + index * 8);
    if (pArrayElement < *(int **)((char *)this + 0x08)) goto LAB_0046b025;
  }
  
  // Fall back to string conversion
  strValue = (char *)getStringValue();
  if (strValue == (char *)0x0) {
    initializeString();
    strValue = (char *)getStringValue();
    if (strValue != (char *)0x0) goto LAB_0046b000;
  }
  else {
LAB_0046b000:
    if (parseInt32(strValue, &localInt) != '\0') {
      return localInt;
    }
    if (strValue != (char *)0x0) goto LAB_0046b04c;
  }
  strValue = "<null>";
LAB_0046b04c:
  logError("Could not turn \'%s\' into an Int32.\n", strValue);
  __debugbreak(); // software interrupt 3
  return 0;
}