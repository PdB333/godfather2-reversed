// FUNC_NAME: PacketDispatcher::handleMessageType802
void __thiscall PacketDispatcher::handleMessageType802(int this, int connection, int session)
{
  int* typeList;          // Pointer to array of message types (this+0x74)
  int   count;            // Number of entries (this+0x78)
  int   index;            // Iteration counter
  int   decodedIndex;     // Index extracted from message (local_c[0])
  int   newValue;         // Value to compare and set

  decodedIndex = 0;
  index = 0;

  // Search for message type 0x802 in the pending list
  if (0 < *(int*)(this + 0x78)) {
    typeList = *(int**)(this + 0x74);
    do {
      if (*typeList == 0x802) {
        // Decode the 0x802 packet and extract an index
        FUN_004af8c0(&decodedIndex, 0x802);   // decodedIndex holds the index from the packet
                                              // (likely a sequence number or object ID)
        // Access session->ptrAt0x8->arrayAt0x50[decodedIndex] to get the new value
        newValue = *(int*)(*(int*)(*(int*)(session + 8) + 0x50) + decodedIndex * 4);
        break;
      }
      index = index + 1;
      typeList = typeList + 4;
    } while (index < *(int*)(this + 0x78));
  }

  // Update the connection's field at offset 0x60 if it changed
  if (*(int*)(connection + 0x60) != newValue) {
    *(int*)(connection + 0x60) = newValue;
  }
}