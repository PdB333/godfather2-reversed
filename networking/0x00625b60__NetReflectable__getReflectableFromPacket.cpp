// FUNC_NAME: NetReflectable::getReflectableFromPacket
int __fastcall NetReflectable::getReflectableFromPacket(undefined4 param_1, int param_2)
{
  int in_EAX;
  int *piVar1;
  
  if (param_2 < 1) {
    piVar1 = (int *)FUN_00625430(); // likely getPacketHeader
  }
  else {
    piVar1 = (int *)(*(int *)(in_EAX + 0xc) + -8 + param_2 * 8); // +0x0C: packetBuffer, each entry 8 bytes
    if (*(int **)(in_EAX + 8) <= piVar1) { // +0x08: packetCount or bufferEnd
      return 0;
    }
  }
  if (piVar1 != (int *)0x0) {
    if (*piVar1 == 2) {
      return piVar1[1]; // type 2: direct pointer to reflectable
    }
    if (*piVar1 == 7) {
      return piVar1[1] + 0x10; // type 7: offset from something, likely a relative offset in memory
    }
  }
  return 0;
}