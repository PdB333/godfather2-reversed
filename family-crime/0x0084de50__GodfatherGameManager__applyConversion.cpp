// FUNC_NAME: GodfatherGameManager::applyConversion
void GodfatherGameManager::applyConversion(void)

{
  int conversionResult;
  undefined1 someBuffer [4];
  int somePointer1 [2];
  int somePointer2 [15];
  
  conversionResult = getConversionResult(); // FUN_004a8f00 - likely returns status/pointer
  if (conversionResult != 0) {
    conversionResult = getConversionResult();
    if (conversionResult == 0) {
      conversionResult = 0;
    }
    else {
      conversionResult = conversionResult + -0x58; // offset -0x58 from structure
    }
    updateConversionState(); // FUN_0084dd20
    initConversionWorkspace(&stack0x0000000c); // FUN_0084d760
    if (conversionResult == 0) {
      conversionResult = 0;
    }
    else {
      conversionResult = conversionResult + 0x3c; // offset +0x3c from structure
    }
    loadConversionData(&DAT_0112dd94,conversionResult,someBuffer,0); // FUN_00408bb0
    if (somePointer2[0] != 0) {
      releaseConversionResource(somePointer2); // FUN_004daf90
    }
    if (somePointer1[0] != 0) {
      releaseConversionResource(somePointer1);
    }
  }
  return;
}