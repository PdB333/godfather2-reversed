// FUNC_NAME: NetSession::handlePacket
void __thiscall NetSession::handlePacket(int this, int *packetData)
{
  int packetType;
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;
  
  FUN_0046c6a0(packetData);
  packetType = *packetData;
  if (packetType == DAT_0120e93c) {
    FUN_004086d0(&DAT_0120e93c);
    local_18 = &PTR_FUN_00e31e2c;
    if ((int *)(this + -0x3c) == (int *)0x0) {
      local_14 = 0;
    }
    else {
      local_14 = this + 0xc;
    }
    local_10 = 0;
    if (local_14 != 0) {
      local_10 = *(undefined4 *)(local_14 + 4);
      *(int **)(local_14 + 4) = &local_14;
    }
    local_8 = &local_18;
    local_c = DAT_0112a6ac;
    local_4 = 0;
    FUN_00408a00(&local_c,0);
    (**(code **)(*(int *)(this + -0x3c) + 0x24))();
    if (local_14 != 0) {
      FUN_004daf90(&local_14);
      return;
    }
  }
  else {
    if (packetType == DAT_0112fddc) {
                    /* WARNING: Could not recover jumptable at 0x006bd4d6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(*(int *)(this + -0x3c) + 0x2c))();
      return;
    }
    if (packetType == DAT_0112fdf8) {
      packetType = packetData[1];
      FUN_006bd3a0(packetType);
      (**(code **)(*(int *)(this + -0x3c) + 0x28))(packetType);
      return;
    }
    if ((packetType == DAT_01206778) && (packetData[1] != 0)) {
      packetType = *(int *)(packetData[1] + 0xc);
      if (packetType == 0) {
        packetType = 0;
      }
      else {
        packetType = *(int *)(packetType + 0x1c);
      }
      if (packetType == *(int *)(this + -0x20)) {
        if (((*(char *)(this + 0x14) == '\0') && ((*(byte *)(DAT_011299c4 + 0x14) & 1) == 0)) &&
           (DAT_01129820 == 0)) {
          FUN_006bd020();
          return;
        }
        FUN_006bcfe0();
      }
    }
  }
  return;
}