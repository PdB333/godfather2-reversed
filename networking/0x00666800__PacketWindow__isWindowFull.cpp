// FUNC_NAME: PacketWindow::isWindowFull
// Function at 0x00666800
// Checks if the reliable packet window is full (all slots have pending ACK)
// Returns 1 if full, 0 otherwise
// this pointer in EAX points to a packet window structure
// Structure layout:
// +0x00: int windowSize (number of slots)
// +0x04: int currentSequence
// +0x08: int baseSequence
// +0x0C: int[] slotStates (array of windowSize ints)
// Slot state values: 0xFFFFFFF = pending ACK, other = acknowledged/delivered

int PacketWindow::isWindowFull(void)
{
  int windowSize;
  int *slotStates;
  int i;
  
  windowSize = this->windowSize;
  if (windowSize < 2) {
    return 0;
  }
  
  i = 1;
  if (1 < windowSize) {
    slotStates = this->slotStates;
    do {
      slotStates = slotStates + 1;
      if (*slotStates != 0xFFFFFFF) {
        return 0;
      }
      i = i + 1;
    } while (i < windowSize);
  }
  return 1;
}