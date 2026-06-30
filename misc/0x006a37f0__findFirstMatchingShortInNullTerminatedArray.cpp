// FUNC_NAME: findFirstMatchingShortInNullTerminatedArray
int findFirstMatchingShortInNullTerminatedArray(short* arrayA, short* arrayB)
{
  int indexA = 0;
  
  // Check if first array is empty (null-terminated, first element zero)
  if (*arrayA != 0) {
    do {
      int indexB = 0;
      
      // Check if second array is non-empty
      if (*arrayB != 0) {
        short currentB = *arrayB;
        do {
          // Compare current element of arrayA with current element of arrayB
          if (arrayA[indexA] == currentB) {
            return indexA; // Found match, return index in arrayA
          }
          currentB = arrayB[indexB + 1];
          indexB = indexB + 1;
        } while (currentB != 0); // Continue until null terminator in arrayB
      }
      indexA = indexA + 1;
    } while (arrayA[indexA] != 0); // Continue until null terminator in arrayA
  }
  
  return -1; // No match found
}