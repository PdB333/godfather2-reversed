// FUNC_NAME: NetSession::processReliablePacket
void NetSession::processReliablePacket(undefined4 *param_1, undefined4 param_2, undefined4 *param_3, undefined4 param_4, int *param_5)
{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int iVar4;
  char cVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 uStack_80;
  undefined4 uStack_7c;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined **local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  int local_58;
  undefined4 local_54;
  undefined1 auStack_50 [12];
  undefined4 local_44;
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_14;
  
  piVar3 = param_5;
  iVar1 = param_5[5]; // +0x14: connection pointer
  if ((iVar1 != 0) && ((int *)(iVar1 + -0x48) != (int *)0x0)) {
    local_6c = *param_3; // packet data start
    local_68 = param_3[1];
    uVar2 = *(undefined4 *)(iVar1 + 0xe8); // +0xE8: some session data
    local_64 = param_3[2];
    local_60 = param_3[3];
    local_54 = param_2; // sequence number
    local_70 = &PTR_LAB_00d75140; // vtable or static table
    local_5c = param_4; // flags
    local_58 = 0;
    FUN_004a4bd0(&local_70); // likely allocate or initialize buffer
    iVar4 = local_58;
    if ((local_58 != 0) && (*(int *)(local_58 + 4) != 0)) {
      local_44 = 0;
      local_34 = 0;
      local_24 = 0;
      local_14 = _DAT_00d5780c; // global timestamp
      uVar6 = (**(code **)(*piVar3 + 0x2c))(); // vtable call: getPacketType?
      FUN_00449da0(auStack_50, uVar6); // serialize packet type
      iVar7 = FUN_009c8e50(0x34); // allocate 0x34 bytes
      if (iVar7 != 0) {
        uStack_7c = param_1[1];
        uStack_80 = *param_1;
        uStack_74 = param_1[3];
        uStack_78 = param_1[2];
        puVar8 = &param_5;
        uVar6 = (**(code **)(*(int *)(iVar1 + -0x48) + 0x58))(puVar8); // vtable call: getConnection?
        puVar8 = (undefined4 *)FUN_004150c0(uVar2, &uStack_80, auStack_50, uVar6, puVar8); // build packet
        if ((puVar8 != (undefined4 *)0x0) && (cVar5 = FUN_004a44a0(iVar4, puVar8), cVar5 == '\0')) {
          (**(code **)*puVar8)(1); // process packet
        }
      }
    }
  }
  if ((param_5 != (int *)0x0) && (param_5[1] = param_5[1] + -1, param_5[1] == 0)) {
    (**(code **)(*param_5 + 4))(); // release reference
  }
  return;
}