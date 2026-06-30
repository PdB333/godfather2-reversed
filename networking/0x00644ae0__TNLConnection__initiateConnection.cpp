// FUNC_NAME: TNLConnection::initiateConnection
void __thiscall TNLConnection::initiateConnection(uint param_1, int param_2)
{
  int in_EAX;
  
  // Set connection state flags: bit 0 = initiating
  *(uint *)(in_EAX + 4) = param_1 | 1;
  
  // Initialize linked list pointers (self-referential for empty list)
  *(int *)(in_EAX + 0xc) = in_EAX;  // +0x0C: next packet
  *(int *)(in_EAX + 8) = in_EAX;   // +0x08: prev packet
  
  // Store the connection parameters
  *(uint *)(in_EAX + param_1) = param_1;
  
  // If the connection is not yet established (flag at +0x46C)
  if (*(char *)(param_2 + 0x46c) == '\0') {
    // Calculate the next sequence number for outgoing packets
    // Uses the base address at +0x440 and shifts the sequence counter
    *(uint *)(param_2 + 0x468) =
         (*(uint *)(*(int *)(param_2 + 0x440) + 4) >> 1 & 0x3ffffffc) + *(int *)(param_2 + 0x440);
  }
  return;
}