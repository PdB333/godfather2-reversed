// FUNC_NAME: TNLConnection::processReliablePacket
void __thiscall TNLConnection::processReliablePacket(int this, int packetBuffer)
{
  int *vtablePtr;
  undefined4 sequenceId;
  int unaff_EBX;
  code *cleanupFunc;
  
  vtablePtr = (int *)FUN_00564de0(this + -4, packetBuffer + 0x110);
  (**(code **)(*vtablePtr + 8))(packetBuffer);
  FUN_004d3bc0(packetBuffer + 8);
  sequenceId = FUN_005653d0(this + -4, &stack0xffffffec);
  if (unaff_EBX != 0) {
    (*cleanupFunc)(unaff_EBX);
  }
  if (*(code **)(this + 0x230) != (code *)0x0) {
    (**(code **)(this + 0x230))(packetBuffer);
  }
  if (*(uint *)(this + 0x228) < 0x40) {
    *(undefined4 *)(this + 0x128 + *(uint *)(this + 0x228) * 4) = sequenceId;
    *(int *)(this + 0x228) = *(int *)(this + 0x228) + 1;
  }
  return;
}