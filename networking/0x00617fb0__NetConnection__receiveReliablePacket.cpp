// FUNC_NAME: NetConnection::receiveReliablePacket
void __thiscall NetConnection::receiveReliablePacket(void *this, undefined4 param_2, uint param_3)
{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined *puVar6;
  uint local_124;
  undefined4 local_120 [4];
  undefined1 local_110 [64];
  undefined1 local_d0 [64];
  undefined1 local_90 [64];
  undefined1 local_50 [76];
  
  iVar3 = 0;
  if (this[1] != 0) {
    // Decompress/copy packet data into temporary buffers
    FUN_0066d310(param_2,local_120,local_90,local_110,local_d0,local_50,param_3);
    local_124 = 0;
    iVar1 = (**(code **)(*this + 0x10))(); // getPacketCount / getReliableBufferCount
    if (iVar1 != 0) {
      piVar4 = (int *)((int)this + 0x10); // +0x10: first reliable buffer slot
      do {
        iVar1 = piVar4[1];
        if (iVar1 != 0) {
          if (local_124 < param_3) {
            // Copy chunk data to appropriate receive buffers
            // +0x4: buffer index, +0x8: data offset, +0xC: size
            FUN_0060aa90(this[1],piVar4[-1],local_120[local_124]); // payload copy
            FUN_0060add0(this[1],*piVar4,local_110 + iVar3); // chunk type/header
            FUN_0060add0(this[1],piVar4[1],local_90 + iVar3); // data
            FUN_0060add0(this[1],piVar4[2],local_d0 + iVar3); // more data
            iVar1 = piVar4[3];
            iVar5 = this[1];
            puVar6 = local_50 + iVar3;
          }
          else {
            puVar6 = &DAT_01225dc0; // null sentinel / end marker
            iVar5 = this[1];
          }
          FUN_0060add0(iVar5,iVar1,puVar6);
        }
        local_124 = local_124 + 1;
        iVar3 = iVar3 + 0x10;
        piVar4 = piVar4 + 5; // each slot is 5 ints (0x14 bytes)
        uVar2 = (**(code **)(*this + 0x10))(); // getReliableBufferCount again (maybe dynamic?)
      } while (local_124 < uVar2);
    }
  }
  return;
}