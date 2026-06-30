// FUNC_NAME: EARSString::assign
undefined1 __thiscall EARSString::assign(uint *this, short *pSource, uint *pHandle1, uint *pHandle2)
{
  short *psSrcIter;
  int iSrcLength;
  short sCh;
  uint uNewBuffer;
  uint uResult;
  undefined1 bSuccess;
  uint uTemp;
  int iBuffer;
  undefined1 bLocalResult;
  int iDestructorArg;
  code *pDestructor;
  
  bLocalResult = 0;
  // Avoid self-assignment? If this equals one of the handles, we need to handle differently
  if ((this != pHandle1) && (this != pHandle2)) {
    // Release previous handle1 contents
    if (*pHandle1 != 0) {
      (*(code *)pHandle1[3])(*pHandle1);  // Call destructor on the object pointed to by handle
    }
    pHandle1[0] = 0;  // Clear pointer
    pHandle1[2] = 0;  // Clear field at +0x08
    pHandle1[1] = 0;  // Clear field at +0x04

    // Release previous handle2 contents
    if (*pHandle2 != 0) {
      (*(code *)pHandle2[3])(*pHandle2);  // Call destructor
    }
    pHandle2[0] = 0;
    pHandle2[2] = 0;
    pHandle2[1] = 0;

    // If this buffer has capacity
    if (this[1] != 0) {
      uResult = FUN_004dc860();  // Allocate new buffer from global pool
      if (uResult != 0) {
        uNewBuffer = this[0];  // Original buffer pointer
        if (uNewBuffer < uResult) {
          // Zero out the extra space? (uResult - uNewBuffer)/2 shorts
          FUN_004dbb10(uNewBuffer,0,(int)(uResult - uNewBuffer) >> 1);
        }
        // Count length of source wide string (assume null-terminated)
        psSrcIter = pSource + 1;  // Skip first short? Possibly a BOM or length prefix?
        do {
          sCh = *pSource;
          pSource = pSource + 1;
        } while (sCh != 0);
        iSrcLength = ((int)pSource - (int)psSrcIter) >> 1;  // Number of shorts after first element?
        // Check if destination buffer already contains data at the computed offset
        iBuffer = uResult + iSrcLength * 2;
        if (*(short *)(uResult + iSrcLength * 2) != 0) {
          // Clear from that offset to end of this buffer
          FUN_004dbb10(iBuffer,0,this[1] - ((int)(iBuffer - this[0]) >> 1));
        }
        bLocalResult = 1;  // Success
      }
    }
    return bLocalResult;
  }
  // Self-assignment case: copy this buffer to temporary handles, then reassign
  FUN_004dba00(*this, this[1]);  // Copy buffer contents to handle1/handle2?
  uResult = FUN_004dcc60(pSource, pHandle1, pHandle2);  // Recursive call with source as new 'this'
  if (iDestructorArg != 0) {
    (*pDestructor)(iDestructorArg);  // Cleanup temporary
  }
  return uResult;
}