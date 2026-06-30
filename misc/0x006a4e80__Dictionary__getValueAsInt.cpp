// FUNC_NAME: Dictionary::getValueAsInt
bool __thiscall Dictionary::getValueAsInt(Dictionary *this, undefined4 param_2, int *outValue)
{
  int value;
  
  value = 0;
  if (FUN_004480d0(this, param_2, &value) != '\0') {
    *outValue = value;
    return true;
  }
  *outValue = 0;
  return false;
}