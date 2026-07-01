// FUNC_NAME: BitStreamReader::readNextPacket
void BitStreamReader::readNextPacket(int param_1, int *param_2)
{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  code *pcVar4;
  int *piVar5;
  int iVar6;
  int local_c0;
  bool local_b8 [8];
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
  undefined1 local_a4 [8];
  undefined1 auStack_9c [44];
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined1 auStack_60 [92];
  
  uVar3 = *(uint *)(param_1 + 0x18); // +0x18: currentBitIndex
  if (*(uint *)(param_1 + 0x2c) < uVar3) { // +0x2c: totalBits
    *(undefined1 *)(param_1 + 0x1c) = 1; // +0x1c: overflowFlag
  }
  else {
    bVar2 = *(byte *)((uVar3 >> 3) + *(int *)(param_1 + 0xc)); // +0xc: dataBuffer
    *(uint *)(param_1 + 0x18) = uVar3 + 1;
    if ((bVar2 & (byte)(1 << ((byte)uVar3 & 7))) != 0) {
      FUN_004a8ec0(0); // readBit
      FUN_004a9360(param_1,local_b8); // readBits
      local_c0 = FUN_004a8f00(); // getReadOffset
      if (local_c0 == 0) {
        local_c0 = 0;
      }
      else {
        local_c0 = local_c0 + -0x58;
      }
      goto LAB_00853226;
    }
  }
  FUN_004a8f30(0); // skipBits
  FUN_004a93d0(param_1,local_a4); // readBytes
  local_c0 = FUN_004a8f80(); // getReadPosition
LAB_00853226:
  if (*(uint *)(param_1 + 0x2c) < *(uint *)(param_1 + 0x18)) {
    *(undefined1 *)(param_1 + 0x1c) = 1;
  }
  else {
    *(uint *)(param_1 + 0x18) = *(uint *)(param_1 + 0x18) + 1;
  }
  uVar3 = *(uint *)(param_1 + 0x18);
  if (*(uint *)(param_1 + 0x2c) < uVar3) {
    *(undefined1 *)(param_1 + 0x1c) = 1;
    local_b8[0] = false;
  }
  else {
    local_b8[0] = (*(byte *)((uVar3 >> 3) + *(int *)(param_1 + 0xc)) &
                  (byte)(1 << ((byte)uVar3 & 7))) != 0;
    *(uint *)(param_1 + 0x18) = uVar3 + 1;
  }
  iVar6 = 0;
  FUN_004a9c90(param_1,&local_b0); // readPacketHeader
  local_70 = local_b0;
  local_6c = local_ac;
  local_68 = local_a8;
  piVar5 = (int *)FUN_004eb390(0xb0,0x10); // allocate memory
  if (piVar5 == (int *)0x0) {
    piVar5 = (int *)0x0;
  }
  else {
    piVar5[1] = 0;
    *piVar5 = (int)&PTR_FUN_00e380b0; // vtable
    piVar5[2] = 0;
    piVar5[3] = 0;
    piVar5[4] = 0;
    piVar5[5] = 0;
    piVar5[6] = 0;
    piVar5[7] = -1;
    piVar5[0x28] = 0;
    piVar5[2] = piVar5[2] | 3;
  }
  piVar1 = piVar5 + 5;
  if (local_c0 != 0) {
    iVar6 = local_c0 + 0x48;
  }
  if (*piVar1 != iVar6) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1); // release reference
    }
    *piVar1 = iVar6;
    if (iVar6 != 0) {
      piVar5[6] = *(int *)(iVar6 + 4);
      *(int **)(iVar6 + 4) = piVar1;
    }
  }
  (**(code **)(*piVar5 + 0x30))(0); // vtable call
  if (piVar5[3] != 0) {
    FUN_004daf90(piVar5 + 3);
    piVar5[3] = 0;
  }
  (**(code **)(*piVar5 + 0x10))(local_c0); // vtable call
  (**(code **)(*piVar5 + 0x18))(local_c0); // vtable call
  pcVar4 = *(code **)(*piVar5 + 0x20);
  piVar5[0x28] = 0;
  (*pcVar4)(auStack_9c); // vtable call
  (**(code **)(*piVar5 + 0x24))(auStack_60); // vtable call
  if (*param_2 != 0) {
    piVar1 = (int *)(*param_2 + 4);
    *piVar1 = *piVar1 + -1;
    if (((int *)*param_2)[1] == 0) {
      (**(code **)(*(int *)*param_2 + 4))(); // destructor
    }
    *param_2 = 0;
  }
  *param_2 = (int)piVar5;
  piVar5[1] = piVar5[1] + 1;
  return;
}