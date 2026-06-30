// FUNC_NAME: NetConnection::processNextPacket
uint __thiscall NetConnection::processNextPacket(int *this, undefined4 param_2)
{
  uint uVar1;
  int iVar2;
  undefined4 uStack_18;
  undefined4 uStack_14;
  
  uStack_14 = param_2;
  uStack_18 = 0x542f98;
  uVar1 = (**(code **)(*this + 0x1dc))(); // +0x1DC: checkPacketAvailable virtual
  if ((char)uVar1 != '\0') {
    uStack_18 = param_2;
    uVar1 = (**(code **)(*this + 0x1e0))(); // +0x1E0: readPacketHeader virtual
    if ((char)uVar1 != '\0') {
      (**(code **)(*this + 0x1ec))(param_2,&stack0xfffffff0); // +0x1EC: processPacketData virtual
      iVar2 = (**(code **)(*this + 500))(&uStack_18); // +0x1F4: checkPacketComplete virtual (500 = 0x1F4)
      return (uint)(iVar2 == 0);
    }
  }
  return uVar1 & 0xffffff00;
}