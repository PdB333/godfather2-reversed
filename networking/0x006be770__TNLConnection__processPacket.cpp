// FUNC_NAME: TNLConnection::processPacket

void __thiscall TNLConnection::processPacket(TNLConnection *this, int *packet)
{
  int state;
  int response;

  validatePacket(packet);
  if (*packet == this->expectedPacketType) { // +0x1c
    state = getConnectionState(this->connectionHandle); // +0x14
    if (state != 0) {
      state = getGameMode();
      // param_2[1] stored but not used – possibly part of packet data for future use
      packet[1]; 
      if (state == this->currentGameMode) { // +0x18
        response = this->modeA; // +0x24
      } else {
        response = this->modeB; // +0x2c
      }
      sendResponse(&response, 0);
    }
  }
}