//FUNC_NAME: AudioOptions::enableSubtitlesForLanguage
void __fastcall AudioOptions::enableSubtitlesForLanguage(int this)
{
    // Get current language ID (0xFFFFFFFF = default/current)
    int languageID = getCurrentLanguageID(0xFFFFFFFF);
    // Determine language type; negative indicates a language that requires forced subtitles
    int languageType = getLanguageType(languageID);
    if (languageType < 0)
    {
        // Set subtitle enabled flag at offset +0x14 (bit 0)
        *(uint32_t *)(this + 0x14) |= 1;
        // Enable subtitles in settings
        setSettingValue("Audio.Subtitles", 1);
    }
}