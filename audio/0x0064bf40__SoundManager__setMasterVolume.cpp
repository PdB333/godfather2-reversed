// FUNC_NAME: SoundManager::setMasterVolume
void SoundManager::setMasterVolume(float volume)
{
    // Clamp volume to byte range (0-255) and add 1 for some reason
    // The cast to byte then back to uint ensures wrapping
    uint adjustedVolume = (uint)(byte)((char)volume + 1);
    
    // Set volume on both channels (left/right or main/sub?)
    setChannelVolume(adjustedVolume);  // FUN_00b9a9fa
    applyVolume(adjustedVolume);       // FUN_0064be30
    
    // Set original volume on both channels
    setChannelVolume(volume);          // FUN_00b9a9fa
    applyVolume(volume);               // FUN_0064be30
}