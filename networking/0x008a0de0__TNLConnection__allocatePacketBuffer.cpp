// FUNC_NAME: TNLConnection::allocatePacketBuffer
int TNLConnection::allocatePacketBuffer(int param_1, int param_2)
{
  int iVar1;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = _DAT_00d5780c; // +0x0c: Some global constant/flag
  iVar1 = FUN_008a09a0(DAT_01129914 + 0x40, &local_20, param_2, 0); // DAT_01129914 likely connection manager instance // +0x40: member field offset for packet buffer allocation
  if (iVar1 != 0) {
    return iVar1 + 0xc; // Return buffer pointer adjusted by +0xc (likely packet header offset)
  }
  return 0;
}