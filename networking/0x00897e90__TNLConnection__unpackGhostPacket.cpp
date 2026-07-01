// FUNC_NAME: TNLConnection::unpackGhostPacket
undefined4 __thiscall TNLConnection::unpackGhostPacket(int this, undefined4 param_2, uint *packetData, uint packetSize)
{
  uint bitMask;
  uint dataWord;
  uint *destSlot;
  byte shift;
  int slotIndex;
  
  if ((packetData != (uint *)0x0) && (3 < packetSize)) {
    // Call some initialization function 8 times
    slotIndex = 7;
    do {
      FUN_00897da0();
      slotIndex = slotIndex + -1;
    } while (slotIndex != 0);
    
    if (packetSize != 4) {
      bitMask = *packetData;
      shift = 2;
      packetData = packetData + 1;
      destSlot = (uint *)(this + 0xc);  // +0x0C: ghost slot array start
      slotIndex = 7;
      
      do {
        // Check if bit at position (shift-2) is set in mask
        if ((bitMask & 1 << (shift - 2 & 0x1f)) != 0) {
          dataWord = *packetData;
          // Check for non-zero data and not a special sentinel value
          if (((((dataWord != 0) || (packetData[1] != 0)) || (packetData[2] != 0)) || (packetData[3] != 0)) &&
             (((dataWord != 0xbadbadba || (packetData[1] != 0xbeefbeef)) ||
              ((packetData[2] != 0xeac15a55 || (packetData[3] != 0x91100911)))))) {
            destSlot[-2] = dataWord;
            destSlot[-1] = packetData[1];
            *destSlot = packetData[2];
            destSlot[1] = packetData[3];
          }
          packetData = packetData + 4;
        }
        
        if ((bitMask & 1 << (shift - 1 & 0x1f)) != 0) {
          dataWord = *packetData;
          if ((((dataWord != 0) || (packetData[1] != 0)) || ((packetData[2] != 0 || (packetData[3] != 0)))) &&
             ((((dataWord != 0xbadbadba || (packetData[1] != 0xbeefbeef)) || (packetData[2] != 0xeac15a55))
              || (packetData[3] != 0x91100911)))) {
            destSlot[4] = dataWord;
            destSlot[5] = packetData[1];
            destSlot[6] = packetData[2];
            destSlot[7] = packetData[3];
          }
          packetData = packetData + 4;
        }
        
        if ((bitMask & 1 << (shift & 0x1f)) != 0) {
          dataWord = *packetData;
          if ((((dataWord != 0) || (packetData[1] != 0)) || ((packetData[2] != 0 || (packetData[3] != 0)))) &&
             (((dataWord != 0xbadbadba || (packetData[1] != 0xbeefbeef)) ||
              ((packetData[2] != 0xeac15a55 || (packetData[3] != 0x91100911)))))) {
            destSlot[10] = dataWord;
            destSlot[0xb] = packetData[1];
            destSlot[0xc] = packetData[2];
            destSlot[0xd] = packetData[3];
          }
          packetData = packetData + 4;
        }
        
        if ((bitMask & 1 << (shift + 1 & 0x1f)) != 0) {
          dataWord = *packetData;
          if (((((dataWord != 0) || (packetData[1] != 0)) || (packetData[2] != 0)) || (packetData[3] != 0)) &&
             (((dataWord != 0xbadbadba || (packetData[1] != 0xbeefbeef)) ||
              ((packetData[2] != 0xeac15a55 || (packetData[3] != 0x91100911)))))) {
            destSlot[0x10] = dataWord;
            destSlot[0x11] = packetData[1];
            destSlot[0x12] = packetData[2];
            destSlot[0x13] = packetData[3];
          }
          packetData = packetData + 4;
        }
        
        shift = shift + 4;
        destSlot = destSlot + 0x18;  // Each slot is 0x60 bytes (24 dwords)
        slotIndex = slotIndex + -1;
      } while (slotIndex != 0);
    }
  }
  return 1;
}