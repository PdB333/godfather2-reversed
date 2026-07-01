// FUNC_NAME: SetGlobalSetting
// Function at 0x008a2c50: sets a global setting value based on ID (0x1d, 0x1e, 0x20)

extern int gGlobalSettingA;  // DAT_0112eba0
extern int gGlobalSettingB;  // DAT_0112eba4
extern int gGlobalSettingC;  // DAT_0112eba8

void SetGlobalSetting(int settingId, int value)
{
    if (settingId == 0x1d) {
        gGlobalSettingA = value;
    } else if (settingId == 0x1e) {
        gGlobalSettingB = value;
        return;
    } else if (settingId == 0x20) {
        gGlobalSettingC = value;
        return;
    }
    return;
}