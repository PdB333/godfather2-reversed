// FUNC_NAME: NetStream::readIndexedByte
undefined4 __thiscall NetStream::readIndexedByte(int this, NetStream *inputStream)
{
  byte bVar1;
  undefined4 *outputToken;
  int *readPtr;
  int dataPtr;
  uint uVar4;
  int iVar5;
  int extraout_ECX;
  uint dataSize;
  bool bVar7;
  float indexFloat;
  float newIndexFloat;

  // readPtr points to the current token in the input stream (type + data pointer)
  readPtr = *(int **)(inputStream + 0xC);
  dataPtr = this; // this might store the final data address or be unused

  // Check if there is a token available in the input stream
  if ((readPtr < *(int **)(inputStream + 8)) && (dataPtr = this, readPtr != (int *)0x0)) {
    if (*readPtr == 4) {
      // Token type 4: immediate data pointer at readPtr[1] + 0x10
      iVar5 = readPtr[1] + 0x10;
    }
    else {
      // Not token type 4: call ensureReadAvailable to advance the stream
      iVar5 = ensureReadAvailable((int)inputStream);
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = readPtr[1] + 0x10;
      }
      // Check for buffer overflow
      if (*(uint *)(*(int *)(inputStream + 0x10) + 0x20) <= *(uint *)(*(int *)(inputStream + 0x10) + 0x24)) {
        handleBufferOverflow();
      }
    }
    dataPtr = iVar5;
    if (iVar5 != 0) goto LAB_0062b3f0;
  }

  // No valid token found, log error
  logError((char *)PTR_s_string_00e2a8ac);
  iVar5 = extraout_ECX; // result from error function

LAB_0062b3f0:
  // Re-read the current token to get the size of the data buffer (at readPtr[1] + 0xC)
  readPtr = *(int **)(inputStream + 0xC);
  if ((readPtr < *(int **)(inputStream + 8)) && (readPtr != (int *)0x0)) {
    if (*readPtr == 4) {
      dataSize = *(uint *)(readPtr[1] + 0xC);
    }
    else {
      iVar5 = ensureReadAvailable((int)inputStream);
      if (iVar5 == 0) {
        dataSize = 0;
        iVar5 = dataPtr;
      }
      else {
        dataSize = *(uint *)(readPtr[1] + 0xC);
        iVar5 = dataPtr;
      }
    }
  }
  else {
    dataSize = 0;
  }

  // Advance to the next token (which should be a float index)
  readPtr = (int *)(*(int *)(inputStream + 0xC) + 8);
  newIndexFloat = DAT_00e2b1a4; // default float value from static memory

  // If the next token exists and its type > 0, read the float index from it
  if (((readPtr < *(int **)(inputStream + 8)) && (readPtr != (int *)0x0)) && (0 < *readPtr)) {
    readFloatToken();
    iVar5 = dataPtr;
    newIndexFloat = in_XMM0_Da; // incoming float from readFloatToken
  }

  uVar4 = (uint)newIndexFloat;
  bVar7 = (int)uVar4 < 0; // negative index?

  // Handle negative index by adding dataSize + 1 (wrap-around)
  if (bVar7) {
    uVar4 = dataSize + 1 + uVar4; // uVar4 is currently the negative value, so this effectively adds
    bVar7 = (int)uVar4 < 0;
  }

  // Check if index is within bounds [0, dataSize)
  if ((uVar4 != 0 && !bVar7) && (uVar4 <= dataSize)) {
    // Read the byte at offset (uVar4 - 1) from the data buffer
    bVar1 = *(byte *)(iVar5 + -1 + uVar4);
    // Write a new token (type 3 = float) with the byte value into the output stream
    outputToken = *(undefined4 **)(inputStream + 8);
    *outputToken = 3;
    outputToken[1] = (float)bVar1;
    *(int *)(inputStream + 8) = *(int *)(inputStream + 8) + 8; // advance output pointer
    return 1;
  }

  return 0;
}