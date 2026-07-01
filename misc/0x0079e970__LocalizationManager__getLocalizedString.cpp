// FUNC_NAME: LocalizationManager::getLocalizedString
uint LocalizationManager::getLocalizedString(uint textId)
{
    // Read flags from large offset (likely a bitfield in a manager object)
    uint flags = *(uint *)(this + 0x249c); // +0x249c: localization flags
    uint shifted = flags >> 1;

    // Check bit1 of original flags (bit0 of shifted)
    if ((shifted & 1) != 0)
    {
        // Global condition: is localization (language/region) enabled?
        // FUN_00481620 – returns char, non-zero if active
        if (isLocalizationEnabled()) 
        {
            // Retrieve localized string using language ID (byte at +0x2498) and text ID
            // FUN_004657f0 – performs actual string lookup
            return lookupLocalizedString(*(byte *)(this + 0x2498), textId);
        }
    }

    // Return error code: flags>>1 with low byte cleared
    return shifted & 0xFFFFFF00;
}