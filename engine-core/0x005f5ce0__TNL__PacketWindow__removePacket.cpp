// FUNC_NAME: TNL::PacketWindow::removePacket
void __fastcall TNL::PacketWindow::removePacket(int *packetEntry)
{
  int *headEntry;
  int *prevEntry;
  int *currentEntry;

  headEntry = (int *)*packetEntry;
  if (headEntry != 0) {
    prevEntry = *(int **)(headEntry + 4); // +0x04: prev pointer
    if (prevEntry == packetEntry) {
      // Removing the head of the list
      *(int *)(headEntry + 4) = packetEntry[1]; // +0x04: prev = next
      *packetEntry = 0; // Clear head
      packetEntry[2] = 0; // +0x08: clear some field
      return;
    }
    currentEntry = (int *)prevEntry[1]; // +0x04: prev's next
    while (currentEntry != packetEntry) {
      prevEntry = (int *)prevEntry[1]; // +0x04: advance prev
      currentEntry = (int *)prevEntry[1]; // +0x04: advance current
    }
    prevEntry[1] = packetEntry[1]; // +0x04: unlink from list
    *packetEntry = 0; // Clear entry
  }
  packetEntry[2] = 0; // +0x08: clear some field
  return;
}