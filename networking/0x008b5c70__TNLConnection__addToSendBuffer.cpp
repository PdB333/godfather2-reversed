// FUNC_NAME: TNLConnection::addToSendBuffer
void __thiscall TNLConnection::addToSendBuffer(int thisPtr, undefined4 param_2)
{
  // +0x108: current send buffer count (uint)
  // +0x08: send buffer array (starts at offset 8, each entry 4 bytes)
  if (*(uint *)(thisPtr + 0x108) < 0x20) {
    *(undefined4 *)(thisPtr + 8 + *(uint *)(thisPtr + 0x108) * 4) = param_2;
    *(int *)(thisPtr + 0x108) = *(int *)(thisPtr + 0x108) + 1;
  }
  return;
}