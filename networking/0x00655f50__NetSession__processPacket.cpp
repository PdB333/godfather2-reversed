// FUNC_NAME: NetSession::processPacket
void __fastcall NetSession::processPacket(int this)
{
  int *in_EAX;
  int iVar1;
  undefined1 local_541;
  int local_540;
  undefined **local_53c;
  undefined4 local_538;
  undefined4 local_534;
  undefined1 *local_530;
  int local_52c;
  undefined1 local_528;
  undefined4 local_524;
  undefined1 local_520;
  undefined1 local_51f;
  undefined4 local_510;
  undefined4 local_50c;
  undefined4 local_508;
  undefined1 local_504;
  undefined1 auStack_40c [8];
  undefined1 local_404 [1028];

  local_530 = local_404;
  local_510 = 0x2000; // +0x510: packet buffer size
  local_50c = 0x2000; // +0x50c: packet buffer size
  local_538 = 0;      // +0x538: flags
  local_534 = 0;      // +0x534: flags
  local_52c = 0x400;  // +0x52c: max packet size
  local_528 = 0;      // +0x528: sequence number
  local_524 = 0;      // +0x524: ack
  local_520 = 0;      // +0x520: flags
  local_51f = 0;      // +0x51f: flags
  local_504 = 0;      // +0x504: buffer
  local_508 = 0;      // +0x508: buffer
  local_53c = &PTR_LAB_00e42f38; // +0x53c: vtable or static data
  local_541 = 2;      // +0x541: packet type

  FUN_0064b810(8, &local_541); // allocate 8 bytes for packet header
  FUN_0064bb50((char)in_EAX[0x66]); // +0x198: connection state
  local_540 = in_EAX[0x29]; // +0xA4: sequence number
  FUN_0064b810(0x20, &local_540); // allocate 32 bytes for packet data
  iVar1 = (**(code **)*in_EAX)(); // vtable call: getPacketSize
  FUN_0064c760(iVar1 + 0x20, 0xff); // memset packet data
  (**(code **)(*in_EAX + 0x44))(&local_53c); // vtable call: buildPacket
  (**(code **)(*in_EAX + 0x20))(&local_540); // vtable call: sendPacket
  in_EAX[0x67] = in_EAX[0x67] + 1; // +0x19C: packet counter
  in_EAX[0x68] = *(int *)(param_1 + 100); // +0x1A0: last received sequence
  FUN_00658230(param_1 + 0x5c, auStack_40c, local_52c + 7U >> 3, 1); // copy packet data
  FUN_0064b440(); // free allocated memory
  return;
}