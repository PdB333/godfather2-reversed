// FUNC_NAME: GraphicsSettingsManager::applyPreset
void __fastcall GraphicsSettingsManager::applyPreset(int presetId)
{
    // +0x94: g_pSetting1 (string pointer for first setting, e.g. texture quality)
    // +0x98: g_pSetting2 (string pointer for second setting, e.g. shadow quality)
    // +0x9C: g_iCurrentPreset (stored preset index)
    // +0x00: g_pSettingsManager (pointer to settings manager object at DAT_01219940)

    // Default values (preset 6/null)
    g_pSetting1 = DAT_012198f8;
    g_pSetting2 = DAT_01219908;

    switch (presetId)
    {
    case 0:
    case 1:
        g_pSetting1 = DAT_012198f0;
        g_pSetting2 = DAT_012198f4;
        break;
    case 2:
        g_pSetting1 = DAT_01219a48;
        g_pSetting2 = DAT_012198f4;
        break;
    case 3:
        g_pSetting2 = DAT_01219900;
        break;
    case 4:
        g_pSetting1 = DAT_012198fc;
        g_pSetting2 = DAT_01219900;
        break;
    case 5:
        g_pSetting1 = DAT_01219a58;
        g_pSetting2 = DAT_01219900;
        break;
    case 6:
        break; // no change from default (lowest quality preset)
    case 7:
        g_pSetting1 = DAT_01219904;
        g_pSetting2 = DAT_01219900;
        break;
    case 8:
        g_pSetting1 = DAT_01219a68;
        break;
    case 9:
        g_pSetting1 = DAT_01219a50;
        break;
    case 10:
        g_pSetting1 = DAT_01219a4c;
        break;
    default:
        presetId = 0xB; // invalid -> force preset 11
        g_pSetting1 = DAT_01219a54;
        g_pSetting2 = DAT_01219900;
        break;
    }

    g_iCurrentPreset = presetId; // store applied preset index

    // If the settings manager is initialized, release the old strings/free resources
    if (DAT_012058e8 == &g_pSettingsManager) {
        FUN_0060a460(g_pSetting1);
        FUN_0060a460(g_pSetting2);
    }
}