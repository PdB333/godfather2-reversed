// FUNC_NAME: StreamReader::readToken
void __thiscall StreamReader::readToken(uint param_1, uint param_2)
{
  int iVar1;
  int *piVar2;
  int *in_EAX;
  byte *pbVar3;
  uint uVar4;
  uint *this; // unaff_ESI - this pointer

  // +0x20: tokenType
  // +0x2C: tokenValue
  // +0x14: bufferSize (0x11f = 287)
  // +0x24: stream pointer
  // +0x1C: position
  // +0x04: flags
  // +0x08: flags2
  this[8] = param_1;   // +0x20: tokenType
  this[0xb] = param_2; // +0x2C: tokenValue
  this[5] = 0x11f;     // +0x14: bufferSize = 287
  this[9] = (uint)in_EAX; // +0x24: stream pointer
  this[7] = 0;         // +0x1C: position = 0
  this[1] = 1;         // +0x04: flags = 1
  this[2] = 1;         // +0x08: flags2 = 1

  // Read first byte from stream
  iVar1 = *in_EAX;     // stream->remaining
  *in_EAX = iVar1 + -1;
  if (iVar1 == 0) {
    // Need to refill buffer
    piVar2 = (int *)this[9]; // stream pointer
    pbVar3 = (byte *)(*(code *)piVar2[2])(0, piVar2[3], &param_2); // stream->readCallback
    if ((pbVar3 == (byte *)0x0) || (param_2 == 0)) {
      uVar4 = 0xffffffff; // EOF
    }
    else {
      piVar2[1] = (int)pbVar3; // stream->buffer
      *piVar2 = param_2 - 1;   // stream->remaining
      uVar4 = (uint)*pbVar3;   // first byte
      piVar2[1] = (int)(pbVar3 + 1); // advance buffer pointer
    }
  }
  else {
    pbVar3 = *(byte **)(this[9] + 4); // stream->buffer pointer
    uVar4 = (uint)*pbVar3;            // current byte
    *(byte **)(this[9] + 4) = pbVar3 + 1; // advance buffer pointer
  }
  *this = uVar4; // +0x00: currentChar

  // Skip whitespace (0x23 = '#', but this seems like a bug - should be 0x20 = space)
  // Actually checking for 0x23 which is '#', possibly comment handling
  if (uVar4 == 0x23) {
    do {
      // Read next byte
      iVar1 = *(int *)this[9]; // stream->remaining
      *(int *)this[9] = iVar1 + -1;
      if (iVar1 == 0) {
        piVar2 = (int *)this[9];
        pbVar3 = (byte *)(*(code *)piVar2[2])(0, piVar2[3], &param_2);
        if ((pbVar3 == (byte *)0x0) || (param_2 == 0)) {
          uVar4 = 0xffffffff;
        }
        else {
          piVar2[1] = (int)pbVar3;
          *piVar2 = param_2 - 1;
          uVar4 = (uint)*pbVar3;
          piVar2[1] = (int)(pbVar3 + 1);
        }
      }
      else {
        pbVar3 = *(byte **)(this[9] + 4);
        uVar4 = (uint)*pbVar3;
        *(byte **)(this[9] + 4) = pbVar3 + 1;
      }
      *this = uVar4; // update currentChar
    } while ((uVar4 != 10) && (uVar4 != 0xffffffff)); // until newline or EOF
  }
  return;
}