// FUNC_NAME: NetPacketProcessor::processBitStream
void __thiscall NetPacketProcessor::processBitStream(uint this, undefined4 param_2, int param_3)
{
  byte bVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int local_8 [2];
  
  FUN_00472830(param_2,param_3); // BitStream::readHeader maybe
  uVar2 = *(uint *)(param_3 + 0x18); // +0x18: bit position in stream
  if (*(uint *)(param_3 + 0x2c) < uVar2) { // +0x2c: stream size
    *(undefined1 *)(param_3 + 0x1c) = 1; // +0x1c: overflow flag
  }
  else {
    bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(param_3 + 0xc)); // +0xc: data buffer
    *(uint *)(param_3 + 0x18) = uVar2 + 1; // increment bit position
    if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) { // check bit
      FUN_004a8ec0(0); // maybe allocate or reset some state
      FUN_004a9360(param_3,local_8); // read an int from bitstream
      iVar3 = FUN_004a8f00(); // decode/validate something
      if (iVar3 == 0) {
        if (local_8[0] == -0x1e98fd1) { // magic constant 0xE16702F
          if (*(int *)(this + 0x138) == 0) goto LAB_008db6ca; // +0x138: some flag
        }
        else if (*(int *)(this + 0x138) == 0) {
          FUN_004547e0(-(uint)(this != 0x58) & this,local_8,0); // callback with this
          goto LAB_008db6ca;
        }
        if (local_8[0] == -0x1e98fd1) {
          *(undefined4 *)(this + 0x138) = 0; // clear flag
        }
      }
      else {
        *(int *)(this + 0x138) = iVar3 + -0x58; // store decoded value - 0x58
      }
    }
  }
LAB_008db6ca:
  uVar2 = *(uint *)(param_3 + 0x18);
  if (*(uint *)(param_3 + 0x2c) < uVar2) {
    *(undefined1 *)(param_3 + 0x1c) = 1;
    return;
  }
  bVar1 = *(byte *)((uVar2 >> 3) + *(int *)(param_3 + 0xc));
  uVar4 = uVar2 + 1;
  *(uint *)(param_3 + 0x18) = uVar4;
  if ((bVar1 & (byte)(1 << ((byte)uVar2 & 7))) != 0) {
    if (*(uint *)(param_3 + 0x2c) < uVar4) {
      *(undefined1 *)(param_3 + 0x1c) = 1;
    }
    else {
      bVar1 = *(byte *)((uVar4 >> 3) + *(int *)(param_3 + 0xc));
      *(uint *)(param_3 + 0x18) = uVar2 + 2;
      if ((bVar1 & (byte)(1 << ((byte)uVar4 & 7))) != 0) {
        (**(code **)(*(int *)(this - 0x58) + 0x198))(); // virtual call via vtable at offset 0x198
        return;
      }
    }
    (**(code **)(*(int *)(this - 0x58) + 0x19c))(); // virtual call via vtable at offset 0x19c
  }
  return;
}