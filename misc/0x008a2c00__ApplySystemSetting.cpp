// FUNC_NAME: ApplySystemSetting
// Address: 0x008a2c00
// Description: Sets a global system setting based on a setting ID and value.
// The setting ID is used to select which global variable to update.
// Known IDs: 0 -> videoModeWidth? (DAT_0112eb94),
// 0x1b -> videoModeHeight? (DAT_0112eb98),
// 0x1c -> videoModeRefreshRate? (DAT_0112eb9c)
void __cdecl ApplySystemSetting(int settingId, unsigned int value)
{
    if (settingId == 0)
    {
        DAT_0112eb94 = value;  // +0x0: Possibly screen width or gamma
    }
    else if (settingId == 0x1b)
    {
        DAT_0112eb98 = value;  // +0x1b: Possibly screen height or brightness
    }
    else if (settingId == 0x1c)
    {
        DAT_0112eb9c = value;  // +0x1c: Possibly refresh rate or contrast
    }
    // Other IDs are ignored
}