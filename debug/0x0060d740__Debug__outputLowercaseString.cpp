// FUNC_NAME: Debug::outputLowercaseString
void Debug::outputLowercaseString(char *inputString)
{
  char *srcPtr;
  char *stackPtr;
  char *dstPtr;
  char currentChar;
  int stringLength;
  int allocatedSize;

  // Calculate string length
  srcPtr = inputString;
  do {
    currentChar = *srcPtr;
    srcPtr = srcPtr + 1;
  } while (currentChar != '\0');

  // Allocate stack space for copy (via alloca probe)
  stringLength = (int)(srcPtr - inputString);
  allocatedSize = -(int)(srcPtr + (1 - (int)(inputString + 1)));
  stackPtr = (char *)((int)&stackArea + allocatedSize);  // stackArea is local variable at stack

  // Copy string to stack
  dstPtr = (char *)((int)&stackArea + (allocatedSize - (int)inputString));
  srcPtr = inputString;
  do {
    currentChar = *srcPtr;
    *dstPtr = currentChar;
    srcPtr = srcPtr + 1;
    dstPtr = dstPtr + 1;
  } while (currentChar != '\0');

  // Convert to lowercase (in-place on stack)
  _strlwr(stackPtr);

  // Recalculate length after strlwr (same length)
  srcPtr = stackPtr;
  do {
    currentChar = *srcPtr;
    srcPtr = srcPtr + 1;
  } while (currentChar != '\0');
  
  // Prepare arguments for logging function
  // Call logging function with lowercase string
  FUN_00ab8560(stackPtr, 0, 0x60d7a4);
}