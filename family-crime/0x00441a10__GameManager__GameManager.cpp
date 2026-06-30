// FUNC_NAME: GameManager::GameManager
undefined4 * __fastcall GameManager::GameManager(undefined4 *this)
{
  this[1] = 0;                                          // +0x04: unknown member, init to 0
  this[2] = &PTR_LAB_00e310bc;                         // +0x08: second vtable pointer (set, then overwritten below)
  g_pGameManager = this;                                // store global singleton pointer
  *this = &PTR_FUN_00e310ac;                           // +0x00: vtable pointer for this class
  this[2] = &PTR_LAB_00e310b8;                         // +0x08: overwritten with another vtable (interface?)
  this[3] = 0;                                          // +0x0C: unknown member, init to 0
  FUN_0049c6e0(&PTR_LAB_00e310a0, 1);                  // registration/initialization call
  return this;
}