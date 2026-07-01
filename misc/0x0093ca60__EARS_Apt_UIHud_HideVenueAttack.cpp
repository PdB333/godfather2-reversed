// Xbox PDB: EARS_Apt_UIHud_HideVenueAttack
// FUNC_NAME: VenueAttackManager::hideVenueAttack
void __thiscall VenueAttackManager::hideVenueAttack(void* this, char isPlayerAttack)
{
    // Check if bit 12 of flags at +0x5c is set
    if ((*(uint*)((int)this + 0x5c) >> 0xc & 1) != 0) {
        // Clear byte at +0x140 (some state flag)
        *(byte*)((int)this + 0x140) = 0;
        // Set state machine or animation at +0x10 to a specific state (label)
        setState((void*)((int)this + 0x10), &LAB_0093bd50, 1);
        // Clear byte at +0x16c (another flag)
        *(byte*)((int)this + 0x16c) = 0;
        // Release or decrement reference counts for two global resources
        releaseResource(&DAT_0112a5a4);
        releaseResource(&DAT_01130248);
        // Choose a global data pointer based on whether this is a player attack
        void* dataPtr = &DAT_00e36d94;
        if (isPlayerAttack == '\0') {
            dataPtr = &DAT_00e36da0;
        }
        // Send a "HideVenueAttack" event with parameters
        sendEvent("HideVenueAttack", 0, &DAT_00d8a64c, 1, dataPtr);
        // Prepare a local GUID/ID structure and clear it
        GUID localGuid;
        localGuid.data1 = DAT_01130330;
        localGuid.data2 = 0;
        localGuid.data3 = 0;
        clearGUID(&localGuid, 0);
    }
    return;
}