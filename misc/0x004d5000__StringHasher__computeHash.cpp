// FUNC_NAME: StringHasher::computeHash

// Address: 0x004d5000
// Role: Converts a string input into a 128-bit hash value stored in a 4-int (16-byte) buffer.
// Uses the class fields at +0x00 (m_pBuffer) and +0x04 (m_bufferLength) for internal state.
// If the input string is null or empty, resets the internal state and returns the output buffer zeroed.
// Otherwise, performs a string parsing step (likely extracting a token from a delimited string)
// and copies data from the internal buffer to the output.

undefined4 * __thiscall StringHasher::computeHash(int *this, undefined4 *outBuffer, char *inputString)
{
  char *pTokenStart;
  char cChar;
  int stringLen;
  int bufferOffset;
  int bufferSize;
  
  // If input string is null or empty, reset internal state and return zeroed output.
  if ((inputString == (char *)0x0) || (*inputString == '\0')) {
    this->reset();              // FUN_004d3b50
    return outBuffer;
  }
  
  // Get internal buffer size (offset +0x04)
  bufferSize = this[1];
  if (bufferSize != 0) {
    // Get internal buffer pointer (offset +0x00)
    bufferOffset = *this;
    // Compute length of the string pointed to by internal buffer? (FUN_004d4e20)
    stringLen = this->getBufferLength(bufferOffset);
    if (stringLen != 0) {
      // Find the null terminator of the inputString
      pTokenStart = inputString + 1;
      do {
        cChar = *inputString;
        inputString = inputString + 1;
      } while (cChar != '\0');
      // Reposition inputString based on the computed length
      // This effectively moves back to point to a specific character in the input
      inputString = inputString + (stringLen - (int)pTokenStart);
      // If that character is not null, copy data from internal buffer to outBuffer
      if (*inputString != '\0') {
        // Copy (internal buffer size - offset) + bufferSize bytes from inputString position
        // FUN_004d38f0 is likely memcpy
        memcpy(inputString, (bufferOffset - (int)inputString) + bufferSize);
        return outBuffer;
      }
    }
  }
  // If any condition fails, zero out the 128-bit output buffer
  outBuffer[0] = 0;
  outBuffer[1] = 0;
  outBuffer[2] = 0;
  outBuffer[3] = 0;
  return outBuffer;
}