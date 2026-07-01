// FUNC_NAME: AudioManager::playSoundEvent
void __fastcall AudioManager::playSoundEvent(int this)
{
    char result;
    int soundId;
    int soundHandle;

    soundId = 0x63c15f4e; // Hash for a specific sound event
    soundHandle = 0;
    // Call virtual method at vtable+0x10 to get sound handle from ID
    result = (*(code **)(**(int **)(this + 0xc) + 0x10))(soundId, &soundHandle);
    if ((result != '\0') && (soundId != 0)) {
        FUN_007944d0(1); // Likely lock or begin audio update
        FUN_00796ba0(soundHandle, DAT_00d5ccf8); // Play sound with handle and global audio manager
        FUN_007944d0(0); // Unlock or end audio update
    }
    return;
}