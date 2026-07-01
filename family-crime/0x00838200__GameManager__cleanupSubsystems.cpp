// FUNC_NAME: GameManager::cleanupSubsystems
void __fastcall GameManager::cleanupSubsystems()
{
    // Destroy global subsystem instance (static)
    // DAT_012069c4 is a global pointer to a subsystem
    destroySubsystem((int*)0x012069c4);

    // Destroy array of 8 subsystems stored at offsets 0xA4 to 0xDC (inclusive)
    // Each subsystem is 8 bytes (likely a pointer or small handle)
    // Destroy in reverse order (last allocated first)
    destroySubsystem((int*)(this + 0xDC));  // Subsystem[7]
    destroySubsystem((int*)(this + 0xD4));  // Subsystem[6]
    destroySubsystem((int*)(this + 0xCC));  // Subsystem[5]
    destroySubsystem((int*)(this + 0xC4));  // Subsystem[4]
    destroySubsystem((int*)(this + 0xBC));  // Subsystem[3]
    destroySubsystem((int*)(this + 0xB4));  // Subsystem[2]
    destroySubsystem((int*)(this + 0xAC));  // Subsystem[1]
    destroySubsystem((int*)(this + 0xA4));  // Subsystem[0]
}