// FUNC_NAME: ContextManager::processContextUpdate
uint __thiscall ContextManager::processContextUpdate(void *this, uint inputContext, uint flags, uint extraData)
{
  char tempFlag;
  uint stateVal;
  int stateOffset;
  uint result;
  
  // Base processing of the context input
  result = baseProcess(inputContext, flags, extraData);
  
  // Check if the lowest bit of flags indicates a special condition
  stateVal = checkFlag(flags & 1);
  if (stateVal != 0) {
    stateVal = updateContext(extraData, (uint *)((int)this + 0x254)); // this+0x254 is context data pointer
  }
  
  // Evaluate state based on flags and internal state
  if ((((flags & 0x10) == 0) || (stateVal = *(uint *)((int)this + 0x1bc), stateVal == 0)) ||
      (stateVal = stateVal - 0x48, stateVal == 0)) {
    stateVal = stateVal & 0xffffff00;
  }
  else {
    stateVal = CONCAT31((int3)(stateVal >> 8), 1); // Set bit 24 as a flag
  }
  
  tempFlag = checkFlag(stateVal);
  if (tempFlag != '\0') {
    stateOffset = *(int *)((int)this + 0x1bc); // +0x1bc: state enum
    if ((stateOffset == 0) || (stateOffset == 0x48)) {
      stateOffset = 0;
    }
    else {
      stateOffset = stateOffset + 0x10;
    }
    tempFlag = checkStateValid(stateOffset);
    if (tempFlag != '\0') {
      stateOffset = *(int *)((int)this + 0x1bc);
      if ((stateOffset == 0) || (stateOffset == 0x48)) {
        stateOffset = 0;
      }
      else {
        stateOffset = stateOffset + 0x10;
      }
      cleanupState(stateOffset);
      storeContextResult(extraData, (undefined1 (*) [8])contextBuffer);
      return result;
    }
    result = result | 0x10;
  }
  return result;
}