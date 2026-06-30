// FUNC_NAME: Socket::recvfrom
// Function at 0x00658390: Receives a network packet and optionally stores the source address.
// Uses EA's networking layer with debug/profile support. Two modes: bitstream (mode 2) and raw (mode 1).
// param_1: outAddr - pointer to NetAddress structure (family, port, 4 x 32-bit address fields)
// param_2: buffer - pointer to receive buffer
// param_3: outLen - pointer to int that receives the number of bytes received (or acts as bitstream pointer in mode 2)
// Returns: 0 on success, 2 on would-block or error

undefined4 Socket::recvfrom(ushort *outAddr, undefined4 buffer, int *outLen)
{
  code *pcVar1;
  int *savedLenPtr;
  char debugCheck;
  ushort port;
  undefined4 retVal;
  int bytesReceived;
  byte *bitmapPtr;
  u_long addr32;
  bool bVar9;
  short family;
  ushort portFromBitstream;
  undefined2 addrPart1;
  undefined2 addrPart2;
  
  savedLenPtr = outLen; // preserve original outLen for later
  
  // Debug/profile code when global mode is 2 and debug enabled
  if ((gSocketMode == 2) && (gSocketDebugEnabled != '\0')) {
    if ((gSocketProfilerFlags & 1) == 0) {
      gSocketProfilerFlags |= 1;
      gSocketProfilerString0 = "Socket::recvfrom";
      gSocketProfilerLine = 0xffffffff;
      gSocketProfilerDepth = gProfilerDepthCurrent;
      gProfilerDepthCurrent = &gSocketProfilerString0;
    }
    socketProfilerEnter(&gSocketProfilerString0);
    gSocketCallCounter = gSocketCallCounter + 1;
    if ((gSocketCallLimit != 0) && (gSocketCallLimit <= gSocketCallCounter)) {
      pcVar1 = (code *)swi(3);
      retVal = (*pcVar1)();
      return retVal;
    }
    // Check if socket would block
    socketCheckBlocking(&outLen);
    if ((char)outLen != '\0') {
      if ((gRecvWouldBlockOk == '\0') && (gRecvWouldBlockCount < gSocketMaxBlockCount)) {
        return 2;
      }
      pcVar1 = (code *)swi(3);
      retVal = (*pcVar1)();
      return retVal;
    }
    // Read address fields from bitstream
    readBitsFromStream(0x10, &outLen);
    *outAddr = (ushort)outLen; // family
    readBitsFromStream(0x10, &outLen);
    outAddr[1] = (ushort)outLen; // port
    readBitsFromStream(0x20, &outLen);
    *(int **)(outAddr + 2) = outLen; // addr part 1
    readBitsFromStream(0x20, &outLen);
    *(int **)(outAddr + 4) = outLen; // addr part 2
    readBitsFromStream(0x20, &outLen);
    *(int **)(outAddr + 6) = outLen; // addr part 3
    readBitsFromStream(0x20, &outLen);
    *(int **)(outAddr + 8) = outLen; // addr part 4
    readBitsFromStream(0x20, &outLen);
    *savedLenPtr = (int)outLen; // length in bytes
    // Read packet data
    readBitsFromStream((int)outLen * 8, buffer);
    if ((gRecvWouldBlockOk != '\0') || (gRecvWouldBlockCount >= gSocketMaxBlockCount)) {
      pcVar1 = (code *)swi(3);
      retVal = (*pcVar1)();
      return retVal;
    }
  }
  else {
    // Normal recvfrom via platform API
    bytesReceived = platformRecvFrom(buffer);
    if (bytesReceived < 0) {
      // Debug/profile for recvfrom failure
      if ((gSocketMode == 1) && (gSocketDebugEnabled != '\0')) {
        if ((gSocketProfilerFlags & 2) == 0) {
          gSocketProfilerFlags |= 2;
          gSocketProfilerString1 = "Socket::recvfrom";
          gSocketProfilerLine = 0xffffffff;
          gSocketProfilerDepth = gProfilerDepthCurrent;
          gProfilerDepthCurrent = &gSocketProfilerString1;
        }
        socketProfilerEnter(&gSocketProfilerString1);
        // Mark an error in the bitmap
        if ((gRecvErrorCount + 1 <= gMaxRecvErrors) || (debugCheck = socketReadyCheck(), debugCheck != '\0')) {
          bitmapPtr = (byte *)(gRecvErrorBitmap + (gRecvErrorCount >> 3));
          *bitmapPtr |= (1 << ((byte)gRecvErrorCount & 7));
          gRecvErrorCount++;
        }
        socketProfilerExit();
      }
      return 2; // would block / error
    }
    // If address structure was provided (family field from bitstream)
    if (family == 2) {
      *outAddr = 0; // clear family
      port = htons(portFromBitstream);
      outAddr[1] = port;
      addr32 = htonl(CONCAT22(addrPart2, addrPart1));
      *(u_long *)(outAddr + 2) = addr32;
      outAddr[4] = 0;
      outAddr[5] = 0;
      outAddr[6] = 0;
      outAddr[7] = 0;
      outAddr[8] = 0;
      outAddr[9] = 0;
    }
    bVar9 = gSocketMode == 1;
    *savedLenPtr = bytesReceived; // store actual bytes received
    if ((bVar9) && (gSocketDebugEnabled != '\0')) {
      // Debug/profile for successful recvfrom
      if ((gSocketProfilerFlags & 4) == 0) {
        gSocketProfilerFlags |= 4;
        gSocketProfilerString2 = "Socket::recvfrom";
        gSocketProfilerLine = 0xffffffff;
        gSocketProfilerDepth = gProfilerDepthCurrent;
        gProfilerDepthCurrent = &gSocketProfilerString2;
      }
      socketProfilerEnter(&gSocketProfilerString2);
      // Log received data: decrement error bitmap count
      if ((gRecvErrorCount + 1 <= gMaxRecvErrors) || (debugCheck = socketReadyCheck(), debugCheck != '\0')) {
        bitmapPtr = (byte *)(gRecvErrorBitmap + (gRecvErrorCount >> 3));
        *bitmapPtr &= ~(1 << ((byte)gRecvErrorCount & 7));
        gRecvErrorCount++;
      }
      // Write back address fields to stream for logging
      outLen = (int *)(uint)*outAddr;
      writeBitsToStream(0x10, &outLen);
      outLen = (int *)(uint)outAddr[1];
      writeBitsToStream(0x10, &outLen);
      outLen = *(int **)(outAddr + 2);
      writeBitsToStream(0x20, &outLen);
      outLen = *(int **)(outAddr + 4);
      writeBitsToStream(0x20, &outLen);
      outLen = *(int **)(outAddr + 6);
      writeBitsToStream(0x20, &outLen);
      outLen = *(int **)(outAddr + 8);
      writeBitsToStream(0x20, &outLen);
      outLen = (int *)*savedLenPtr;
      writeBitsToStream(0x20, &outLen);
      writeBitsToStream(*savedLenPtr * 8, buffer);
      socketProfilerExit();
    }
  }
  return 0; // success
}