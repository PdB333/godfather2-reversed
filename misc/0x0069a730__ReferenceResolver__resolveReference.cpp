// FUNC_NAME: ReferenceResolver::resolveReference
undefined4 * __thiscall ReferenceResolver::resolveReference(int thisPtr, undefined4 *output, int *inputPtr, uint flags)
{
  uint originalFlags;
  int *tempPtr;
  int validationResult;
  undefined4 *alignedResult;
  byte localBuffer[8]; // unused buffer for alignment call

  originalFlags = flags;
  // Check if inputPtr is the same as the stored pointer at +0x4 or the address of that field
  if ((inputPtr == *(int **)(thisPtr + 4)) || (inputPtr == (int *)(thisPtr + 4))) {
    // If there is a count/limit at +0x14 and validation of flags fails
    if ((*(int *)(thisPtr + 0x14) != 0) && (validationResult = FUN_004d4b20(flags), validationResult < 0)) {
      // Copy from stored pointer with invalid flag
      FUN_00699df0(output, *(int *)(thisPtr + 4), flags, 0);
      return output;
    }
    // Mask lower 8 bits (flags?) and align
    flags = flags & 0xffffff00;
    alignedResult = (undefined4 *)FUN_0069a2a0(localBuffer, originalFlags, flags);
    *output = *alignedResult;
    return output;
  }
  // Dereference inputPtr via some function (e.g., getObjectFromPointer)
  tempPtr = (int *)FUN_00ab3c50(inputPtr);
  validationResult = FUN_004d4b20(flags);
  if ((validationResult < 0) && (validationResult = FUN_004d4b20(tempPtr + 4), validationResult < 0)) {
    // Check if the original inputPtr has a non-zero first dword
    validationResult = *inputPtr;
    if (validationResult != 0) {
      inputPtr = tempPtr; // use the dereferenced pointer
    }
    // Copy with flag indicating whether original pointer was non-null
    FUN_00699df0(output, inputPtr, flags, validationResult != 0);
    return output;
  }
  // If validation passes, mask and align
  flags = flags & 0xffffff00;
  alignedResult = (undefined4 *)FUN_0069a2a0(localBuffer, originalFlags, flags);
  *output = *alignedResult;
  return output;
}