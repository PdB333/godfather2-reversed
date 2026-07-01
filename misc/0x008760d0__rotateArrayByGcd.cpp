// FUNC_NAME: rotateArrayByGcd
void rotateArrayByGcd(undefined4 *array, int arraySize, undefined4 *startPtr)

{
  undefined4 temp1;
  undefined4 temp2;
  int gcd;
  undefined4 *writePtr;
  undefined4 *readPtr;
  int stepSize;
  int cycleLen;
  int cycleCount;
  int numCycles;
  undefined4 *cycleStart;
  
  cycleLen = (int)startPtr - (int)array >> 3;
  stepSize = arraySize - (int)array >> 3;
  cycleCount = stepSize;
  numCycles = cycleLen;
  while (gcd = cycleCount, gcd != 0) {
    cycleCount = numCycles % gcd;
    numCycles = gcd;
  }
  if ((numCycles < cycleLen) && (0 < numCycles)) {
    cycleStart = array + numCycles * 2;
    do {
      temp1 = *cycleStart;
      temp2 = cycleStart[1];
      readPtr = cycleStart + stepSize * 2;
      writePtr = cycleStart;
      if (cycleStart + stepSize * 2 == startPtr) {
        readPtr = array;
      }
      while (readPtr != cycleStart) {
        *writePtr = *readPtr;
        writePtr[1] = readPtr[1];
        gcd = (int)startPtr - (int)readPtr >> 3;
        writePtr = readPtr;
        if (stepSize < gcd) {
          readPtr = readPtr + stepSize * 2;
        }
        else {
          readPtr = array + (stepSize - gcd) * 2;
        }
      }
      numCycles = numCycles + -1;
      cycleStart = cycleStart + -2;
      *writePtr = temp1;
      writePtr[1] = temp2;
    } while (0 < numCycles);
  }
  return;
}