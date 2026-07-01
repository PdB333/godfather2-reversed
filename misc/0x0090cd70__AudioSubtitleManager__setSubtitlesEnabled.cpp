// FUNC_NAME: AudioSubtitleManager::setSubtitlesEnabled
// Function at 0x0090cd70: Sets subtitle enable flag and notifies audio subsystem
void __thiscall AudioSubtitleManager::setSubtitlesEnabled(bool enable) {
    // Offset +0x14 holds bitfield flags; bit 0 = subtitles enabled
    if (enable) {
        *(uint32_t *)(this + 0x14) |= 1;
    } else {
        *(uint32_t *)(this + 0x14) &= ~1;
    }
    // Propagate change to audio subsystem (e.g., config/console variable)
    // FUN_0069bf00 likely writes to "Audio.Subtitles" config key
    FUN_0069bf00("Audio.Subtitles", enable);
}