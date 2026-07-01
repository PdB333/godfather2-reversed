// FUNC_NAME: Player::shutdown
void __fastcall Player::shutdown(undefined4 *this)
{
  int iVar1;
  
  iVar1 = this[0x14]; // +0x50: m_pPlayerData
  *this = &PTR_LAB_00d72db0; // vtable pointer
  FUN_005512c0(0); // likely some cleanup
  *(uint *)(iVar1 + 0x4a4) = *(uint *)(iVar1 + 0x4a4) & 0xfffffffe; // clear bit 0 of some flag at +0x4A4
  if (*(char *)(this + 0x26) != '\0') { // +0x98: m_bIsActive
    FUN_007f63e0(1); // disable something
    (**(code **)(*(int *)this[0x14] + 0x234))(4,1); // call virtual function at vtable+0x234 on player data
  }
  FUN_007f6420(0x5d); // unregister something (ID 0x5D)
  FUN_007f7e40(); // cleanup input
  FUN_0080ea60(); // base class destructor
  return;
}