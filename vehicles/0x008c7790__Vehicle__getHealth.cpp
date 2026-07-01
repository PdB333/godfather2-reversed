// FUNC_NAME: Vehicle::getHealth
uint Vehicle::getHealth(undefined4 param_1)
{
  int iVar1;
  
  iVar1 = FUN_008c7490(param_1);
  if (iVar1 != 0) {
    // Extract health from bitfield at +0x84
    // Bits [5..17] contain health value (13 bits)
    // Return value is masked to 0xffffff01 to clear lower byte
    return CONCAT31((uint3)(*(uint *)(iVar1 + 0x84) >> 0xd),~(byte)(*(uint *)(iVar1 + 0x84) >> 5)) &
           0xffffff01;
  }
  return 0;
}