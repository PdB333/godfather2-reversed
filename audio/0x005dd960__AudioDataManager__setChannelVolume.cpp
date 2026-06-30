// FUNC_NAME: AudioDataManager::setChannelVolume
void __cdecl AudioDataManager::setChannelVolume(uint musicVolume, uint sfxVolume, uint dialogVolume)
{
    // +0x00f15b78: musicVolume
    DAT_00f15b78 = musicVolume;
    // +0x00f15b7c: sfxVolume
    DAT_00f15b7c = sfxVolume;
    // +0x012056c0: dialogVolume
    DAT_012056c0 = dialogVolume;
    // +0x00f15b80: combinedVolume (bitwise OR of all channels)
    DAT_00f15b80 = musicVolume | sfxVolume | dialogVolume;
    return;
}