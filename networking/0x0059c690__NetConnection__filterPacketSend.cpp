// FUNC_NAME: NetConnection::filterPacketSend
void __fastcall NetConnection::filterPacketSend(uint param_1, uint *param_2)
{
  uint packetType;
  
  if (param_2 != DAT_0119cbbc) {
    packetType = *param_2 & 0x7fff;
    if ((packetType != 0x19) && // Not a Ping response packet
       (((~(*param_2 >> 0xf) & 1) != 0 || // Not a reliable packet
        (((packetType != 0xb && (packetType != 0x18)) && (packetType != 0x17)))))) { // Not a game state packet type
      FUN_0059c230(param_2); // Send the packet via the connection layer
    }
  }
}