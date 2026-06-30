// FUNC_NAME: NetSession::initPacketWindow
void NetSession::initPacketWindow(void)
{
  undefined4 uVar1;
  undefined4 *this; // in_EAX
  
  uVar1 = DAT_00e2eff4; // +0x00: sequence base
  *this = DAT_00e2eff4; // +0x00: localSequence
  this[1] = uVar1;      // +0x04: remoteSequence
  this[2] = uVar1;      // +0x08: lastAckSequence
  uVar1 = DAT_00e2b1a4; // +0x0C: ack mask base
  this[3] = DAT_00e2b1a4; // +0x0C: ackMask
  this[4] = uVar1;      // +0x10: lastAckMask
  this[5] = 0;          // +0x14: packetSendCount
  this[6] = 0;          // +0x18: packetRecvCount
  this[0xd] = 96000;    // +0x34: maxPacketSize (96KB)
  this[7] = 1;          // +0x1C: windowSize (32 slots)
  this[8] = 0xbadbadba; // +0x20: magic1 (connection marker)
  this[9] = 0xbeefbeef; // +0x24: magic2
  this[10] = 0xeac15a55; // +0x28: magic3 (EA signature)
  this[0xb] = 0x91100911; // +0x2C: magic4 (9/11 date reference)
  *(undefined1 *)(this + 0xc) = 0; // +0x30: flags (cleared)
  return;
}