// FUNC_NAME: Entity::validateAndNotifyManager
// Function address: 0x008c6740
// Role: Checks entity type and if not a specific type (magic hash 0x637b907) and not disabled, triggers manager update.
// Offsets: +0x54 = type/hash, +0x84 bit 4 = disabled flag
void __thiscall Entity::validateAndNotifyManager(void)
{
    // If entity is not of type 0x637b907 (likely not a player) and not disabled
    if ((*(int*)((char*)this + 0x54) != 0x637b907) &&
        ((*(uint*)((char*)this + 0x84) >> 4 & 1) == 0))
    {
        // Retrieve global manager (e.g., CrimeManager, DonControlManager)
        int manager = GetManager();
        // Set manager mode/state (0 = idle? 1 = active?)
        InitializeManagerState(manager, 0, 1);
        // Apply the manager update (e.g., process crime scene, start chase)
        ApplyManagerUpdate(manager);
    }
    return;
}