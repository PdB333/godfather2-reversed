// FUNC_NAME: TNLConnection::handleReliablePacket
void __thiscall TNLConnection::handleReliablePacket(int thisPtr, ushort packetSequence)
{
  int iVar1;
  
  if (0x1f < packetSequence) {
    iVar1 = FUN_00989df0(*(undefined4 *)(thisPtr + 0x2c), &packetSequence, 1);
    FUN_0098a480(iVar1 + *(int *)(thisPtr + 0x2c));
  }
  return;
}