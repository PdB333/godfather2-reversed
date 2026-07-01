// FUNC_NAME: Player::hideWeaponDisplay
void __fastcall Player::hideWeaponDisplay(Player* this)
{
    // Dispatches a "HideWeaponDisplay" event (likely UI-related)
    // Parameters: eventName string, 0, global data pointer (DAT_00d8a64c), 0
    triggerEvent("HideWeaponDisplay", 0, &DAT_00d8a64c, 0);
    // Clears weapon display visibility flags at offset +0x5c
    // Bitmask 0xe7ffff3f clears specific bits (e.g., 0x1C0000C0?)
    this->flags &= 0xe7ffff3f;
}