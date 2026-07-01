// FUNC_NAME: TNLConnection::validatePacketId
uint TNLConnection::validatePacketId(int *this, uint packetId)
{
  char isValid;
  uint validatedId;

  validatedId = 0;
  // Call virtual function at vtable+0x10 to validate the packet ID
  // Returns non-zero if the packet ID is valid for this connection
  isValid = (**(code **)(*this + 0x10))(packetId, &validatedId);
  
  // If valid, return the validated ID; otherwise return 0
  return -(uint)(isValid != '\0') & packetId;
}