// FUNC_NAME: NetObject::createNetObject
uint* NetObject::createNetObject(uint param_1)
{
  uint* puVar1;
  undefined4 local_48;
  undefined4 local_44;
  undefined8* local_40;
  undefined8 local_3c;
  undefined8 local_34;
  uint local_2c[2];
  undefined1* puStack_24;
  undefined1 auStack_20[32];
  
  local_40 = &local_3c;
  local_48 = 0;
  local_44 = 0;
  local_3c = 0;
  local_34 = 0;
  FUN_005a92b0(&local_48);
  FUN_005b8b40(local_2c,param_1);
  puVar1 = (uint*)(*DAT_0119caf0)(8,0);
  if (puVar1 == (uint*)0x0) {
    puVar1 = (uint*)0x0;
  }
  else {
    *puVar1 = *puVar1 & 0xffff8007 | 7;
    *(undefined2*)((int)puVar1 + 2) = 0;
    *puVar1 = *puVar1 | 0x8000;
    puVar1[1] = local_2c[0];
  }
  if ((puStack_24 != auStack_20) && (puStack_24 != (undefined1*)0x0)) {
    (*DAT_0119caf4)(puStack_24);
  }
  if ((local_40 != &local_3c) && (local_40 != (undefined8*)0x0)) {
    (*DAT_0119caf4)(local_40);
  }
  return puVar1;
}