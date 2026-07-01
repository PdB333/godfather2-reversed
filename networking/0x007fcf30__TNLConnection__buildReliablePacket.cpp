// FUNC_NAME: TNLConnection::buildReliablePacket
void TNLConnection::buildReliablePacket(undefined4 param_1, int *param_2, undefined4 param_3, undefined4 *param_4,
                 undefined4 param_5, int *param_6, undefined4 param_7, undefined4 *param_8,
                 undefined4 param_9)

{
  undefined4 uVar1;
  undefined4 unaff_EBX;
  undefined4 uStack_b8;
  undefined4 uStack_b4;
  undefined4 uStack_a4;
  undefined4 local_90 [2];
  undefined4 uStack_88;
  undefined4 local_84;
  undefined4 uStack_80;
  undefined4 uStack_78;
  undefined4 local_74;
  undefined4 uStack_70;
  undefined4 uStack_68;
  undefined4 local_64;
  undefined4 uStack_60;
  undefined1 auStack_5c [4];
  undefined4 uStack_58;
  undefined4 local_54;
  undefined4 uStack_50;
  undefined4 uStack_48;
  undefined4 local_44;
  undefined4 uStack_40;
  undefined4 uStack_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 local_24;
  undefined4 local_14;
  
  uStack_b4 = 1;
  uStack_b8 = param_5;
  local_84 = 0;
  local_74 = 0;
  local_64 = 0;
  local_54 = _DAT_00d5780c;
  local_44 = 0;
  local_34 = 0;
  local_24 = 0;
  local_14 = _DAT_00d5780c;
  (**(code **)(*param_2 + 0x8c))(local_90);
  (**(code **)(*param_6 + 0x8c))(auStack_5c,param_9,1);
  param_4[4] = param_7;
  param_4[5] = param_8;
  param_4[6] = local_90[0];
  param_4[8] = uStack_88;
  param_4[9] = local_84;
  param_4[10] = uStack_80;
  *param_4 = unaff_EBX;
  param_4[0xc] = uStack_78;
  param_4[1] = uStack_a4;
  param_4[0xd] = local_74;
  param_4[2] = param_3;
  param_4[0xe] = uStack_70;
  uVar1 = _DAT_00d5780c;
  param_4[3] = 0;
  param_4[7] = 0;
  param_4[0xb] = 0;
  param_4[0xf] = uVar1;
  *param_8 = uStack_68;
  param_8[1] = local_64;
  param_8[2] = uStack_60;
  param_8[4] = uStack_58;
  param_8[3] = 0;
  param_8[5] = local_54;
  param_8[6] = uStack_50;
  param_8[7] = 0;
  param_8[0xb] = 0;
  param_8[8] = uStack_48;
  param_8[0xc] = uStack_38;
  param_8[9] = local_44;
  param_8[0xd] = local_34;
  param_8[10] = uStack_40;
  param_8[0xe] = uStack_30;
  param_8[0xf] = uVar1;
  FUN_007f7ae0(&uStack_b8,param_1);
  return;
}