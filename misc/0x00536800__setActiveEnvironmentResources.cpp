// FUNC_NAME: setActiveEnvironmentResources
void __fastcall setActiveEnvironmentResources(bool useNightVariant)
{
    // EAX holds the environment index (0-5)
    // Based on index, select appropriate resource pointers (presumably for day/night variants)
    // Then if currently active environment is the default one (DAT_0121a1f0), release old resources

    switch (in_EAX) {
    case 0:
        // Environment set 0
        g_pEnvResourceB = g_EnvResourceSet0_B;
        g_pEnvResourceA = g_EnvResourceSet0_A;
        break;
    case 1:
        // Environment set 1
        g_pEnvResourceA = g_EnvResourceSet1_A;
        g_pEnvResourceB = g_EnvResourceSet1_B;
        break;
    case 2:
        // Environment set 2: day/night switch
        g_pEnvResourceA = g_EnvResourceSet2_A;
        g_pEnvResourceB = g_EnvResourceSet2_B_day;
        if (useNightVariant == false) {
            g_pEnvResourceB = g_EnvResourceSet2_B_night;
        }
        break;
    case 3:
        // Environment set 3: day/night switch
        g_pEnvResourceB = g_EnvResourceSet3_B;
        if (useNightVariant == false) {
            g_pEnvResourceB = g_EnvResourceSet3_B_night;
        }
        g_pEnvResourceA = g_EnvResourceSet3_A;
        break;
    case 4:
        // Environment set 4
        g_pEnvResourceA = g_EnvResourceSet4_A;
        g_pEnvResourceB = g_EnvResourceSet4_B;
        break;
    case 5:
        // Environment set 5
        g_pEnvResourceB = g_EnvResourceSet5_B;
        g_pEnvResourceA = g_EnvResourceSet5_A;
        break;
    }

    // If the active environment pointer is the default/empty one, release old resources before switching
    if (g_pActiveEnvironment == &g_defaultEnvironmentMarker) {
        releaseEnvironmentResource(g_pEnvResourceB);  // FUN_0060a460
        releaseEnvironmentResource(g_pEnvResourceA);
    }
}