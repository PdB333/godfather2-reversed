// FUNC_NAME: GodfatherGameManager::updateTick
// Address: 0x005ef5a0
// Role: Per-frame update for the game manager. Resets a global busy flag, checks if the manager is ready via virtual call (vtable+0xEC), and if so performs additional processing (cleaning and handling a data buffer).
void __fastcall GodfatherGameManager::updateTick(int *this) // ECX = this
{
  char isReady;
  
  g_bGameManagerBusy = false; // DAT_0120569d
  isReady = (*(code **)(*this + 0xec))(); // virtual call: bool isReady()
  if (isReady != '\0') {
    FUN_005ef7a0(); // static helper, likely cleans up stale references
    FUN_005ef5f0(this, this[3]); // uses this->someData at offset +0xC (int)
  }
  return;
}