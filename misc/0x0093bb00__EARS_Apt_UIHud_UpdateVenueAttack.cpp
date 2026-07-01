// Xbox PDB: EARS_Apt_UIHud_UpdateVenueAttack
// FUNC_NAME: CrimeManager::updateVenueAttack

void __fastcall CrimeManager::updateVenueAttack(CrimeManager* this)
{
    char bAllowUpdate;
    char eventData[16];  // Probably a GUID or formatted identifier (e.g., "VenueAttack_<ID>")

    // Check if a venue attack update is allowed (e.g., player in control of rackets, no active cooldown)
    bAllowUpdate = FUN_0093afa0();
    if (bAllowUpdate != '\0') {
        // Build event payload using the venue ID stored at this+0x13C
        // DAT_00e3266c is likely a format string or static identifier for venue attacks
        FUN_005c4630(eventData, 0x10, &DAT_00e3266c, *(int*)((char*)this + 0x13c));
        // Dispatch the "UpdateVenueAttack" event to trigger gameplay logic (e.g., update UI, respawn enemies)
        FUN_005a04a0("UpdateVenueAttack", 0, &DAT_00d8a64c, 1, eventData);
    }
}