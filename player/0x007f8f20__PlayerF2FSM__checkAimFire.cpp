// FUNC_NAME: PlayerF2FSM::checkAimFire
void __fastcall PlayerF2FSM::checkAimFire(int *this)
{
  char cVar1;
  
  // Check if bit 0 of byte at +0x129 is NOT set (meaning aiming?).
  // Also check if bit 15 of dword at +0x124 is set (maybe "can fire?" flag).
  if (((~*(byte *)(this + 0x129) & 1) != 0) && (((uint)this[0x124] >> 0xf & 1) != 0)) {
    // If we are allowed to fire and the aim is active, call a function that likely
    // tests if the player should start/continue firing.
    cVar1 = FUN_00481620();  // IsFirePressed? or ShouldStartFiring?
    if (cVar1 != '\0') {
      // Trigger the "fire" action (via vtable at +0x288, likely a method like startFiring or handleFire).
      (**(code **)(*this + 0x288))(2,0,0);
    }
  }
}