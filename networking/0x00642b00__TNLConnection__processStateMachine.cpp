// FUNC_NAME: TNLConnection::processStateMachine
void TNLConnection::processStateMachine(void)
{
  int *statePtr; // unaff_EDI
  int state; // *unaff_EDI
  int result; // iVar1

  state = *statePtr;
  switch(state) {
  case 5: // Resend request state
    *statePtr = 0xb; // Transition to wait state
    return;
  case 6: // Command type 4 with ID shifted
    result = sendCommand(statePtr[1] << 0xf | 4, *(this->dataBuffer + 8)); // Construct packet header
    *statePtr = 10;
    statePtr[1] = result;
    return;
  case 7: // Command type 5 with ID shifted
    result = sendCommand(statePtr[1] << 6 | 5, *(this->dataBuffer + 8));
    *statePtr = 10;
    statePtr[1] = result;
    return;
  case 8: // Data send state with space check
    if ((this->maxSlots <= statePtr[2]) && (statePtr[2] < 250)) {
      this->slotCount--;
    }
    if ((this->maxSlots <= statePtr[1]) && (statePtr[1] < 250)) {
      this->slotCount--;
    }
    result = allocateSlot(6, statePtr[1], statePtr[2]); // Get a slot index
    *statePtr = 10;
    statePtr[1] = result;
    return;
  case 0xc: // Clear flags and set bit for slot
    if (*statePtr == 0xc) {
      // Access slot array via vtable offset +0xc
      *(uint *)(*(this->vtablePtr + 0xc) + statePtr[1] * 4) = 
           *(uint *)(*(this->vtablePtr + 0xc) + statePtr[1] * 4) & 0xffff80bf | 0x80;
      // Transition and read status byte
      *statePtr = 0xb;
      statePtr[1] = (int)*(char *)(*(this->vtablePtr + 0xc) + 3 + statePtr[1] * 4);
    }
  }
  return;
}