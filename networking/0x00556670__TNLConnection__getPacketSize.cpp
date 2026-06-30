// FUNC_NAME: TNLConnection::getPacketSize
int TNLConnection::getPacketSize(int param_1)
{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x1c); // +0x1c: packetFlags or packetType
  if ((uVar1 & 0xc0000000) == 0x80000000) { // Check if bit 30 is set (0x80000000)
    return uVar1 * 4; // Return size in bytes (multiply by 4 for 32-bit words)
  }
  if ((uVar1 & 0xc0000000) != 0xc0000000) { // Check if bits 30-31 are not both set
    return 0; // Invalid packet type, return 0
  }
  return *(int *)(uVar1 * 4 + 0x60); // +0x60: packetSizeTable or similar lookup
}