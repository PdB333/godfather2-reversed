// FUNC_NAME: RandomGenerator::getRandomInRange
uint __thiscall RandomGenerator::getRandomInRange(int this, undefined4 *param_2)
{
  uint uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = param_2[1];
  local_10 = *param_2;
  local_8 = param_2[2];
  local_4 = param_2[3];
  FUN_004d9af0(); // likely seed update or internal state advance
  uVar1 = FUN_004db320(&local_10,0x10); // hash or CRC on 16-byte input
  return uVar1 % *(uint *)(this + 4); // +0x4: range/max value
}