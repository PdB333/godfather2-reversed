// FUNC_NAME: SetFeatureEnabled
void SetFeatureEnabled(char isEnabled)
{
    // DAT_0112a064: feature enabled flag
    g_featureEnabled = isEnabled;
    // DAT_0112a068: feature state value (copied from global _DAT_00d5cf70)
    g_featureState = g_globalStateValue;
    if (isEnabled == 0)
    {
        // FUN_0069e8b0: cleanup / deinitialize feature
        DeinitializeFeature();
    }
}