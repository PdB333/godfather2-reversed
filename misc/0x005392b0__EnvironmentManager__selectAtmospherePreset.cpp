// FUNC_NAME: EnvironmentManager::selectAtmospherePreset

void EnvironmentManager::selectAtmospherePreset(int presetId)
{
    // Global pointers to atmosphere/sky objects
    static Atmosphere* g_defaultAtmosphere = s_atmosphereDefault;         // DAT_01219908
    static Atmosphere* g_currentAtmosphere;                               // DAT_0121b750
    static SkyMesh* g_currentSkyMesh;                                     // DAT_0121b754
    static int g_skyFlags;                                                // DAT_0121b874
    static int g_skyIndex;                                                // DAT_0121b878
    static SkyMesh* g_skyPresets[12];                                     // DAT_0121bbd4 (base)
    static ShaderParameter* g_fogColorParam;                             // DAT_0121bb7c
    static ShaderParameter* g_fogParamsParam;                            // DAT_0121bb80
    static ShaderParameter* g_depthTextureParam;                         // DAT_0121bb84
    static Atmosphere* g_altAtmosphere;                                   // DAT_0121bc0c

    g_currentAtmosphere = g_defaultAtmosphere;

    if (presetId != 5)
    {
        g_skyFlags = 0;
    }

    switch (presetId)
    {
    case 0:
        g_currentSkyMesh = g_skyPreset0;          // DAT_0121bbb0
        break;
    case 1:
        g_currentSkyMesh = g_skyPreset1;          // DAT_0121bbb4
        break;
    case 2:
        g_currentSkyMesh = g_skyPreset2;          // DAT_0121bbb8
        break;
    case 3:
        g_currentSkyMesh = g_skyPreset3;          // DAT_0121bba8
        break;
    case 4:
        g_currentSkyMesh = g_skyPreset4;          // DAT_0121bbac
        break;
    case 5:
        // Complex sub-selection based on flags
        if ((g_skyFlags & 4) == 0)
        {
            if ((g_skyFlags & 1) == 0)
            {
                g_skyIndex = ((g_skyFlags >> 4) & 8) +
                             ((g_skyFlags >> 5) & 2) +
                             ((g_skyFlags >> 3) & 2) +
                             2 +
                             ((g_skyFlags >> 3) & 1);
            }
            else
            {
                g_skyIndex = 0;
            }
        }
        else
        {
            g_skyIndex = 1;
        }
        g_currentSkyMesh = g_skyPresets[g_skyIndex];  // base array at DAT_0121bbd4
        if ((g_skyFlags & 2) != 0)
        {
            g_currentAtmosphere = g_altAtmosphere;
        }
        break;
    case 6:
        g_currentSkyMesh = g_skyPreset6;          // DAT_0121bbbc
        break;
    case 7:
        g_currentSkyMesh = g_skyPreset7;          // DAT_0121bbc0
        break;
    case 8:
        g_currentSkyMesh = g_skyPreset8;          // DAT_0121bbc4
        break;
    case 9:
        g_currentSkyMesh = g_skyPreset9;          // DAT_0121bbc8
        break;
    case 10:
        g_currentSkyMesh = g_skyPreset10;         // DAT_0121bbcc
        break;
    case 11:
        g_currentSkyMesh = g_skyPreset11;         // DAT_0121bbd0
        break;
    }

    // If the selected sky mesh has fog/depth capabilities, retrieve shader parameters
    if (g_currentSkyMesh == g_skyPreset7 || g_currentSkyMesh == g_skyPreset8 || g_currentSkyMesh == g_skyPreset9)
    {
        g_fogColorParam = getShaderParameter(g_currentSkyMesh, "fog_color");        // FUN_0060a580
        g_fogParamsParam = getShaderParameter(g_currentSkyMesh, "fog_params");
        g_depthTextureParam = getShaderParameter(g_currentSkyMesh, "depth_texture");
    }

    // If the scene manager is currently referencing this environment container, release old references
    if (g_sceneManager == &g_environmentContainer)   // DAT_012058e8 == &DAT_0121b740
    {
        releaseShaderParameter(g_currentSkyMesh);     // FUN_0060a460 on sky mesh
        releaseShaderParameter(g_currentAtmosphere);  // on atmosphere
    }
}