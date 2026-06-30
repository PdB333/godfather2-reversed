// FUNC_NAME: Crypto::verifyHMAC_SHA1
uint Crypto::verifyHMAC_SHA1(undefined4 param_1, undefined4 param_2, uint param_3)
{
  undefined4 in_EAX;
  uint uVar1;
  undefined1 local_f8 [4];
  undefined1 local_f4;
  undefined1 local_f3;
  undefined1 local_f2;
  undefined1 local_f1;
  byte local_f0 [32];
  undefined1 local_d0 [208];
  
  local_f4 = (undefined1)((uint)in_EAX >> 0x18);
  local_f3 = (undefined1)((uint)in_EAX >> 0x10);
  local_f2 = (undefined1)((uint)in_EAX >> 8);
  local_f1 = (undefined1)in_EAX;
  FUN_006595c0(local_d0); // SHA1_Init
  FUN_00659640(local_d0,local_f8,8); // SHA1_Update with key
  FUN_00659640(local_d0,param_1,8); // SHA1_Update with data1
  FUN_00659640(local_d0,param_2,8); // SHA1_Update with data2
  FUN_00659730(local_d0,local_f0); // SHA1_Final
  uVar1 = 0;
  if (8 < param_3) {
    do {
      if (local_f0[uVar1] != 0) {
        return uVar1 & 0xffffff00;
      }
      param_3 = param_3 - 8;
      uVar1 = uVar1 + 1;
    } while (8 < param_3);
  }
  return CONCAT31((int3)(uVar1 >> 8),
                  '\\x01' - ((-1 << (8U - (char)param_3 & 0x1f) & local_f0[uVar1]) != 0));
}