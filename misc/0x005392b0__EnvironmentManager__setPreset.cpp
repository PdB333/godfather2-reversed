// FUNC_NAME: EnvironmentManager::setPreset
// Address: 0x005392b0
// Role: Selects and applies an environment effect preset based on an index (0-11). Preset 5 uses bit flags to select a combined effect.

// Reconstructed C++ for The Godfather 2 (EARS engine, x86)
// Assumes global state: s_pMainEffect, s_pCurrentEffect, s_flags, etc.

void EnvironmentManager::setPreset(int presetIndex)
{
    // Default main effect (base)
    s_pMainEffect = s_defaultEffect; // DAT_01219908

    // Reset flags for any preset except 5 (dynamic/combined)
    if (presetIndex != 5)
    {
        s_flags = 0; // DAT_0121b874
    }

    // Select the current effect based on the preset index
    switch (presetIndex)
    {
    case 0:
        s_pCurrentEffect = s_effect0; // DAT_0121bbb0
        break;
    case 1:
        s_pCurrentEffect = s_effect1; // DAT_0121bbb4
        break;
    case 2:
        s_pCurrentEffect = s_effect2; // DAT_0121bbb8
        break;
    case 3:
        s_pCurrentEffect = s_effect3; // DAT_0121bba8
        break;
    case 4:
        s_pCurrentEffect = s_effect4; // DAT_0121bbac
        break;
    case 5:
    {
        // Composite preset: use flags to compute an array index
        if ((s_flags & 4) == 0)
        {
            if ((s_flags & 1) == 0)
            {
                // Compute combined index: bits from flags
                s_tempIndex = ( (s_flags >> 4) & 8 ) + ( (s_flags >> 5) & 2 ) + ( (s_flags >> 3) & 2 ) + 2 + ( (s_flags >> 3) & 1 ); // DAT_0121b878
            }
            else
            {
                s_tempIndex = 0;
            }
        }
        else
        {
            s_tempIndex = 1;
        }
        s_pCurrentEffect = s_effectArray[s_tempIndex]; // DAT_0121bbd4[ index ]

        // Override main effect if certain flag (2) is set
        if ((s_flags & 2) != 0)
        {
            s_pMainEffect = s_effectOverride; // DAT_0121bc0c
        }
        break;
    }
    case 6:
        s_pCurrentEffect = s_effect6; // DAT_0121bbbc
        break;
    case 7:
        s_pCurrentEffect = s_effect7; // DAT_0121bbc0
        break;
    case 8:
        s_pCurrentEffect = s_effect8; // DAT_0121bbc4
        break;
    case 9:
        s_pCurrentEffect = s_effect9; // DAT_0121bbc8
        break;
    case 10:
        s_pCurrentEffect = s_effect10; // DAT_0121bbcc
        break;
    case 11:
        s_pCurrentEffect = s_effect11; // DAT_0121bbd0
        break;
    }

    // For effects that include fog (specific pointers), load additional parameters
    if (s_pCurrentEffect == s_effect7 || s_pCurrentEffect == s_effect8 || s_pCurrentEffect == s_effect9) // DAT_0121bbc0, DAT_0121bbc4, DAT_0121bbc8
    {
        s_fogColor = getEffectPropertyPtr(s_pCurrentEffect, "fog_color");     // FUN_0060a580
        s_fogParams = getEffectPropertyPtr(s_pCurrentEffect, "fog_params");   // FUN_0060a580
        s_depthTexture = getEffectPropertyPtr(s_pCurrentEffect, "depth_texture"); // FUN_0060a580
    }

    // If the active manager points to this environment manager's instance, activate the effects
    if (s_pActiveManager == &s_environmentManagerInstance) // DAT_012058e8 == &DAT_0121b740
    {
        applyEffect(s_pCurrentEffect); // FUN_0060a460
        applyEffect(s_pMainEffect);    // FUN_0060a460
    }
}