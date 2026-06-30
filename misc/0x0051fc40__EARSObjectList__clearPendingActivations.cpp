// FUNC_NAME: EARSObjectList::clearPendingActivations
void EARSObjectList::clearPendingActivations()
{
  // Iterate over linked list from head (+0x14) to tail (+0x1c)
  Node* current = head; // +0x14
  while (current != tail) { // +0x1c
    uint8_t flags = (uint8_t)(current->flags); // +0x460 (lower byte)
    // Check bit2 (pending active) set and bit1 (active) clear
    if ((flags & 0x04) && !(flags & 0x02)) {
      // Clear bit2 and reset state byte
      current->flags = current->flags & 0xfffb; // clear bit2
      current->state = 0; // +0x450
    }
    current = current->next; // +0x40
  }
}