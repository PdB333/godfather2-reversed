// FUNC_NAME: InputManager::handleSpecialActionString
bool InputManager::handleSpecialActionString(byte *actionString)
{
  int cmpResult;
  byte *strPtr;
  byte *inputPtr;
  bool isEqual;
  
  // Check for left arrow hospital string
  cmpResult = 0x1f;
  isEqual = true;
  strPtr = (byte *)"/lmrk/lmrk/venues/l_arrow/hspt";
  inputPtr = actionString;
  do {
    if (cmpResult == 0) break;
    cmpResult = cmpResult + -1;
    isEqual = *strPtr == *inputPtr;
    strPtr = strPtr + 1;
    inputPtr = inputPtr + 1;
  } while (isEqual);
  if (isEqual) {
    FUN_005bf350(6); // Trigger left arrow hospital action
    return true;
  }
  
  // Check for right arrow hospital string
  cmpResult = 0x1f;
  isEqual = true;
  strPtr = (byte *)"/lmrk/lmrk/venues/r_arrow/hspt";
  inputPtr = actionString;
  do {
    if (cmpResult == 0) break;
    cmpResult = cmpResult + -1;
    isEqual = *strPtr == *inputPtr;
    strPtr = strPtr + 1;
    inputPtr = inputPtr + 1;
  } while (isEqual);
  strPtr = PTR_s__lmrk_lmrk_csa_button_1_button_00e573a0; // Pointer to "/lmrk/lmrk/csa/button_1/button"
  inputPtr = actionString;
  if (isEqual) {
    FUN_005bf350(7); // Trigger right arrow hospital action
    return true;
  }
  
  // Compare with button 1 string
  do {
    byte bVar1 = *strPtr;
    isEqual = bVar1 < *inputPtr;
    if (bVar1 != *inputPtr) {
LAB_00951090:
      cmpResult = (1 - (uint)isEqual) - (uint)(isEqual != 0);
      goto LAB_00951095;
    }
    if (bVar1 == 0) break;
    bVar1 = strPtr[1];
    isEqual = bVar1 < inputPtr[1];
    if (bVar1 != inputPtr[1]) goto LAB_00951090;
    strPtr = strPtr + 2;
    inputPtr = inputPtr + 2;
  } while (bVar1 != 0);
  cmpResult = 0;
LAB_00951095:
  strPtr = PTR_s__lmrk_lmrk_csa_button_2_button_00e573a4; // Pointer to "/lmrk/lmrk/csa/button_2/button"
  if (cmpResult == 0) {
    FUN_005bf350(10); // Trigger button 1 action
    return true;
  }
  
  // Compare with button 2 string
  do {
    byte bVar1 = *strPtr;
    isEqual = bVar1 < *actionString;
    if (bVar1 != *actionString) {
LAB_009510d4:
      cmpResult = (1 - (uint)isEqual) - (uint)(isEqual != 0);
      goto LAB_009510d9;
    }
    if (bVar1 == 0) break;
    bVar1 = strPtr[1];
    isEqual = bVar1 < actionString[1];
    if (bVar1 != actionString[1]) goto LAB_009510d4;
    actionString = actionString + 2;
    strPtr = strPtr + 2;
  } while (bVar1 != 0);
  cmpResult = 0;
LAB_009510d9:
  if (cmpResult == 0) {
    FUN_005bf350(0xd); // Trigger button 2 action
  }
  return cmpResult == 0;
}