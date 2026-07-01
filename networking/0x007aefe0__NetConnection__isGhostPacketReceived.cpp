// FUNC_NAME: NetConnection::isGhostPacketReceived
undefined4 __thiscall NetConnection::isGhostPacketReceived(int this, uint ghostId)
{
  // +0x58: pointer to ghost packet receive bitfield array
  // +0x8e0: offset into bitfield array for ghost packet reception tracking
  // Each bit in the array represents whether a specific ghost packet has been received
  // param_2 is the ghost packet ID (0-31 typically)
  return CONCAT31((int3)((uint)*(int *)(this + 0x58) >> 8),
                  (*(uint *)(*(int *)(this + 0x58) + 0x8e0 + (ghostId >> 5) * 4) &
                  1 << ((byte)ghostId & 0x1f)) != 0);
}