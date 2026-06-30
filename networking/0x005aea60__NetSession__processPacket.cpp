// FUNC_NAME: NetSession::processPacket
undefined4 __thiscall NetSession::processPacket(NetSession *this, int packetData, undefined4 param_3, undefined4 param_4, undefined4 param_5)
{
  char cVar1;
  uint *puVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 local_40;
  undefined4 local_24;
  undefined4 local_20;
  undefined8 *local_1c;
  undefined8 local_18;
  undefined8 local_10;
  
  local_1c = &local_18;
  local_24 = 0;
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  if (packetData != 0) {
    cVar1 = FUN_0059c5c0(0); // likely isNetworkEnabled or similar
    if (cVar1 != '\0') {
      puVar2 = (uint *)FUN_0059c3b0(); // getConnectionState or similar
      uVar3 = *puVar2 & 0x7fff;
      if (((*puVar2 & 0x8000) == 0) || ((uVar3 != 0xd && (uVar3 != 0x12)))) {
        FUN_0059c3b0(); // getConnectionState again
        cVar1 = FUN_005a4140(); // check if packet is valid
        if (cVar1 == '\0') {
          FUN_0059c3b0(); // getConnectionState
          cVar1 = FUN_0059c950(); // check if connection is established
          if (cVar1 == '\0') {
            FUN_0059bf00(); // handle invalid packet / disconnect
          }
        }
      }
    }
  }
  FUN_005ad100(packetData, param_3, param_4, &local_24); // parsePacketHeader
  uVar4 = FUN_005ae7e0(this, packetData, local_40, param_3, &local_24, param_4, param_5); // processPacketBody
  if ((local_1c != &local_18) && (local_1c != (undefined8 *)0x0)) {
    (*DAT_0119caf4)(local_1c); // free allocated memory
  }
  return uVar4;
}