// FUNC_NAME: StreamManager::checkMagicNumber
bool __fastcall StreamManager::checkMagicNumber(int *streamContext)
{
  int currentPos;
  unsigned int magic;
  char byte0, byte1, byte2;

  currentPos = streamContext[3]; // +0x0C: current read position in stream
  streamContext[1] = currentPos; // +0x04: save position
  magic = *(unsigned int *)(*streamContext + currentPos); // +0x00: stream buffer pointer
  byte0 = (char)magic;
  streamContext[1] = currentPos + 10; // advance past header (10 bytes)
  if (((byte0 == 'P') && (byte1 = (char)(magic >> 8), byte1 == 'F')) &&
      (byte2 = (char)(magic >> 0x10), byte2 == 'R')) {
    // Found "PFR" magic (EA EARS package format)
    streamContext[1] = currentPos; // restore position
    return true;
  }
  streamContext[1] = currentPos; // restore position
  return false;
}