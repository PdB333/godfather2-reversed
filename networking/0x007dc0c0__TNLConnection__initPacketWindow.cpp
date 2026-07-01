// FUNC_NAME: TNLConnection::initPacketWindow
void __thiscall TNLConnection::initPacketWindow(undefined2 *this, int param_2, undefined2 param_3, int param_4, int *param_5)
{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  
  // +0x02: store sequence number (param_3)
  this[1] = param_3;
  
  // +0x10: start of packet window data (32 slots, 4 bytes each = 0x80 bytes)
  puVar1 = (undefined4 *)(this + 0x10);
  
  // +0x00: clear first field (likely packet count or flags)
  *this = 0;
  
  // Calculate source offset for copying packet window data
  param_2 = param_2 - (int)puVar1;
  
  // Copy 16 dwords (64 bytes) from source to packet window
  iVar3 = 0x10;
  do {
    *puVar1 = *(undefined4 *)(param_2 + (int)puVar1);
    puVar1 = puVar1 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  
  // +0x30: handle optional callback/notification pointer
  if ((param_5 == (int *)0x0) || (*param_5 == 0)) {
    *(undefined4 *)(this + 0x30) = 0;
  }
  else {
    // FUN_004080d0 likely increments ref count or registers callback
    FUN_004080d0(param_5);
  }
  
  // +0x14 (this + 10): clear count of pending acknowledgements
  *(undefined4 *)(this + 10) = 0;
  
  // Copy acknowledgement entries from param_4 (max 4 entries)
  if ((param_4 != 0) && (uVar2 = 0, *(int *)(param_4 + 0x10) != 0)) {
    do {
      if (*(uint *)(this + 10) < 4) {
        // +0x04 to +0x0C: store ACK entries (4 slots, 2 bytes each)
        *(undefined4 *)(this + *(uint *)(this + 10) * 2 + 2) =
             *(undefined4 *)(param_4 + uVar2 * 4);
        *(int *)(this + 10) = *(int *)(this + 10) + 1;
      }
      uVar2 = uVar2 + 1;
    } while (uVar2 < *(uint *)(param_4 + 0x10));
  }
  return;
}